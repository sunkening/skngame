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
	vertexes[0] = Vertex(0, 0, 0); //vertexes[0].color = D3DUtil::BLUE;
	vertexes[1] = Vertex(0, -3, 3);// vertexes[1].color = D3DUtil::CYAN;
	vertexes[2] = Vertex(3, -3, 0); //vertexes[2].color = D3DUtil::RED;
	vertexes[3] = Vertex(0, -3, -3);// vertexes[3].color = D3DUtil::GREEN;
	vertexes[4] = Vertex(-3, -3, 0);// vertexes[4].color = D3DUtil::YELLOW;
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
	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
//	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,5,0,4);

	device->EndScene();
	device->Present(0, 0, 0, 0);
}

bool GameTest2::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	int hr = d3dUtil->device->CreateVertexBuffer(12 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	Vertex* v;
	vertexBuffer->Lock(0, 0, (void **)&v, D3DLOCK_DISCARD);
	v[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
	v[1] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[2] = Vertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

	// left face
	v[3] = Vertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0.0f);
	v[4] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[5] = Vertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

	// right face
	v[6] = Vertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
	v[7] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[8] = Vertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0.0f);

	// back face
	v[9] = Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	v[10] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	vertexBuffer->Unlock();


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
	D3DXMATRIX   view;
	D3DXMatrixLookAtLH(&view, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &view);
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//device->SetRenderState(D3DRS_LIGHTING, false);//默认是启用的
	D3DMATERIAL9 material=D3DUtil::InitMaterial(D3DUtil::WHITE,0.2f,1);
	device->SetMaterial(&material);
	D3DXVECTOR3 lightdirecton(-1,0,0);
	D3DXVECTOR3 lightPosition(2, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::WHITE);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	//device->LightEnable(1, true);

	device->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	 device->SetRenderState(D3DRS_SPECULARENABLE, true);
	return true;
}

void GameTest2::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX ry, positon;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, -1, -2);
	device->SetTransform(D3DTS_WORLD, &(ry*positon));
	device->SetTransform(D3DTS_WORLD, &(ry*positon));
	device->BeginScene();
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	device->SetFVF(Vertex::FVF);
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0,4);

	device->EndScene();
	device->Present(0, 0, 0, 0);
}

bool GameTest3::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	int hr = d3dUtil->device->CreateVertexBuffer(12 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	Vertex* vertexes;
	vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = Vertex(0, 0, 0, 0, 1, 0);  vertexes[0].setTex(0.5f,0.0f);
	vertexes[1] = Vertex(0, -3, 3,0,-3, 3); vertexes[1].setTex(0.0f, 1.0f);
	vertexes[2] = Vertex(3, -3, 0,3, -3, 0); vertexes[2].setTex(0.33f, 1.0f);
	vertexes[3] = Vertex(0, -3, -3,0, -3, -3); vertexes[3].setTex(0.66f, 1.0f);
	vertexes[4] = Vertex(-3, -3, 0, - 3, -3, 0); vertexes[4].setTex(1.0f, 1.0f);
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
	D3DXMATRIX   view;
	D3DXMatrixLookAtLH(&view, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &view);
	
	D3DMATERIAL9 material = D3DUtil::InitMaterial(D3DUtil::WHITE, 0.3f, 1);
	material.Diffuse.a = 0.5f;
	device->SetMaterial(&material);
	IDirect3DTexture9 *texture=d3dUtil->LoadTexture(TEXT("res/texture/wall.png"));
	device->SetTexture(0,texture);
	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	device->LightEnable(1, true);
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//device->SetRenderState(D3DRS_LIGHTING, false);//默认是启用的
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// use alpha in material's diffuse component for alpha
//	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	// set blending factors so that alpha component determines transparency
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	return true;
}

void GameTest3::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX ry, positon, positon2;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, 1, 2);
	device->SetTransform(D3DTS_WORLD, &(ry*positon));
 
	device->BeginScene();
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(Vertex::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMatrixTranslation(&positon2, 1, 0, -1);
	device->SetTransform(D3DTS_WORLD, &(ry*positon*positon2));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}

const int GameTest4::numSub = 2;

