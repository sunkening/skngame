#include <windows.h>
#include"../skn3d.h"
using namespace skn_d3d;
#include "GameTest1.h"
bool GameTest1::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	int hr = d3dUtil->device->CreateVertexBuffer(5 * sizeof(ColorVertex), D3DUSAGE_WRITEONLY, ColorVertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	ColorVertex* vertexes;
	vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = ColorVertex(0, 0, 0); vertexes[0].color = D3DUtil::BLUE;
	vertexes[1] = ColorVertex(0, -3, 3); vertexes[1].color = D3DUtil::CYAN;
	vertexes[2] = ColorVertex(3, -3, 0); vertexes[2].color = D3DUtil::RED;
	vertexes[3] = ColorVertex(0, -3, -3); vertexes[3].color = D3DUtil::GREEN;
	vertexes[4] = ColorVertex(-3, -3, 0); vertexes[4].color = D3DUtil::YELLOW;
	vertexes[0]._u = 0; vertexes[0]._v = 0;
	vertexes[1]._u = 0; vertexes[0]._v =1;
	vertexes[2]._u = 1; vertexes[0]._v = 1;
	vertexes[3]._u = 0; vertexes[0]._v = 1;
	vertexes[4]._u = 1; vertexes[0]._v = 1;
	vertexBuffer->Unlock();

	hr = d3dUtil->device->CreateIndexBuffer(12 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateIndexBuffer() - FAILED"), 0, 0);
		return false;
	}
	IDirect3DTexture9* shadetex;
	D3DXCreateTextureFromFile(device, TEXT("res/texture/toonshade.bmp"), &shadetex);
	device->SetTexture(0, shadetex);
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
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(ColorVertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(ColorVertex::FVF);
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
	D3DXVECTOR3 positon(0.0f, 100.0f, -25.0f);
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
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);

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
	//terrain->draw(0, 0, 0, false);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}

//terrain
bool GameTest6::setup()
{
	TheCamera.setCameraType(skn_d3d::Camera::LANDOBJECT) ;
	IDirect3DDevice9* device = d3dUtil->device;
	terrain = new skn_d3d::Terrain(device,"res/texture/coastMountain64.raw", 64, 64, 10, 0.5f);
	TSTRING texname = TEXT("res/texture/wall.png");
	terrain->loadTexture(texname);
	//D3DXVECTOR3 lightDirection(-1,0,0);
	//terrain->lightTerrain(&lightDirection);
	snow = new skn_d3d::Snow(10000);
	snow->init(device, TEXT("res/texture/snowflake.dds"));
	D3DXMATRIX   proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 90 - degree
		(float)800 / (float)600,
		1.0f,
		1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);
	/*D3DXVECTOR3 positon(0.0f, 200.0f, -450.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX   view;
	D3DXMatrixLookAtLH(&view, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &view);*/

	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	//device->LightEnable(1, true);
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

void GameTest6::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
 
		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			TheCamera.walk(100.0f * timeDelta);

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			TheCamera.walk(-100.0f * timeDelta);

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			TheCamera.yaw(-1.0f * timeDelta);

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			TheCamera.yaw(1.0f * timeDelta);

		if (::GetAsyncKeyState('N') & 0x8000f)
			TheCamera.strafe(-100.0f * timeDelta);

		if (::GetAsyncKeyState('M') & 0x8000f)
			TheCamera.strafe(100.0f * timeDelta);

		if (::GetAsyncKeyState('W') & 0x8000f)
			TheCamera.pitch(1.0f * timeDelta);

		if (::GetAsyncKeyState('S') & 0x8000f)
			TheCamera.pitch(-1.0f * timeDelta);
			if (::GetAsyncKeyState('Q') & 0x8000f)
				TheCamera.fly(100.0f * timeDelta);
			if (::GetAsyncKeyState('A') & 0x8000f)
				TheCamera.fly(-100.0f * timeDelta);
		D3DXVECTOR3 pos;
		TheCamera.getPosition(&pos);
		float height = terrain->getHeight(pos.x, pos.z);
		
		pos.y = height + 10.0f; // add height because we're standing up
		TheCamera.setPosition(&pos);

		D3DXMATRIX V;
		TheCamera.getViewMatrix(&V);
		device->SetTransform(D3DTS_VIEW, &V);
		snow->update(timeDelta);
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);
 
	
	device->BeginScene();
	terrain->draw(0,0,0,false);
	snow->render();
	device->EndScene();
	device->Present(0, 0, 0, 0);
}

