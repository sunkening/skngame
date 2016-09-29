// GameApp.h: interface for the GameApp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <vector>
#include <map>
#include <list>
#include <set>
using namespace std;
#include "GObject.h"
#include "GRect.h"
#include "GDDrawRender.h"
#include "GbackgroundLayer.h"
#include "GScene.h"
#include "GDDraw.h"
#include "GLogger.h"
#include "gl.h"


class GameApp : public GObject  
{
protected :
	static GameApp * app;
	HWND hwnd;
	GScene * curScene;
	GRenderer * render;
	GLogger* logger;
	bool enableLog;
	vector<GViewPort*> *viewPortList;
//	GFrame * logPanel;
	GViewPort* logPort;
	map<int,GScene*> sceneMap;
	map<int,GFrame*>* frameMap;
//	int startClockCount;
//	int count;
	int second60;
	
protected:
	void renderScene();
public:
	
	GameApp();
	virtual ~GameApp();
	static GameApp * getInstance(){return app;};
	static void  setInstance(GameApp * a){app=a;}
	GScene* getCurScene(){return curScene;};
	GRenderer * getRender(){return render;}
	GViewPort * addViewPort(string name,G2DPoint world,G2DPoint screen,int width,int height,int color=0);
	
	void addScene(GScene * s);
	GScene*  getScene(int id);
	void deleteScene(int i);
	void startScene(int id,GBandle* bandle=null,bool release=false);
	//void releaseScene(int id);

	void initLogger(G2DPoint screen,int width,int height);
	void disableLogger( );
	
	GViewPort * getViewPortByName(const string &name);
	virtual int init(HINSTANCE hinstance_app,bool windowed,HWND main_window_handle,int mode,int width, int height, int bpp=0);
	virtual void play();
	virtual void afterPlay();
	virtual void beforePlay();
	virtual void release();
	static void mainLoop();

	virtual int load();
 
	
};
//extern   GameApp * gameapp;
#endif 