bool GameTest4::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	

	int hr = D3DXCreateMeshFVF(4, 5, D3DXMESH_MANAGED, Vertex::FVF, device, &mesh);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("D3DXCreateMeshFVF() - FAILED"), 0, 0);
		return false;
	}
	
	Vertex* vertexes;
	mesh->LockVertexBuffer(0, (void **)&vertexes);
	//vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = Vertex(0, 0, 0, 0, 1, 0);  vertexes[0].setTex(0.5f, 0.0f);
	vertexes[1] = Vertex(0, -3, 3, 0, -3, 3); vertexes[1].setTex(0.0f, 1.0f);
	vertexes[2] = Vertex(3, -3, 0, 3, -3, 0); vertexes[2].setTex(0.33f, 1.0f);
	vertexes[3] = Vertex(0, -3, -3, 0, -3, -3); vertexes[3].setTex(0.66f, 1.0f);
	vertexes[4] = Vertex(-3, -3, 0, -3, -3, 0); vertexes[4].setTex(1.0f, 1.0f);
	mesh->UnlockVertexBuffer();
	 
	WORD * indexes;
	mesh->LockIndexBuffer(0, (void **)&indexes);
	//indexBuffer->Lock(0, 0, (void **)&indexes, D3DLOCK_DISCARD);
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
	mesh->UnlockIndexBuffer();
	DWORD* attributeBuffer;
	mesh->LockAttributeBuffer(0, &attributeBuffer);
	attributeBuffer[0] = 0;
	attributeBuffer[1] = 0;
	attributeBuffer[2] = 1;
	attributeBuffer[3] = 1;
	mesh->UnlockAttributeBuffer();
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
	D3DXMATRIX   view;
	D3DXMatrixLookAtLH(&view, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &view);

	D3DMATERIAL9 material = D3DUtil::InitMaterial(D3DUtil::WHITE, 0.5f, 1);
	material.Diffuse.a = 0.5f;
	device->SetMaterial(&material);
	textures[0]=d3dUtil->LoadTexture(TEXT("res/texture/wall.png"));
	textures[1] = d3dUtil->LoadTexture(TEXT("res/texture/wall2.png"));
	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	device->LightEnable(1, true);
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//device->SetRenderState(D3DRS_LIGHTING, false);//默认是启用的
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// use alpha in material's diffuse component for alpha
	//	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//透明度来源
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	// set blending factors so that alpha component determines transparency
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//混合因子
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//混合因子
	return true;
}

void GameTest4::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX ry, positon, positon2;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, 1, 2);
	device->SetTransform(D3DTS_WORLD, &(ry*positon));

	device->BeginScene();
	for (int i=0;i<2;i++)
	{
		device->SetTexture(0,textures[i]);
			mesh->DrawSubset(i);
	}
	D3DXMatrixTranslation(&positon2, 1, 0, -1);
	device->SetTransform(D3DTS_WORLD, &(ry*positon*positon2));
	for (int i = 0; i < 2; i++)
	{
		if (i == 1)
		{
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		}
		device->SetTexture(0, textures[i]);
		mesh->DrawSubset(i);
	}
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}


bool GameTest5::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	
	ID3DXBuffer * adjBuffer;
	ID3DXBuffer * materialBuffer;
	DWORD mtrlNum;
	int hr = D3DXLoadMeshFromX(TEXT("res/xfile/bigship1.x"),D3DXMESH_MANAGED,device,&adjBuffer,&materialBuffer,0,&mtrlNum,&mesh);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("D3DXLoadMeshFromX() - FAILED"), 0, 0);
		return false;
	}
	if (materialBuffer!=0 && mtrlNum!=0) {
		D3DXMATERIAL * mtrls= (D3DXMATERIAL *)materialBuffer->GetBufferPointer();
		for (int i = 0; i < mtrlNum;i++) {
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			materials.push_back(mtrls[i].MatD3D);
			if (mtrls[i].pTextureFilename!=0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(device,(PTCHAR)mtrls[i].pTextureFilename,&tex);
				textures.push_back(tex);
			}
			else {
				textures.push_back(0);
			}
		}
		materialBuffer->Release();
	}

	D3DXMATRIX   proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)800 / (float)600,
		1.0f,
		1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);
	D3DXVECTOR3 positon(0.0f, 0.0f, -25.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX   view;
	D3DXMatrixLookAtLH(&view, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &view);

	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	device->LightEnable(1, true);
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//device->SetRenderState(D3DRS_LIGHTING, false);//默认是启用的
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// use alpha in material's diffuse component for alpha
	//	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//透明度来源
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	// set blending factors so that alpha component determines transparency
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//混合因子
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//混合因子
	return true;
}

void GameTest5::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX ry, positon, positon2;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, 1, 2);
	device->SetTransform(D3DTS_WORLD, &(ry*positon));

	device->BeginScene();
	for (int i = 0; i < materials.size(); i++)
	{
		device->SetMaterial(&materials[i]);
		device->SetTexture(0, textures[i]);
		mesh->DrawSubset(i);
	}
	 
	device->EndScene();
	device->Present(0, 0, 0, 0);
}