//ray
bool GameTest7::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	D3DXCreateTeapot(device, &Teapot, 0);
	BYTE* v_byte = 0;
	Teapot->LockVertexBuffer(0, (void**)&v_byte);

	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v_byte,
		Teapot->GetNumVertices(),
		D3DXGetFVFVertexSize(Teapot->GetFVF()),
		&BSphere._center,
		&BSphere._radius);
	Teapot->UnlockVertexBuffer();
	//
	// Build a sphere mesh that describes the teapot's bounding sphere.
	//
	D3DXCreateSphere(device, BSphere._radius, 20, 20, &Sphere, 0);
	//
	// Set light.
	//



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

	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	device->LightEnable(1, true);
	device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	const D3DMATERIAL9 YELLOW_MTRL = D3DUtil::InitMaterial(D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL = D3DUtil::InitMaterial(D3DUtil::BLUE, D3DUtil::BLUE, D3DUtil::BLUE, D3DUtil::BLACK, 2.0f);
	return true;
}

void GameTest7::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	POINT point;
	GetCursorPos(&point);//获取的是在整个屏幕的位置
	ScreenToClient(d3dUtil->hwnd, &point);
	cout << point.x<<"    "<< point.y << endl;
	//point.y += 31;
	Ray ray = D3DUtil::CalcPickingRay(device, point.x, point.y);
 
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);

	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);

	D3DUtil::TransformRay(&ray, &viewInverse);
	bool pick = false;
	// test for a hit
	if (D3DUtil::RaySphereIntTest(&ray, &BSphere))
		pick = true;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);
 
	// transfrom the bounding sphere to match the teapots position in the
	// world.
  
	device->BeginScene();
	// Render the teapot.
	D3DXMATRIX ry, positon;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 3, 3, 0);
	BSphere._center.x = 3;
	BSphere._center.y = 3;
	BSphere._center.z = 0;
	device->SetTransform(D3DTS_WORLD, &(ry*positon));
	D3DMATERIAL9 YELLOW_MTRL = D3DUtil::InitMaterial(D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::BLACK, 2.0f);
	device->SetMaterial(&YELLOW_MTRL);
	Teapot->DrawSubset(0);
	// Render the bounding sphere with alpha blending so we can see 
	// through it.
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	D3DMATERIAL9 blue = D3DUtil::InitMaterial(D3DUtil::BLUE, D3DUtil::BLUE, D3DUtil::BLUE, D3DUtil::BLACK, 2.0f);
	blue.Diffuse.a = 0.25f; // 25% opacity
	device->SetMaterial(&blue);
	if (pick)
	{
		Sphere->DrawSubset(0);
	}
	
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}


bool GameTest8::setup()
{
	device = d3dUtil->device;
	D3DXCreateTeapot(device, &Teapot, 0);
	//initDiffuseShader();
	//initBlueShader();
	initToonShader();


	D3DXMATRIX   proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)D3DUtil::screenWidth / (float)D3DUtil::screenHeight,
		1.0f,
		1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);
	D3DXVECTOR3 positon(0.0f, 0.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX   v;
	D3DXMatrixLookAtLH(&v, &positon, &target, &up);
	device->SetTransform(D3DTS_VIEW, &v);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
 
	return true;
}

