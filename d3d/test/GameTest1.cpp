#include "StdAfx.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"../D3DUtil.h"
#include <iostream>
using namespace std;
#include "../GameMain.h"
#include "GameTest1.h"
using namespace skn_d3d;
bool GameTest1::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	int hr = d3dUtil->device->CreateVertexBuffer(5 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	Vertex* vertexes;
	vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = Vertex(0, 0, 0); vertexes[0].color = D3DUtil::BLUE;
	vertexes[1] = Vertex(0, -3, 3); vertexes[1].color = D3DUtil::CYAN;
	vertexes[2] = Vertex(3, -3, 0); vertexes[2].color = D3DUtil::RED;
	vertexes[3] = Vertex(0, -3, -3); vertexes[3].color = D3DUtil::GREEN;
	vertexes[4] = Vertex(-3, -3, 0); vertexes[4].color = D3DUtil::YELLOW;
	vertexBuffer->Unlock();

	hr = d3dUtil->device->CreateIndexBuffer(12 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateIndexBuffer() - FAILED"), 0, 0);
		return false;
	}
	WORD * indexes;
	indexBuffer->Lock(0, 0, (void **)&indexes, D3DLOCK_DISCARD);
	indexes[0] = 0;
	indexes[1] = 1;
	indexes[2] = 2;

	indexes[3] = 0;
	indexes[4] = 2;
	indexes[5] = 3;

	indexes[6] = 0;
	indexes[7] = 3;
	indexes[8] = 4;
	indexes[9] = 0;
	indexes[10] = 4;
	indexes[11] = 1;
	indexBuffer->Unlock();
	D3DXMATRIX   proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)800 / (float)600,
		1.0f,
		1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);
	D3DXVECTOR3 positon(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX   v;
	D3DXMatrixLookAtLH(&v, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &v);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	device->SetRenderState(D3DRS_LIGHTING, false);
	
	
	return true;
}

void GameTest1::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	D3DXMATRIX ry,positon;
	static float y = 0;
	y += timeDelta;
	if (y>6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, 1, 0);
	device->SetTransform(D3DTS_WORLD, & (ry*positon));

	device->BeginScene();
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(Vertex::FVF);
//	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,5,0,4);

	device->EndScene();
	device->Present(0, 0, 0, 0);
}
