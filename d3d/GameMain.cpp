#include "stdafx.h"

#include<d3d9.h>
#include<d3dx9.h>
#include"D3DUtil.h"
#include "GameMain.h"
namespace skn_d3d {
	void GameMain::play(float timeDelta)
	{
		d3dUtil->device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3dUtil->device->BeginScene();

		d3dUtil->device->EndScene();
		d3dUtil->device->Present(0, 0, 0, 0);

	}
}