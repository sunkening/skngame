#include "stdafx.h"


#include <string>
#include<d3d9.h>
#include<d3dx9.h>
#include"D3DUtil.h"
#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;
 
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

	int Terrain::getHeight(int row, int col)
	{
		return _heightMap[row*_numVersPreRow + col];
	}

	void Terrain::setHeight(int row, int col, int height)
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
			//_device->SetRenderState(D3DRS_LIGHTING, false);
			hr=_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numVertices, 0, _numTriangles);
			//_device->SetRenderState(D3DRS_LIGHTING, true);
			if (FAILED(hr))
			{
				::MessageBox(0, _T("computeIndices - FAILED"), 0, 0);
				::PostQuitMessage(0);
			}
			return true;
		}
		
		return false;
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