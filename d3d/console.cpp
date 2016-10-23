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
 
#include "Camera.h"



using namespace skn_d3d; 
Camera TheCamera(Camera::LANDOBJECT);
 
int Width=800;
int Height =600; 
  
int _tmain(int ac,char *av[])

{

	HINSTANCE inst;
	inst=(HINSTANCE)GetModuleHandle(NULL);
	//_tWinMain(inst, 0,0, SW_SHOWNORMAL);
	GameMain *gamemain=new GameTest5;
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
