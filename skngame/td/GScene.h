// GScene.h: interface for the GScene class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GSCENE_H
#define GSCENE_H
#include <map>
#include <list>
#include <set>
#include <new>
#include <string>
#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw
using namespace std;

#include "GObject.h"

#include "GLayer.h"
#include "GCompareZ.h"
#include "gl.h"
#include "GLogger.h"
#include "GDDrawFrame.h"
#include "GBandle.h"
#include "GameApp.h"
#include "GAnimation.h"
#include <VECTOR>
#define GRAVITY_DOWN 1
#define GRAVITY_UP 2
class GScene : public GObject  
{
public:
	static const int PLAYING;//正在运行的
	static const int HANGED;//loading后或者hangup后
	static const int RELEASED;//init之后或者release后,需要reload或者load才可以play

	int id;
	GameApp * gameApp;
	
protected:
	map<int,GLayer*> layerMap;
	map<int,GLayer*>  sortedLayers;
	
	string sceneName;
	map<int,GFrame*> * frameMap;//保存场景游戏层用到的fram，在场景release和析构时会释放掉
	map<int,GAnimation*> animationMap;//保存场景游戏层用到的animation，在场景release和析构时会释放掉

	//背景色
	int backgroundColor;
	GFrame* backgroundImage;
	int status;
	int frameCount;
	int animationCount;

public:
	GScene();
	GScene(int id);
	virtual ~GScene();
//	virtual set<GLayer* ,CompareLessZ> * getLayerSet();
	map<int,GLayer*> *getLayerMap(){return &layerMap;};
	map<int,GLayer*>* getSortedLayers(){return &sortedLayers;};
	int getStatus(){return status;}
	//void  addLayer(int id,GLayer * layer);
	void  addLayer(GLayer * layer);
	GLayer *  getLayer(int id);
	void removeLayer(int id);

	string getSceneName();
	void setSceneName(string name);
	GFrame* getFrameForReference(int id);
	void setBackgroundColor(int color)
	{
		backgroundColor=color;
	};
	void initBcakgroundImage(GFrame* frame);
	void initBcakgroundImage(string fileName);
	void addFrame(int id,GFrame* frame);
	GFrame * createFrame( BitMapFile * bitmap,int lowcolor,int highcolor);
	GAnimation * createAnimation(BitMapFile * bitmap,int cell_width,int lowcolor=0,int highcolor=0);
	//virtual int load();
	virtual int onLoad(GBandle *bandle){return 1;};//利用init()函数初始化的成员变量,加载资源,通常在这里显示loading画面
	virtual void play();//场景的主要循环
	virtual void hangUp();//挂起
	virtual void popUp();//弹出到前端
	virtual void release();//释放资源

	virtual void beforePlay(){};
	virtual void afterPlay();

protected:
	virtual void beforeDoVelocity(GSpirit*){};
	//void doVelocity(GSpirit*);
	virtual void afterDoVelocity(GSpirit*){};
	virtual void beforeMoveSpirit(GSpirit*){};
	//void moveSpirits(GSpirit*);
	virtual void afterMoveSpirit(GSpirit*){};
	virtual void sortLayers() ;
	virtual void sortSpirits();	
 
};

#endif  
