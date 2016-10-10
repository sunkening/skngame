// skngame.cpp : 定义控制台应用程序的入口点。
/////
#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#define INITGUID

#include <stdio.h>
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <tchar.h>
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;
#include<d3d9.h>
#include<d3dx9.h>
#include<IOSTREAM>
#include "D3DUtil.h"
#include "GameMain.h"
#include "test/GameTest1.h"
#include "d3dUtility.h"
#include "Camera.h"



using namespace skn_d3d;
//using namespace   sknd3d;
IDirect3DDevice9* Device = 0; 
IDirect3DVertexBuffer9* VB = 0;
IDirect3DVertexBuffer9* mirror=0;

IDirect3DIndexBuffer9*  IB = 0;
ID3DXMesh*   Teapot = 0;
D3DMATERIAL9 TeapotMtrl;
Camera TheCamera(Camera::LANDOBJECT);

ID3DXMesh* Objects[5] = {0, 0, 0, 0, 0};
 vector<D3DMATERIAL9>       Mtrls(0);
 vector<IDirect3DTexture9*> Textures(0);
D3DXMATRIX ObjWorldMatrices[5];
int Width=800;
int Height =600;
D3DXHANDLE ViewProjMatrixHandle = 0;
D3DXMATRIX   proj ;
ID3DXConstantTable* shadertable =0;
IDirect3DVertexShader9* toonshader = 0;

D3DXMATRIX WorldMatrix;
IDirect3DTexture9* tex[4]={0};
IDirect3DVertexBuffer9* Triangle = 0;
IDirect3DTexture9* mirror_t;
 
 
bool Setup()
{	
	ID3DXBuffer* shader =0;
	ID3DXBuffer* errorbuffer=0;
	HRESULT hr = 0;
	hr=D3DXCompileShaderFromFile(_T("shader.txt"),0,0,  "Main" ,  "vs_1_1" ,D3DXSHADER_DEBUG,
		&shader,&errorbuffer,&shadertable);
	if (errorbuffer)
	{
		cout<<(char*)errorbuffer->GetBufferPointer()<<endl;
		d3d::Release<ID3DXBuffer*>(errorbuffer);
	}

	if (FAILED(hr))
	{
		cout<<"D3DXCompileShaderFromFile failed"<<endl;
		return false;
	}
	
	hr= Device->CreateVertexShader((DWORD*)shader->GetBufferPointer(),&toonshader);
	if (FAILED(hr))
	{
		cout<<"CreateVertexShader failed"<<endl;
		return false;
	}
 
	ViewProjMatrixHandle=shadertable->GetConstantByName(0,"ViewProjMatrix");
	shadertable->SetDefaults(Device);
	 
 
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)Width / (float)Height,
		1.0f,
		1000.0f);

 
 
	
 

/*
Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true); 
*/

 
 
	D3DXCreateTeapot(Device, &Teapot, 0);
 
	return true;
} 
 
bool Display(float timeDelta)
{
 
	static float angle  = (3.0f * D3DX_PI) / 2.0f;
	static float height = 2.0f;

	 
	if( ::GetAsyncKeyState('W') & 0x8000f )
		TheCamera.walk(4.0f * timeDelta);

	if( ::GetAsyncKeyState('S') & 0x8000f )
		TheCamera.walk(-4.0f * timeDelta);

	if( ::GetAsyncKeyState('A') & 0x8000f )
		TheCamera.strafe(-4.0f * timeDelta);

	if( ::GetAsyncKeyState('D') & 0x8000f )
		TheCamera.strafe(4.0f * timeDelta);

	if( ::GetAsyncKeyState('R') & 0x8000f )
		TheCamera.fly(4.0f * timeDelta);

	if( ::GetAsyncKeyState('F') & 0x8000f )
	{
		TheCamera.fly(-4.0f * timeDelta);
		 
	}
	if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		TheCamera.pitch(1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		TheCamera.pitch(-1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		TheCamera.yaw(-1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		TheCamera.yaw(1.0f * timeDelta);

	if( ::GetAsyncKeyState('N') & 0x8000f )
		TheCamera.roll(1.0f * timeDelta);

	if( ::GetAsyncKeyState('M') & 0x8000f )
		TheCamera.roll(-1.0f * timeDelta);
 
	D3DXMATRIX V;
	TheCamera.getViewMatrix(&V);
	/*Device->SetTransform(D3DTS_PROJECTION, &proj);
	Device->SetTransform(D3DTS_VIEW, &V);*/

	D3DXMATRIX viewProj=proj*V;
	shadertable->SetMatrix(Device,ViewProjMatrixHandle,&viewProj);

 
	D3DXMATRIX w;
	D3DXMatrixTranslation(&w,0,0,2);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
	Device->BeginScene();
	 
	Device->SetTransform(D3DTS_WORLD, &w);
 
	// Device->SetVertexShader(toonshader);
	Teapot->DrawSubset(0); 
	
	cout << "dsfdsad" << endl;

	Device->EndScene();
	Device->Present(0, 0, 0, 0);
 
	return true;
}
void Cleanup()
{
	for(int i = 0; i < 5; i++)
		d3d::Release<ID3DXMesh*>(Objects[i]);
}
 
int _tmain(int ac,char *av[])

{

	HINSTANCE inst;
	inst=(HINSTANCE)GetModuleHandle(NULL);
	//_tWinMain(inst, 0,0, SW_SHOWNORMAL);
	GameMain *gamemain=new GameTest3;
	 D3DUtil d3dutil;
	 gamemain->setD3DUtil(&d3dutil);
	if (!d3dutil.InitD3D(inst,
		Width, Height, true, D3DDEVTYPE_HAL))
	{
		::MessageBox(0, _T("InitD3D() - FAILED"), 0, 0);
		return 0;
	}
	GameMain::EnterMsgLoop(gamemain);
//	Setup();
	//d3d::EnterMsgLoop( Display );

//	Cleanup();

	//Device->Release();
	return 1;


}
