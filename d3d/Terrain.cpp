#include "stdafx.h"


#include <string>
#include<d3d9.h>
#include<d3dx9.h>
#include"D3DUtil.h"
#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;
 
#include "sknwindow.h"
#include "Terrain.h"

namespace skn_d3d {
	const DWORD TerrainVertex::FVF = D3DFVF_XYZ |   D3DFVF_TEX1;
	Terrain::Terrain(IDirect3DDevice9 *device, std::string heightmapFilename, int numVersPerRow, int numVersPerCol, int cellSpacing, float heightScale)
	{
		_device = device;
		_numCellsPerRow = numVersPerRow - 1;
		_numCellsPerCol = numVersPerCol - 1;
		_numVersPreRow = numVersPerRow;
		_numVersPerCol = numVersPerCol;
		_numTriangles = _numCellsPerCol*_numCellsPerRow * 2;
		_cellSpacing = cellSpacing;
		_heithtScale = heightScale;
		_numVertices = numVersPerCol*numVersPerRow;
		//_xlength,_zlength必须是2的倍数，因为有很多地方要除以2
		_xlength = _numCellsPerRow*_cellSpacing;
		_zlength = _numCellsPerCol*_cellSpacing;
		// load heightmap
		if (!readRawFile(heightmapFilename))
		{
			::MessageBox(0, _T("readRawFile - FAILED"), 0, 0);
			::PostQuitMessage(0);
		}

		// scale heights
		for (int i = 0; i < _heightMap.size(); i++)
			_heightMap[i] *= heightScale;

		// compute the vertices
		if (!buideVertex())
		{
			::MessageBox(0, _T("computeVertices - FAILED"), 0, 0);
			::PostQuitMessage(0);
		}

		// compute the indices
		if (!buideIndex())
		{
			::MessageBox(0, _T("computeIndices - FAILED"), 0, 0);
			::PostQuitMessage(0);
		}
	}

	bool Terrain::readRawFile(std::string fileName)
	{
		std::vector<byte> in(_numVertices);
		std::ifstream infile(fileName.c_str(), std::ios_base::binary);
		if (!infile.is_open())
		{
			return false;
		}
		infile.read((char*)&in[0], _numVertices);
		infile.close();
		_heightMap.resize(_numVertices);
		for (int i = 0; i < in.size(); i++)
		{
			_heightMap[i] = in[i];
		}
		return true;
	}

	int Terrain::getHeightmapEntry(int row, int col)
	{
		return _heightMap[row*_numVersPreRow + col];
	}

	float Terrain::getHeight(float x, float z)
	{
		x += _xlength / 2.0f;
		z = _zlength / 2.0f-z;
		x/= _cellSpacing;
		z/= _cellSpacing;
		int col = (int)x;
		int row = (int)z  ;
		if (row<0)
		{
			row = 0;
		}
		if (col<0)
		{
			col = 0;
		}
		if (row>62)
		{
			row = 62;
		}
		if (col>62)
		{
			col = 62;
		}
		//  A   B
		//  *---*
		//  | / |
		//  *---*  
		//  C   D
		float a = getHeightmapEntry(row, col);
		float b= getHeightmapEntry(row, col+1);
		float c = getHeightmapEntry(row+1, col);
		float d = getHeightmapEntry(row+1, col+1);
		float dx = x - col;
		float  dz = z - row;
		float height = 0;
		if (dz<1-dx)
		{
			float uy = b - a; // A->B
			float vy = c - a; // A->C
			height = a + Learp(0, uy, dx) + Learp(0, vy, dz);
		}
		else {
			float uy = c - d; // D->C
			float vy = b - d; // D->B
			height = d + Learp(0, uy, 1-dx) + Learp(0, vy,1- dz);
		}
		return height;
	}

	void Terrain::setHeightmapEntry(int row, int col, int height)
	{
		_heightMap[row*_numVersPreRow + col] = height;
	}

	bool Terrain::draw(float x, float y, float z, bool drawLine)
	{
		int hr;
		if (_device)
		{
			D3DXMATRIX position;
			D3DXMatrixTranslation(&position, x, y, z);
			_device->SetTransform(D3DTS_WORLD, &(position));
			_device->SetStreamSource(0, _vertexBuffer, 0, sizeof(TerrainVertex));
			_device->SetIndices(_indexBuffer);
			_device->SetFVF(TerrainVertex::FVF);
			_device->SetTexture(0,_tex);
			_device->SetRenderState(D3DRS_LIGHTING, false);
			hr=_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numVertices, 0, _numTriangles);
			_device->SetRenderState(D3DRS_LIGHTING, true);
			if (FAILED(hr))
			{
				::MessageBox(0, _T("computeIndices - FAILED"), 0, 0);
				::PostQuitMessage(0);
			}
			return true;
		}
		
