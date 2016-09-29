// GameApp.cpp: implementation of the GameApp class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw


#include "GameApp.h"
#include "System.h"
#include "GInput.h"
#include "LOG.h"
#include "GMath.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GameApp * GameApp::app=NULL;
GameApp::GameApp()
{
	render=null;
	hwnd=null;
	viewPortList=new vector<GViewPort*>;
 
	curScene=null;
 	app=null;
	//gameapp=this;
	logger=new GLogger;
	enableLog=false;
	logPort=null;
	//startClockCount=0;
	//count=15;
	second60=0;
}

GameApp::~GameApp()
{
	if(render){
		delete render;
	}
	if(viewPortList){	
	}
	map<int,GScene*>::iterator sceneIter;
	for (sceneIter=sceneMap.begin();sceneIter!=sceneMap.end();sceneIter++)
	{
		GScene *s=sceneIter->second;
		if(s)delete s;
	}
	if(logger){
		delete logger;
	}
	GDDraw::release();
	GInput::release();
}

int GameApp::init(HINSTANCE hinstance_app,bool windowed,HWND main_window_handle,int mode,int width, int height, int bpp)
{
	hwnd=main_window_handle;
	if(mode==DIRECT_DRAW)
	{
		GDDraw::init( windowed,  main_window_handle,  width,   height,   bpp );
		render=new GDDrawRenderer ;
	}
	//初始化输入设备
	if(!GInput::init(main_window_handle,hinstance_app))return 0;
	//初始化数学引擎
	GMath::init();
	LOG::init();
	load();
	return 1;
}
int GameApp::load()
{
	return 1;
}

/*
void GameApp::setViewPort(int num,GRect *rectList)
{
	if(viewtList==NULL){
		this->viewPortList=new ViewPort;
		viewPortNum=1;
		viewPortList->screen_x=0;
		viewPortList->screen_y=0;
		viewPortList->world_x=0;
		viewPortList->world_y=0;
		viewPortList->width=screenWidth;
		viewPortList->height=screenHeight;
		//如果只有一个视口,视口表面就是主缓冲表面
		viewPortList->viewPortSurface=lpddsback;
		// setup backbuffer clipper always
		RECT screen_rect = {0,0,screenWidth,screenHeight};
		lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);
	}else{
	
	  viewPortList=viewtList;
		if(num>MAX_VIEWPORT_NUM)viewPortNum=MAX_VIEWPORT_NUM;
		else viewPortNum=num;
		RECT *viewRect=new RECT[num];
		for(int i=0;i<num&&i<MAX_VIEWPORT_NUM;i++){
			//创建裁剪用的RECT
			viewRect[0].left=0;
			viewRect[0].right=viewPortList[i].width;
			viewRect[0].top=0;
			viewRect[0].bottom=viewPortList[i].height;	
			//给此视口创建表面
			viewPortList[i].viewPortSurface=CreateSurface(viewPortList[i].width,viewPortList[i].height,0,color_key);
			DDraw_Attach_Clipper(viewPortList[i].viewPortSurface,1,viewRect);
		}
	}
	
}*/
GViewPort * GameApp::addViewPort(string name,G2DPoint  world,G2DPoint screen,int width,int height,int color)
{		
	GViewPort *viewport= render->createViewPort(world,screen,width,height);
	viewport->name=name;
	viewport->backgroundColor=color;
	viewPortList->push_back(viewport);
	return viewport;
}
GViewPort *GameApp::getViewPortByName(const string &name)
{
	GViewPort* v=null;
	vector<GViewPort*>::iterator iter;
	for(iter=viewPortList->begin();iter!=viewPortList->end();iter++)
	{
		if(name==((*iter)->name)){
			v= *iter;
			break;
		}
	}
	if (!v)
	{
		string s("没有获取到视口：");
		s+=name;
		LOG::i(s);
	}
	return v;
}

