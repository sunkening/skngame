#pragma once
namespace skn_d3d 
{
class D3DUtil {
public :
	D3DUtil();
	IDirect3DDevice9* device;
	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType);    // [in] HAL or REF
		
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);
	static const D3DXCOLOR      WHITE;
	static const D3DXCOLOR      BLACK;
	static const D3DXCOLOR        RED;
	static const D3DXCOLOR      GREEN;
	static const D3DXCOLOR       BLUE;
	static const D3DXCOLOR     YELLOW;
	static const D3DXCOLOR       CYAN;
	static const D3DXCOLOR    MAGENTA;
};
struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		_x = x;  _y = y;	_z = z;
	}
	Vertex(float x, float y, float z, float nx, float ny, float nz)
	{
		_x = x;  _y = y;	_z = z;
		_nx = nx; _ny = ny; _nz = nz;
	}
	void setTex(float u, float v) {
		_u = u;
		_v = v;
	};
	float _x, _y, _z;
	D3DCOLOR color;
	float _nx, _ny, _nz;
	float _u, _v;
	static const DWORD FVF;
};

}