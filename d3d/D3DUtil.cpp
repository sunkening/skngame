#include "stdafx.h"

#include <string>
#include<d3d9.h>
#include<d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <limits>
using namespace std;

#include "D3DUtil.h"
#include "Input.h"
namespace skn_d3d {
	const D3DXCOLOR   D3DUtil::WHITE = D3DCOLOR_XRGB(255, 255, 255);
	const D3DXCOLOR   D3DUtil::BLACK = D3DCOLOR_XRGB(0, 0, 0);
	const D3DXCOLOR   D3DUtil::RED = D3DCOLOR_XRGB(255, 0, 0);
	const D3DXCOLOR   D3DUtil::GREEN = D3DCOLOR_XRGB(0, 255, 0);
	const D3DXCOLOR   D3DUtil::BLUE = D3DCOLOR_XRGB(0, 0, 255);
	const D3DXCOLOR   D3DUtil::YELLOW = D3DCOLOR_XRGB(255, 255, 0);
	const D3DXCOLOR   D3DUtil::CYAN = D3DCOLOR_XRGB(0, 255, 255);
	const D3DXCOLOR   D3DUtil::MAGENTA = D3DCOLOR_XRGB(255, 0, 255);
	int D3DUtil::screenHeight = 0;
	int D3DUtil::screenWidth = 0;
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
		ZeroMemory(&light, sizeof D3DLIGHT9);
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
		ZeroMemory(&m, sizeof D3DMATERIAL9);
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
		byte *b = (byte*)&c;
		int alph = b[3];
		int red = b[2];
		int green = b[1];
		int blue = b[0];

		D3DXCOLOR a(red / 255, green / 255, blue / 255, alph / 255);
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
		D3DXCreateTextureFromFile(device, filename, &t);
		return t;
	}

	Ray D3DUtil::CalcPickingRay(IDirect3DDevice9* device,int x, int y)
	{
		float px = 0.0f;
		float py = 0.0f;

		D3DVIEWPORT9 vp;
		device->GetViewport(&vp);

		D3DXMATRIX proj;
		device->GetTransform(D3DTS_PROJECTION, &proj);

		px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
		py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

		Ray ray;
		ray._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ray._direction = D3DXVECTOR3(px, py, 1.0f);

		return ray;
	}

	void D3DUtil::TransformRay(Ray *ray, D3DXMATRIX *T)
	{
		//D3DXVec3TransformCoord和D3DXVec3TransformNormal都是以3D向量作为参数，
		//D3DXVec3TransformNormal忽略平移 
		// transform the ray's origin, w = 1.
		D3DXVec3TransformCoord(
			&ray->_origin,
			&ray->_origin,
			T);
		// transform the ray's direction, w = 0.
		D3DXVec3TransformNormal(
			&ray->_direction,
			&ray->_direction,
			T);

		// normalize the direction
		D3DXVec3Normalize(&ray->_direction, &ray->_direction);
	}

	bool D3DUtil::RaySphereIntTest(Ray* ray, BoundingSphere* sphere)
	{
		D3DXVECTOR3 v = ray->_origin - sphere->_center;

		float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
		float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

		// find the discriminant
		float discriminant = (b * b) - (4.0f * c);

		// test for imaginary number
		if (discriminant < 0.0f)
			return false;

		discriminant = sqrtf(discriminant);

		float s0 = (-b + discriminant) / 2.0f;
		float s1 = (-b - discriminant) / 2.0f;

		// if a solution is >= 0, then we intersected the sphere
		if (s0 >= 0.0f || s1 >= 0.0f)
			return true;

		return false;
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
		screenHeight = height;
		screenWidth = width;
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

		 
		hwnd = ::CreateWindow(_T("Direct3D9App"), _T("Direct3D9App"),
			WS_EX_TOPMOST,
			0, 0, width, height,
			0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

		if (!hwnd)
		{
			::MessageBox(0, _T("CreateWindow() - FAILED"), 0, 0);
			return false;
		}
		Input::init(hwnd, hInstance);
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
		//cout <<(bool) (caps.FVFCaps&D3DFVFCAPS_PSIZE) << endl;
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

	float Learp(float a, float b, float t)
	{

		return a + (b - a)*t;

	}

	const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	//D3DFVF_DIFFUSE不能和D3DFVF_NORMAL等其他一起使用，否则颜色会不正常，为何？
	//const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1;D3DFVF_DIFFUSE
	const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	const DWORD MultiTexVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX3;
	float D3DUtil::GetRandomFloat(float lowBound, float highBound)
	{
		if (lowBound >= highBound) // bad input
			return lowBound;

		// get random float in [0, 1] interval
		float f = (rand() % 10000) * 0.0001f;

		// return float in [lowBound, highBound] interval. 
		return (f * (highBound - lowBound)) + lowBound;
	}

	void D3DUtil::GetRandomVector(
		D3DXVECTOR3* out,
		D3DXVECTOR3* min,
		D3DXVECTOR3* max)
	{
		out->x = GetRandomFloat(min->x, max->x);
		out->y = GetRandomFloat(min->y, max->y);
		out->z = GetRandomFloat(min->z, max->z);
	}

	DWORD D3DUtil::FtoDw(float f)
	{
		return *((DWORD*)&f);
	}

	BoundingBox::BoundingBox()
	{
		_min.x = INFINITY;
		_min.y =  INFINITY;
		_min.z =  INFINITY;

		_max.x =  INFINITY;
		_max.y =  INFINITY;
		_max.z =  INFINITY;
	}

	bool BoundingBox::isPointInside(D3DXVECTOR3& p)
	{
		if (p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
			p.x <= _max.x && p.y <= _max.y && p.z <= _max.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	BoundingSphere::BoundingSphere()
	{
		_radius = 0.0f;
	}

}