void GameApp::renderScene()
{
	if(curScene)
	{
		render->render(hwnd,curScene,viewPortList);
		if(enableLog){
			render->drawToBack(logPort->getCanvas(),logPort->screen.x,logPort->screen.y, 0);
		}
		render->flip();
	}
}

void GameApp::afterPlay()
{
	if (curScene)
	{
		curScene->afterPlay();
	}
}
void GameApp::beforePlay()
{
	// make sure this isn't executed again
	//if (window_closed)   return(0);
	// for now test if user is hitting ESC and send WM_CLOSE
	if (KEYDOWN(VK_ESCAPE))
	{
	 //  PostMessage(main_window_handle,WM_CLOSE,0,0);
	  // window_closed = 1;
	} // end if
	if(enableLog){
		GDDraw::fillSurface((LPDIRECTDRAWSURFACE7)logPort->getCanvas()->getSurface(),0);
	}
	
	GInput::getInputState();
	if (curScene)
	{
		curScene->beforePlay();
	}
}
void GameApp::play()
{
	if(curScene)curScene->play();
}
void GameApp::release()
{

}
void GameApp::mainLoop()
{
	
	GSystem::resetTickCount();
	
/*
	app->beforePlay();
	int beforePlaytime=GetTickCount();
	app->play();//游戏主逻辑循环
	int playtime=GetTickCount();		 
	app->afterPlay(); 
	int afterplaytime=GetTickCount();*/
 
	if (GSystem::secondCount60>app->second60)
	{
		 
		app->second60=GSystem::secondCount60;
		app->beforePlay();
			 
		app->play();//游戏主逻辑循环
			 
		app->afterPlay(); 
			 
	//	GSystem::waitClock();
	}

	app->renderScene();
 int rendertime=GetTickCount();
/*
 cout<<"beforePlaytime="<<beforePlaytime-GSystem::tickCount<<
	 ";playtime="<<playtime-beforePlaytime<<
	 ";afterplaytime="<<afterplaytime-playtime<<
	 "rendertime="<<rendertime-afterplaytime<<endl;*/
	//GSystem::waitClock();
	//string ss="FPS:";
	//GLogger::info(ss+(int)(1000/(GetTickCount()-GSystem::tickCount)));
}
void GameApp::addScene(GScene * s)
{
	if (s->id==0)
	{
		return;
	}
	map<int,GScene*>::iterator iter;
	iter=sceneMap.find(s->id);
	if (iter!=sceneMap.end())
	{
		return;
	}
	sceneMap.insert(map<int,GScene*>::value_type(s->id,s));
	s->gameApp=this;
}
GScene* GameApp::getScene(int i)
{	
	GScene* scene=null;
	map<int,GScene*>::iterator iter;
	iter=sceneMap.find(i);
	if (iter!=sceneMap.end())
	{
		scene=iter->second;
	}
	return scene;
	
}
void GameApp::initLogger(G2DPoint screen,int width,int height )
{
	G2DPoint world(0,0);
	logPort = render->createViewPort(world,screen,320,240);
	enableLog=true;
	GLogger::setPanel(logPort->getCanvas());
	GLogger::enable=true;
	GLogger::render=render;
}
void GameApp::disableLogger( )
{
	if(logger)
		logger->enable=false;
}

void GameApp::deleteScene(int i)
{
	map<int,GScene*>::iterator iter;
	iter=sceneMap.find(i);
	if (iter!=sceneMap.end()&&iter->second)
	{
		iter->second->release();
		delete iter->second;
		sceneMap.erase(iter);
	}
}

void GameApp::startScene(int id,GBandle* bandle,bool release)
{	
	map<int,GScene*> :: iterator iter=sceneMap.find(id);
	GScene *s=null;
	if(iter!=sceneMap.end()&&iter->second)
	{
		s=iter->second;
		if(s->getStatus()==GScene::RELEASED)
		{
			s->onLoad(bandle);
		}
		s->popUp();
	}
	if (curScene)
	{
		if (release)
		{
			curScene->release();
		}else 
		{
			curScene->hangUp();
		}
	}
	curScene=s;
}
