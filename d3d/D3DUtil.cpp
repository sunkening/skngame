#include "stdafx.h"


#include <string>
#include<d3d9.h>
#include<d3dx9.h>
#include <iostream>
using namespace std;
#include "D3DUtil.h"
namespace skn_d3d {
	const D3DXCOLOR   D3DUtil::WHITE = D3DCOLOR_XRGB(255, 255, 255);
	const D3DXCOLOR   D3DUtil::BLACK = D3DCOLOR_XRGB(0, 0, 0);
	const D3DXCOLOR   D3DUtil::RED = D3DCOLOR_XRGB(255, 0, 0);
	const D3DXCOLOR   D3DUtil::GREEN = D3DCOLOR_XRGB(0, 255, 0);
	const D3DXCOLOR   D3DUtil::BLUE = D3DCOLOR_XRGB(0, 0, 255);
	const D3DXCOLOR   D3DUtil::YELLOW = D3DCOLOR_XRGB(255, 255, 0);
	const D3DXCOLOR   D3DUtil::CYAN = D3DCOLOR_XRGB(0, 255, 255);
	const D3DXCOLOR   D3DUtil::MAGENTA = D3DCOLOR_XRGB(255, 0, 255);
	//计算面的法线，定点为顺时针环绕
	void D3DUtil::ComputeNormal(D3DXVECTOR3 *p0, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *out)
	{
		D3DXVECTOR3 u = *p1 - *p0;
		D3DXVECTOR3 v = *p2 - *p0;
		D3DXVec3Cross(out, &u, &v);
		D3DXVec3Normalize(out, out);
	}

	D3DLIGHT9 D3DUtil::InitDirectionLight(D3DXVECTOR3 d, D3DXCOLOR color)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light,sizeof D3DLIGHT9);
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = color*0.4f;
		light.Diffuse = color;
		light.Specular = color*0.6f;
		light.Direction = d;
		return light;
	}

	D3DLIGHT9 D3DUtil::InitPointLight(D3DXVECTOR3 position, D3DXCOLOR color)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof D3DLIGHT9);
		light.Type = D3DLIGHT_POINT;
		light.Ambient = color * 0.3f;
		light.Diffuse = color;
		light.Specular = color * 0.9f;
		light.Position = position;
		light.Range = 1000.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 1.0f;
		light.Attenuation2 = 0.0f;
		return light;
	}

	D3DMATERIAL9 D3DUtil::InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p /*= 0.0f*/)
	{
		D3DMATERIAL9 m;
		ZeroMemory(&m,sizeof D3DMATERIAL9);
		m.Ambient = a;
		m.Diffuse = d;
		m.Emissive = e;
		m.Specular = s;
		m.Power = p;
		return m;
	}

	D3DMATERIAL9 D3DUtil::InitMaterial(D3DCOLOR c, float ambient, float s, float e)
	{
		D3DMATERIAL9 m;
		ZeroMemory(&m, sizeof D3DMATERIAL9);
		byte *b=(byte*) &c;
		int alph = b[3];
		int red = b[2];
		int green = b[1];
		int blue = b[0];
 
		D3DXCOLOR a(red/255, green/255, blue/255, alph/255);
		m.Ambient = a*ambient;
		m.Diffuse = a;
		m.Emissive = a*e;
		m.Specular = a*s;
		m.Power = 5.0f;
		return m;
	}

	IDirect3DTexture9* D3DUtil::LoadTexture(TCHAR * filename)
	{
		IDirect3DTexture9* t;
		D3DXCreateTextureFromFile(device,filename,&t);
		return t;
	}

	D3DUtil::D3DUtil()
	{
	}

bool D3DUtil::InitD3D(
		HINSTANCE hInstance,
		int width, int height,
		bool windowed,
		D3DDEVTYPE deviceType
		)
	{
		//
		// Create the main application window.
		//
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = 0;
		wc.lpszClassName = _T("Direct3D9App");

		if (!RegisterClass(&wc))
		{
			::MessageBox(0, _T("RegisterClass() - FAILED"), 0, 0);
			return false;
		}

		HWND hwnd = 0;
		hwnd = ::CreateWindow(_T("Direct3D9App"), _T("Direct3D9App"),
			WS_EX_TOPMOST,
			0, 0, width, height,
			0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

		if (!hwnd)
		{
			::MessageBox(0, _T("CreateWindow() - FAILED"), 0, 0);
			return false;
		}

		::ShowWindow(hwnd, SW_SHOW);
		::UpdateWindow(hwnd);

		//
		// Init D3D: 
		//

		HRESULT hr = 0;

		// Step 1: Create the IDirect3D9 object.

		IDirect3D9* d3d9 = 0;
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		if (!d3d9)
		{
			::MessageBox(0, _T("Direct3DCreate9() - FAILED"), 0, 0);
			return false;
		}

		// Step 2: Check for hardware vp.

		D3DCAPS9 caps;
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

		int vp = 0;
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.

		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = windowed;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		// Step 4: Create the device.

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT, // primary adapter
			deviceType,         // device type
			hwnd,               // window associated with device
			vp,                 // vertex processing
			&d3dpp,             // present parameters
			&device);            // return created device

		if (FAILED(hr))
		{
			// try again using a 16-bit depth buffer
			d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

			hr = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				deviceType,
				hwnd,
				vp,
				&d3dpp,
				&device);

			if (FAILED(hr))
			{
				d3d9->Release(); // done with d3d9 object
				::MessageBox(0, _T("CreateDevice() - FAILED"), 0, 0);
				return false;
			}
		}

		d3d9->Release(); // done with d3d9 object

		return true;
	}
	LRESULT CALLBACK D3DUtil::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				::DestroyWindow(hwnd);
			break;
		}
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}

	const DWORD Vertex::FVF = D3DFVF_XYZ |  D3DFVF_NORMAL | D3DFVF_TEX1 ;
	//D3DFVF_DIFFUSE不能和D3DFVF_NORMAL等其他一起使用，否则颜色会不正常，为何？
	//const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1;D3DFVF_DIFFUSE
	const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE  ;
}