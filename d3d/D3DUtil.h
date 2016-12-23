#pragma once
namespace skn_d3d 
{
	class D3DUtil {
	public:
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
		//计算面的法线，顶点为顺时针环绕
		static void ComputeNormal(D3DXVECTOR3 *p0, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *out);
		static D3DLIGHT9 InitDirectionLight(D3DXVECTOR3 d, D3DXCOLOR color);
		static D3DLIGHT9 InitPointLight(D3DXVECTOR3 position, D3DXCOLOR color);
		static D3DMATERIAL9 InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e , float p = 0.0f);
		static D3DMATERIAL9 InitMaterial(D3DCOLOR c, float diffuse=1,float s=0,float e=0);
		IDirect3DTexture9* LoadTexture(TCHAR * filename);
		//
		// Cleanup
		//
		 template<class T> static void Release(T t)
		{
			if (t)
			{
				t->Release();
				t = 0;
			}
		}

		 template<class T>static void Delete(T t)
		{
			if (t)
			{
				delete t;
				t = 0;
			}
		}
		static float GetRandomFloat(float lowBound, float highBound);
		 // Desc: Returns a random vector in the bounds specified by min and max.
		static void GetRandomVector(
			 D3DXVECTOR3* out,
			 D3DXVECTOR3* min,
			 D3DXVECTOR3* max);
		static DWORD FtoDw(float f);
};
	struct ColorVertex
	{
		ColorVertex() {}
		ColorVertex(float x, float y, float z)
		{
			_x = x;  _y = y;	_z = z;
		}
		float _x, _y, _z;
		D3DCOLOR color;
		static const DWORD FVF;
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
	//D3DCOLOR color;
	float _nx, _ny, _nz;
	float _u, _v;
	
	static const DWORD FVF;
};
float Learp(float a, float b, float t);
}