void GameTest8::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	D3DXMATRIX ry, positon;
	static float y = 0;
	y += timeDelta;
	if (y > 6.28f)
	{
		y = 0;
	}
	D3DXMatrixRotationY(&ry, y);
	D3DXMatrixTranslation(&positon, 0, -1, 0);
	device->SetTransform(D3DTS_WORLD, &(ry*positon));
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);
	device->BeginScene();
	updateToonShader();
	//updateDiffuseShader();
	//updateBlueShader();
	
	Teapot->DrawSubset(0);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}

bool GameTest8::initBlueShader()
{
	IDirect3DDevice9* device = d3dUtil->device;
	ID3DXBuffer* shader = 0;
	ID3DXBuffer* errorBuffer = 0;
	HRESULT hr = 0;
	hr = D3DXCompileShaderFromFile(
		TEXT("res/shader/transform.txt"),
		0,
		0,
		"Main",  // entry point function name
		"vs_1_1",// shader version to compile to
		D3DXSHADER_DEBUG,
		&shader,
		&errorBuffer,
		&ConstantTable);
	// output any error messages
	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		D3DUtil::Release<ID3DXBuffer*>(errorBuffer);
	}
	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("D3DXCreateEffectFromFile() - FAILED"), 0, 0);
		return false;
	}

	hr = device->CreateVertexShader(
		(DWORD*)shader->GetBufferPointer(),
		&VertexShader);

	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("CreateVertexShader - FAILED"), 0, 0);
		return false;
	}

	D3DUtil::Release<ID3DXBuffer*>(shader);

	// 
	// Get Handles.
	//

	TransformViewProjHandle = ConstantTable->GetConstantByName(0, "ViewProjMatrix");

	//
	// Set shader constants:
	//

	ConstantTable->SetDefaults(device);
}

void GameTest8::updateBlueShader()
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->SetVertexShader(VertexShader);

	//direct9 从物体到视口有三个变换 世界变换，取景变换（相机变换），投影变换（透视变换）
	//获取世界变换矩阵
	D3DXMATRIX world;
	device->GetTransform(D3DTS_WORLD, &world);
	//获取取景变换矩阵
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	//获取投影变换矩阵
	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);
	ConstantTable->SetMatrix(
		device,
		TransformViewProjHandle,
		&(world*view*proj));
}

bool GameTest8::initDiffuseShader()
{
	IDirect3DDevice9* device = d3dUtil->device;
	ID3DXBuffer* shader = 0;
	ID3DXBuffer* errorBuffer = 0;
	HRESULT hr = 0;
	 
	hr = D3DXCompileShaderFromFile(
		TEXT("res/shader/diffuse.txt"),
		0,
		0,
		"Main",  // entry point function name
		"vs_1_1",// shader version to compile to
		D3DXSHADER_DEBUG,//  | D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY
		&shader,
		&errorBuffer,
		&ConstantTable);
	// output any error messages
	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		cout <<(char*) errorBuffer->GetBufferPointer() << endl;
		D3DUtil::Release<ID3DXBuffer*>(errorBuffer);
	}
	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("D3DXCreateEffectFromFile() - FAILED"), 0, 0);
		return false;
	}

	hr = device->CreateVertexShader(
		(DWORD*)shader->GetBufferPointer(),
		&VertexShader);

	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("CreateVertexShader - FAILED"), 0, 0);
		return false;
	}

	D3DUtil::Release<ID3DXBuffer*>(shader);
	D3DXHANDLE ViewMatrixHandle = ConstantTable->GetConstantByName(0, "ViewMatrix");
	D3DXHANDLE ViewProjMatrixHandle = ConstantTable->GetConstantByName(0, "ViewProjMatrix");
	D3DXHANDLE AmbientMtrlHandle = ConstantTable->GetConstantByName(0, "AmbientMtrl");
	D3DXHANDLE DiffuseMtrlHandle = ConstantTable->GetConstantByName(0, "DiffuseMtrl");
	D3DXHANDLE LightDirHandle = ConstantTable->GetConstantByName(0, "LightDirection");
	//
	// Set shader constants:
	//

	// Light direction:
	D3DXVECTOR4 directionToLight(-0.57f, 0.57f, -0.57f, 0.0f);
	ConstantTable->SetVector(device, LightDirHandle, &directionToLight);

	// Materials:
	D3DXVECTOR4 ambientMtrl(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVECTOR4 diffuseMtrl(0.0f, 0.0f, 1.0f, 1.0f);

	ConstantTable->SetVector(device, AmbientMtrlHandle, &ambientMtrl);
	ConstantTable->SetVector(device, DiffuseMtrlHandle, &diffuseMtrl);
	ConstantTable->SetDefaults(device);

	return true;
}