		return false;
	}

	float Terrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
	{
		// get heights of three vertices on the quad
		float heightA = getHeightmapEntry(cellRow, cellCol);
		float heightB = getHeightmapEntry(cellRow, cellCol + 1);
		float heightC = getHeightmapEntry(cellRow + 1, cellCol);

		// build two vectors on the quad
		D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
		D3DXVECTOR3 v(0.0f, heightC - heightA, -_cellSpacing);

		// find the normal by taking the cross product of two
		// vectors on the quad.
		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &u, &v);
		D3DXVec3Normalize(&n, &n);

		float cosine = D3DXVec3Dot(&n, directionToLight);

		if (cosine < 0.0f)
			cosine = 0.0f;

		return cosine;
	}

	bool Terrain::lightTerrain(D3DXVECTOR3 * directionToLight)
	{
		HRESULT hr = 0;

		D3DSURFACE_DESC textureDesc;
		_tex->GetLevelDesc(0 /*level*/, &textureDesc);

		// make sure we got the requested format because our code that fills the
		// texture is hard coded to a 32 bit pixel depth.
		if (textureDesc.Format != D3DFMT_A8R8G8B8) {
		 
			skn_window::MessageBoxPrintf(_T("lightTerrain - textureDesc.Format =%d"),_T("lightTerrain - textureDesc.Format =%d"),(int)textureDesc.Format);
			return false;
		}
			

		D3DLOCKED_RECT lockedRect;
		_tex->LockRect(
			0,          // lock top surface level in mipmap chain
			&lockedRect,// pointer to receive locked data
			0,          // lock entire texture image
			0);         // no lock flags specified

		DWORD* imageData = (DWORD*)lockedRect.pBits;
		/*int pixPerCellRow = textureDesc.Width / _numCellsPerRow;
		int pixPerCellCol = textureDesc.Height / _numCellsPerCol;*/
		skn_window::MessageBoxPrintf(_T("lightTerrain - textureDesc.Format =%d"), _T("lightTerrain - textureDesc.Format =%d"), (int)textureDesc.Height);

		for (int i = 0; i < textureDesc.Height; i++)
		{
			
			for (int j = 0; j < textureDesc.Width; j++)
			{
				// index into texture, note we use the pitch and divide by 
				// four since the pitch is given in bytes and there are 
				// 4 bytes per DWORD.
				int index = i * lockedRect.Pitch / 4+ j;

				// get current color of quad
				D3DXCOLOR c(imageData[index]);

				// shade current quad
				if (i<63&&j<63)
				{
					c *= computeShade(i, j, directionToLight);
				}
				
				 
				// save shaded color
				imageData[index] = (D3DCOLOR)c;
				 
			}
			 
		}

		_tex->UnlockRect(0);

		return true;
	}

	bool Terrain::loadTexture(TSTRING fileName)
	{
		int hr;
		hr = D3DXCreateTextureFromFile(_device, fileName.c_str(), &_tex);
		if (FAILED(hr)) {
			::MessageBox(0, _T("loadTexture - FAILED"), 0, 0);
			return false;
		}
		return true;
	}

	bool Terrain::buideVertex()
	{
		int hr=_device->CreateVertexBuffer(_numVertices * sizeof(TerrainVertex), D3DUSAGE_WRITEONLY, TerrainVertex::FVF, D3DPOOL_MANAGED, &_vertexBuffer, 0);
		if (FAILED(hr))
		{
			::MessageBox(0, _T("buideVertex CreateVertexBuffer() - FAILED"), 0, 0);
			return false;
		}
		int startx = -_xlength/2, startz = _zlength/2;
		int index = 0;
		float du = 1.0f / _numCellsPerRow;
		float dv = 1.0f / _numCellsPerCol;
		/*du = 1;
		dv = 1;*/
		TerrainVertex* vertexes;
		_vertexBuffer->Lock(0, 0, (void **)&vertexes, 0);
		for (int j=0;j<_numVersPerCol;j++)
		{
			int x = startx;
			for (int i=0;i<_numVersPreRow;i++)
			{
				vertexes[index] = TerrainVertex(x, _heightMap[index],startz, i*du,j*dv);
				x += _cellSpacing;
				index++;
			}
			startz -= _cellSpacing;
		}
		_vertexBuffer->Unlock();
		return true;
	}

	bool Terrain::buideIndex()
	{
		int hr = _device->CreateIndexBuffer(_numTriangles*3 * sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&_indexBuffer,0);
		if (FAILED(hr))
		{
			::MessageBox(0, _T("buideIndex CreateIndexBuffer() - FAILED"), 0, 0);
			return false;
		}
		WORD * indexes;
		_indexBuffer->Lock(0, 0, (void **)&indexes, 0);
		int baseIndex = 0;
		for (int i = 0; i < _numCellsPerCol; i++)
		{
			for (int j = 0; j< _numCellsPerRow; j++)
			{
				indexes[baseIndex] = i*_numVersPreRow + j;
				indexes[baseIndex + 1] = indexes[baseIndex] + 1;
				indexes[baseIndex + 2] = indexes[baseIndex] + _numVersPreRow;

				indexes[baseIndex + 3] = indexes[baseIndex + 2];
				indexes[baseIndex + 4] = indexes[baseIndex + 1];
				indexes[baseIndex + 5] = indexes[baseIndex + 3]+1;
				baseIndex += 6;
			}
		}
		_indexBuffer->Unlock();
		return true;
	}

}