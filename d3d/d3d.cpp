// d3d.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "d3d.h"
#include <string>
#include<d3d9.h>
#include<d3dx>
#include "d3dUtility.h"
#include <iostream>
using namespace std;
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
HWND hWnd;
IDirect3DDevice9* device;
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
IDirect3D9 * _d3d9;
// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID Cleanup();
int initd3d();
void gamemain(float timeDelta);
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;
	

		// 初始化全局字符串
	/*LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_D3D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);*/
	// Register the window class.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		_T("Direct3D Tutorial"), NULL };

	RegisterClassEx( &wc );

	// Create the application's window.
	 hWnd = CreateWindow( _T("Direct3D Tutorial"), _T("Direct3D Tutorial 01: CreateDevice"), 
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		GetDesktopWindow(), NULL, wc.hInstance, NULL );
	 ShowWindow(hWnd, nCmdShow);
	 UpdateWindow(hWnd);
/*
	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}*/
	 initd3d();
	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3D));
	float lasttime=timeGetTime();
	// 主消息循环:
	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		float currtime=timeGetTime();
		float timeDelta=(currtime-lasttime)*0.001f;
		gamemain(timeDelta);
	}
	 
	Cleanup();
	return (int) msg.wParam;
}
void gamemain(float timeDelta){
	device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	device->BeginScene();
	ID3DXMesh* mesh=0;
	D3DXCreateTeapot(device,&mesh,0);
	mesh->DrawSubset(0);
	// Rendering of scene objects happens here

	// End the scene
	device->EndScene();
	device->Present( NULL, NULL, NULL, NULL );



}
int initd3d(){
	_d3d9=Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps);
	int vp=0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp=D3DCREATE_HARDWARE_VERTEXPROCESSING;
		cout<<"硬件顶点运算"<<endl;
	}else{
		vp= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		cout<<"软件顶点运算"<<endl;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	/*d3dpp.BackBufferWidth=800;
	d3dpp.BackBufferHeight=600;
	d3dpp.BackBufferFormat=D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount=1;
	d3dpp.MultiSampleType=D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality=0;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow=hWnd;
	d3dpp.Windowed=false;
	d3dpp.EnableAutoDepthStencil=true;
	d3dpp.AutoDepthStencilFormat=D3DFMT_D24S8;
	d3dpp.Flags=0;
	d3dpp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;*/
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	 device=0;
	HRESULT hr;
	hr=_d3d9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,vp,&d3dpp,&device);

	if  ( FAILED(hr) )
	{
		cout<<"创建d3d失败"<<endl;
		return 0;
	}
	return 1;
}
 
 
//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	 
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
VOID cleanup()
{
	if( device != NULL)
		device->Release();
	if( _d3d9 != NULL)
		_d3d9->Release();
}