void GameTest8::updateDiffuseShader()
{
	D3DXHANDLE ViewMatrixHandle = ConstantTable->GetConstantByName(0, "ViewMatrix");
	D3DXHANDLE ViewProjMatrixHandle = ConstantTable->GetConstantByName(0, "ViewProjMatrix");
	D3DXHANDLE LightDirHandle = ConstantTable->GetConstantByName(0, "LightDirection");
	D3DXVECTOR4 directionToLight(-0.57f, 0.57f, -0.57f, 0.0f);
	 
 
	//获取世界变换矩阵
	D3DXMATRIX world;
	device->GetTransform(D3DTS_WORLD, &world);
	//获取取景变换矩阵
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	D3DXVec4Transform(&directionToLight, &directionToLight, &view);
	//获取投影变换矩阵
	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);
	ConstantTable->SetMatrix(device, ViewMatrixHandle, &view);
	D3DXMATRIX ViewProj = view * proj;
	ConstantTable->SetMatrix(device, ViewProjMatrixHandle, &ViewProj);
	ConstantTable->SetVector(device, LightDirHandle, &directionToLight);
	device->SetVertexShader(VertexShader);
	
}

bool GameTest8::initToonShader()
{
	IDirect3DDevice9* device = d3dUtil->device;
	ID3DXBuffer* shader = 0;
	ID3DXBuffer* errorBuffer = 0;
	HRESULT hr = 0;

	hr = D3DXCompileShaderFromFile(
		TEXT("res/shader/toon.txt"),
		0,
		0,
		"Main",  // entry point function name
		"vs_1_1",// shader version to compile to
		D3DXSHADER_DEBUG,//  | D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY
		&shader,
		&errorBuffer,
		&ConstantTable);
	// output any error messages
	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		cout << (char*)errorBuffer->GetBufferPointer() << endl;
		D3DUtil::Release<ID3DXBuffer*>(errorBuffer);
	}
	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("D3DXCreateEffectFromFile() - FAILED"), 0, 0);
		return false;
	}

	hr = device->CreateVertexShader(
		(DWORD*)shader->GetBufferPointer(),
		&VertexShader);

	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("CreateVertexShader - FAILED"), 0, 0);
		return false;
	}
	D3DUtil::Release<ID3DXBuffer*>(shader);
	IDirect3DTexture9* shadetex;
	D3DXCreateTextureFromFile(device, TEXT("res/texture/toonshade.bmp"), &shadetex);
	device->SetTexture(0, shadetex);
	D3DMATERIAL9 YELLOW_MTRL = D3DUtil::InitMaterial(D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::YELLOW, D3DUtil::BLACK, 2.0f);
	device->SetMaterial(&YELLOW_MTRL);
	//device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	//device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	device->SetRenderState(D3DRS_LIGHTING, false);
	D3DXVECTOR3 lightdirecton(-1, 0, 0);
	D3DXVECTOR3 lightPosition(5, 0, 0);
	D3DLIGHT9 light0 = D3DUtil::InitDirectionLight(lightdirecton, D3DUtil::WHITE);
	D3DLIGHT9 light1 = D3DUtil::InitPointLight(lightPosition, D3DUtil::RED);
	device->SetLight(0, &light0);
	device->SetLight(1, &light1);
	device->LightEnable(0, true);
	device->LightEnable(1, true);
	//device->SetRenderState(D3DRS_LIGHTING, false);
	/*device->SetRenderState(D3DRS_LIGHTING, true);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);*/
	ConstantTable->SetDefaults(device);
	return true;
}

