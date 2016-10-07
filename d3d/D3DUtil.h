#pragma once
namespace skn_d3d 
{
class D3DUtil {
public :
	void(*display)(float timedelta);
	D3DUtil();
	IDirect3DDevice9* device;
	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType);    // [in] HAL or REF
		
	int EnterMsgLoop( );
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);

};
struct Vertex {
	float _x, _y, _z;
	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ;
}