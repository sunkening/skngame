#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw
#include "GameAppExample.h"
#include "GSceneDefault.h"
#include "GameSceneJX.h"
#include "G3DScene.h"
#include "gl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameAppExample::GameAppExample()
{

}

GameAppExample::~GameAppExample()
{

}
/*
int GameAppExample::init(bool windowed,HWND main_window_handle,int mode,int width, int height, int bpp)
{		
 
	if(!GameApp::init(  windowed, main_window_handle, mode, width, int height,   bpp))
		return 0;

	
	return 1;
}*/
int GameAppExample::load()
{
	//新建摄像机
	string name="viewPort";
	G2DPoint world(0,600);
	G2DPoint screen(0,0);
	GViewPort *v=addViewPort(name+1,world,screen,800,600,RGB(252,148,92));

	G2DPoint world2(0,50);
	G2DPoint screen2(0,245);
//	addViewPort(name+2,world2,screen2,320,240 );

	//新建场景
	GScene *s=new G3DScene();
	 //GScene *s=new GameSceneJX();
	//GScene *s=new GameSceneExample();
	s->id=1;
	addScene(s);//
	//启动场景
	startScene(1);
	
	G2DPoint logPosition(320,240);
	GameApp::getInstance()->initLogger(logPosition,320,240 );
	string ss="aldjflasdjglajglasjdl";
	GLogger::info(ss);
	return 1;
}
	