void GameTest8::updateToonShader()
{
	D3DXMATRIX world;
	device->GetTransform(D3DTS_WORLD, &world);
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXHANDLE WorldViewHandle = ConstantTable->GetConstantByName(0, "WorldViewMatrix");
	D3DXHANDLE WorldViewProjHandle = ConstantTable->GetConstantByName(0, "WorldViewProjMatrix");
	D3DXHANDLE LightDirHandle = ConstantTable->GetConstantByName(0, "LightDirection");
	D3DXMATRIX  WorldView = world * view;
	D3DXMATRIX WorldViewProj = world * view * proj;
	D3DXVECTOR4 directionToLight(-0.57f, 0.57f, -0.57f, 0.0f);
	//D3DXVec4Transform(&directionToLight, &directionToLight, &WorldView);
	ConstantTable->SetMatrix(
		device,
		WorldViewHandle,
		&WorldView);
	ConstantTable->SetMatrix(
		device,
		WorldViewProjHandle,
		&WorldViewProj);
	ConstantTable->SetVector(
		device,
		LightDirHandle,
		&directionToLight);
	//ConstantTable->SetVector(
	//	device,
	//	ColorHandle,
	//	&MeshColors[i]);
	device->SetVertexShader(VertexShader);
}


bool GameTest9::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	int hr = d3dUtil->device->CreateVertexBuffer(5 * sizeof(MultiTexVertex), D3DUSAGE_WRITEONLY, MultiTexVertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	MultiTexVertex* vertexes;
	vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = MultiTexVertex(0, 0, 0,  
		0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	vertexes[1] = MultiTexVertex(0, -3, 3,
		0.0f,1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertexes[2] = MultiTexVertex(3, -3, 0, 
		0.33f, 1.0f, 0.33f, 1.0f, 0.33f, 1.0f);
	vertexes[3] = MultiTexVertex(0, -3, -3,
		0.66f,1.0f, 0.66f, 1.0f, 0.66f, 1.0f);
	vertexes[4] = MultiTexVertex(-3, -3, 0,
		1.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
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
	IDirect3DTexture9 *texture = d3dUtil->LoadTexture(TEXT("res/texture/wall.png"));
	device->SetTexture(0, texture);
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
	ID3DXBuffer* shader = 0;
	ID3DXBuffer* errorBuffer = 0;

	hr = D3DXCompileShaderFromFile(
		TEXT("res/shader/ps_multitex.txt"),
		0,
		0,
		"Main", // entry point function name
		"ps_2_0",
		D3DXSHADER_DEBUG,
		&shader,
		&errorBuffer,
		&ConstantTable);

	// output any error messages
	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		D3DUtil::Release<ID3DXBuffer*>(errorBuffer);
	}

	if (FAILED(hr))
	{
		::MessageBoxA(0, "D3DXCompileShaderFromFile() - FAILED", 0, 0);
		return false;
	}

	//
	// Create Pixel Shader
	//
	hr = device->CreatePixelShader(
		(DWORD*)shader->GetBufferPointer(),
		&PixelShader);

	if (FAILED(hr))
	{
		::MessageBoxA(0, "CreateVertexShader - FAILED", 0, 0);
		return false;
	}

	D3DUtil::Release<ID3DXBuffer*>(shader);

	//
	// Load textures.
	//
	IDirect3DTexture9 *BaseTex = d3dUtil->LoadTexture(TEXT("res/texture/wall.png"));
	IDirect3DTexture9 *SpotLightTex = d3dUtil->LoadTexture(TEXT("res/texture/spotlight.bmp"));
	IDirect3DTexture9 *StringTex = d3dUtil->LoadTexture(TEXT("res/texture/text.bmp"));
	D3DXHANDLE BaseTexHandle = 0;
	D3DXHANDLE SpotLightTexHandle = 0;
	D3DXHANDLE StringTexHandle = 0;
	BaseTexHandle = ConstantTable->GetConstantByName(0, "BaseTex");
	SpotLightTexHandle = ConstantTable->GetConstantByName(0, "SpotLightTex");
	StringTexHandle = ConstantTable->GetConstantByName(0, "StringTex");
	D3DXCONSTANT_DESC BaseTexDesc;
	D3DXCONSTANT_DESC SpotLightTexDesc;
	D3DXCONSTANT_DESC StringTexDesc;
	UINT count;

	ConstantTable->GetConstantDesc(BaseTexHandle, &BaseTexDesc, &count);
	ConstantTable->GetConstantDesc(SpotLightTexHandle, &SpotLightTexDesc, &count);
	ConstantTable->GetConstantDesc(StringTexHandle, &StringTexDesc, &count);
	// base tex
	device->SetTexture(BaseTexDesc.RegisterIndex, BaseTex);
	device->SetSamplerState(BaseTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(BaseTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(BaseTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// spotlight tex
	device->SetTexture(SpotLightTexDesc.RegisterIndex, SpotLightTex);
	device->SetSamplerState(SpotLightTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(SpotLightTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(SpotLightTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// string tex
	device->SetTexture(StringTexDesc.RegisterIndex, StringTex);
	device->SetSamplerState(StringTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(StringTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(StringTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	ConstantTable->SetDefaults(device);
	device->SetPixelShader(PixelShader);
	return true;
}

void GameTest9::play(float timeDelta)
{
	IDirect3DDevice9* device = d3dUtil->device;
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);

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
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(MultiTexVertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(MultiTexVertex::FVF);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMatrixTranslation(&positon2, 1, 0, -1);
	device->SetTransform(D3DTS_WORLD, &(ry*positon*positon2));
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device->EndScene();
	device->Present(0, 0, 0, 0);
}

bool GameTest10::setup()
{
	IDirect3DDevice9* device = d3dUtil->device;
	D3DXCreateTeapot(device, &Teapot, 0);
	int hr = d3dUtil->device->CreateVertexBuffer(12 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);
	if (FAILED(hr))
	{
		::MessageBox(0, _T("CreateVertexBuffer() - FAILED"), 0, 0);
		return false;
	}
	Vertex* vertexes;
	vertexBuffer->Lock(0, 0, (void **)&vertexes, D3DLOCK_DISCARD);
	vertexes[0] = Vertex(0, 0, 0, 0, 1, 0);  vertexes[0].setTex(0.5f, 0.0f);
	vertexes[1] = Vertex(0, -3, 3, 0, -3, 3); vertexes[1].setTex(0.0f, 1.0f);
	vertexes[2] = Vertex(3, -3, 0, 3, -3, 0); vertexes[2].setTex(0.33f, 1.0f);
	vertexes[3] = Vertex(0, -3, -3, 0, -3, -3); vertexes[3].setTex(0.66f, 1.0f);
	vertexes[4] = Vertex(-3, -3, 0, -3, -3, 0); vertexes[4].setTex(1.0f, 1.0f);
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
	 
	ID3DXBuffer* errorBuffer = 0;
	hr = D3DXCreateEffectFromFile(
		device,
		TEXT("res/shader/light_tex.txt"),
		0,                // no preprocessor definitions
		0,                // no ID3DXInclude interface
		D3DXSHADER_DEBUG, // compile flags
		0,                // don't share parameters
		&LightTexEffect,
		&errorBuffer);
	// output any error messages
	if (errorBuffer)
	{
		::MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		D3DUtil::Release<ID3DXBuffer*>(errorBuffer);
	}

	if (FAILED(hr))
	{
		::MessageBoxA(0, "D3DXCreateEffectFromFile() - FAILED", 0, 0);
		return false;
	}
	IDirect3DTexture9 *texture = d3dUtil->LoadTexture(TEXT("res/texture/wall.png"));
	D3DXHANDLE TexHandle = LightTexEffect->GetParameterByName(0, "Tex");
	LightTexEffect->SetTexture(TexHandle, texture);
	return true;
}

void GameTest10::play(float timeDelta)
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
	D3DXHANDLE LightTexTechHandle = LightTexEffect->GetTechniqueByName("LightAndTexture");
	D3DXHANDLE WorldMatrixHandle = LightTexEffect->GetParameterByName(0, "WorldMatrix");
	D3DXHANDLE ViewMatrixHandle = LightTexEffect->GetParameterByName(0, "ViewMatrix");
	D3DXHANDLE ProjMatrixHandle = LightTexEffect->GetParameterByName(0, "ProjMatrix");
	D3DXMATRIX world;
	device->GetTransform(D3DTS_WORLD, &world);
	D3DXMATRIX view;
	device->GetTransform(D3DTS_VIEW, &view);
	D3DXMATRIX proj;
	device->GetTransform(D3DTS_PROJECTION, &proj);
 
	LightTexEffect->SetMatrix(WorldMatrixHandle, &world);
	LightTexEffect->SetMatrix(ViewMatrixHandle, &view);
	LightTexEffect->SetMatrix(ProjMatrixHandle, &proj);

	// set the technique to use
	LightTexEffect->SetTechnique(LightTexTechHandle);

	UINT numPasses = 0;
	LightTexEffect->Begin(&numPasses, 0);

 
		LightTexEffect->BeginPass(0);
		
		device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
		device->SetIndices(indexBuffer);
		device->SetFVF(Vertex::FVF);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
		
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		D3DXMatrixTranslation(&positon2, 1, 0, -1);
		device->SetTransform(D3DTS_WORLD, &(ry*positon*positon2));
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		LightTexEffect->EndPass();


		LightTexEffect->BeginPass(1);
		IDirect3DTexture9 *shadetex;
		D3DXHANDLE ShadeTexHandle = LightTexEffect->GetParameterByName(0, "ShadeTex");
		D3DXCreateTextureFromFile(device, TEXT("res/texture/toonshade.bmp"), &shadetex);
		LightTexEffect->SetTexture(ShadeTexHandle, shadetex);
		D3DXHANDLE ColorHandle = LightTexEffect->GetParameterByName(0, "Color");
		LightTexEffect->SetVector(ColorHandle, &D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f));
		D3DXHANDLE WorldViewHandle = LightTexEffect->GetParameterByName(0, "WorldViewMatrix");
		D3DXHANDLE WorldViewProjHandle = LightTexEffect->GetParameterByName(0, "WorldViewProjMatrix");
		D3DXHANDLE LightDirHandle = LightTexEffect->GetParameterByName(0, "LightDirection");
		D3DXMATRIX  WorldView = world * view;
		D3DXMATRIX WorldViewProj = world * view * proj;
		D3DXVECTOR4 directionToLight(-0.57f, 0.57f, -0.57f, 0.0f);
		//D3DXVec4Transform(&directionToLight, &directionToLight, &WorldView);
		LightTexEffect->SetMatrix(
			WorldViewHandle,
			&WorldView);
		LightTexEffect->SetMatrix(
			WorldViewProjHandle,
			&WorldViewProj);
		LightTexEffect->SetVector(
			LightDirHandle,
			&directionToLight);
		Teapot->DrawSubset(0);
		LightTexEffect->EndPass();
	LightTexEffect->End();


	
	device->EndScene();
	device->Present(0, 0, 0, 0);
}