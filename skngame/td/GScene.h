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
	static const int PLAYING;//�������е�
	static const int HANGED;//loading�����hangup��
	static const int RELEASED;//init֮�����release��,��Ҫreload����load�ſ���play

	int id;
	GameApp * gameApp;
	
protected:
	map<int,GLayer*> layerMap;
	map<int,GLayer*>  sortedLayers;
	
	string sceneName;
	map<int,GFrame*> * frameMap;//���泡����Ϸ���õ���fram���ڳ���release������ʱ���ͷŵ�
	map<int,GAnimation*> animationMap;//���泡����Ϸ���õ���animation���ڳ���release������ʱ���ͷŵ�

	//����ɫ
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
	virtual int onLoad(GBandle *bandle){return 1;};//����init()������ʼ���ĳ�Ա����,������Դ,ͨ����������ʾloading����
	virtual void play();//��������Ҫѭ��
	virtual void hangUp();//����
	virtual void popUp();//������ǰ��
	virtual void release();//�ͷ���Դ

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
