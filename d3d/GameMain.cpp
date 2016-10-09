#include "stdafx.h"

#include<d3d9.h>
#include<d3dx9.h>
#include"D3DUtil.h"
#include "GameMain.h"
#include <iostream>
using namespace std;
namespace skn_d3d {
	void GameMain::play(float timeDelta)
	{
		IDirect3DDevice9* device = d3dUtil->device;
		device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		device->BeginScene();
		
		device->EndScene();
		device->Present(0, 0, 0, 0);
	}

	bool GameMain::setup()
	{
		 
		return true;
	}

	GameMain::GameMain()
	{
	}

	int GameMain::EnterMsgLoop(GameMain *game)
	{
		MSG msg;
		::ZeroMemory(&msg, sizeof(MSG));

		static float lastTime = (float)timeGetTime();
		game->setup();
		while (msg.message != WM_QUIT)
		{
			if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				float currTime = (float)timeGetTime();
				float timeDelta = (currTime - lastTime)*0.001f;
				game->play(timeDelta);
				lastTime = currTime;
			}
		}
		return msg.wParam;
	}
}