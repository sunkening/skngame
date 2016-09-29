// GScene.cpp: implementation of the GScene class.
//
//////////////////////////////////////////////////////////////////////


#include <algorithm>

#include "GScene.h"
#include "LOG.h"
#include "Exception.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int GScene::PLAYING=1;
const int GScene::HANGED=2;
const int GScene::RELEASED=3;
GScene::GScene()
{
	frameMap=new map<int,GFrame*>  ;
	status=RELEASED;
	backgroundColor=0;
	backgroundImage=null;
	frameCount=0;
	animationCount=0;
	id=0;
}
GScene::GScene(int i)
{
 	new(this) GScene();
	id=i;
}

GScene::~GScene()
{ 
	map<int ,GFrame*>::iterator frameIter;
	for(frameIter=frameMap->begin();frameIter!=frameMap->end();frameIter++)
	{
		delete (*frameIter).second;
	}
	delete frameMap;
	map<int ,GLayer*>::iterator layerIter;
	for(layerIter=layerMap.begin();layerIter!=layerMap.end();layerIter++)
	{
		delete (*layerIter).second;
	}
 
	delete backgroundImage;
}

void  GScene::addLayer(GLayer * layer)
{
	if(layer==null){
		return;
	}
	if (layer->id<=0)
	{
		LOG::e("GScene::addLayer(GLayer * layer)，添加层失败，layer的id<=0;");
		throw new Exception("GScene::addLayer(GLayer * layer)，添加层失败，layer的id<=0;");
	}
	map<int,GLayer*>::iterator iter;
	iter=layerMap.find(layer->id);
	if (iter!=layerMap.end())
	{
		if (iter->second)
		{
			delete iter->second;
		}
		layerMap.erase(iter);
	}
	layerMap.insert(map<int,GLayer*>::value_type(layer->id,layer));
}
 
string GScene::getSceneName()
{
	return sceneName;
}
void GScene::setSceneName(string name)
{

}

void GScene::play()
{

}
GFrame* GScene::getFrameForReference(int id)
{
	map<int,GFrame*>::iterator iter;
	iter=frameMap->find(id);
	if(iter==frameMap->end())return null;
	GFrame* frame=(*iter).second;
	frame->increaseCount();
	return frame;
}
void GScene::addFrame(int id,GFrame* frame)
{
	map<int,GFrame*>::iterator iter;
	iter=frameMap->find(id);
	if(iter!=frameMap->end())
	{
		delete (*iter).second;
	}
	frameMap->insert(map<int,GFrame*>::value_type(id,frame));
}
void GScene::initBcakgroundImage(GFrame* frame)
{
	if(!backgroundImage)backgroundImage=frame;
}
 
void GScene::initBcakgroundImage(string fileName)
{
	if(!backgroundImage)
	{
		GFrame* frame=new GDDrawFrame((char*)fileName.c_str(),0,0);
		backgroundImage=frame;
	}
} 


void GScene::hangUp()
{

}
void GScene::popUp()
{

}
void GScene::release()
{

}

GFrame * GScene::createFrame( BitMapFile * bitmap,int lowcolor,int highcolor)
{
	GFrame *f=gameApp->getRender()->createFrame(bitmap,lowcolor,highcolor);
	f->id=++frameCount;
	frameMap->insert(map<int,GFrame*>::value_type(f->id,f));
	return f;
}

void GScene::afterPlay()
{
	int a=GetTickCount();
	map<int,GLayer* >::iterator iter;
	for(iter=layerMap.begin();iter!=layerMap.end();iter++)
	{
		GLayer *layer=(*iter).second;
		if (!layer->needMoveSpirits)
		{
			continue;
		}
		vector<GSpirit*> *v=& layer->spirits;
		vector<GSpirit*>::iterator spritIter;
		for (spritIter=v->begin();spritIter!=v->end();spritIter++)
		{
			GSpirit * sprite=*spritIter;

			beforeDoVelocity(sprite);
			sprite->positionOffset+=sprite->v;//把速度加到位置偏移量上
			afterDoVelocity(sprite);

			beforeMoveSpirit(sprite);
			//把位置偏移量加到位置上
			sprite->position+=sprite->positionOffset;	
			sprite->positionOffset.x=0;
			sprite->positionOffset.y=0;
			 
			
			afterMoveSpirit(sprite);
		}
	}
 
int b=GetTickCount();
	sortSpirits();//给精灵排序
int c=GetTickCount();
	sortLayers();//给层排序
int d=GetTickCount();
//cout<<b-a<<":"<<c-b<<":"<<d-c<<endl;
}

void GScene::sortSpirits()
{
	map<int,GLayer*>::iterator iter;
	for (iter=layerMap.begin();iter!=layerMap.end();iter++)
	{
		if (iter->second->needSort)
		{
			vector<GSpirit*> *v=&iter->second->spirits;
			sort(v->begin(),v->end(),ComparableZ::bigger);
		}
	}
}

void GScene::sortLayers()
{
	sortedLayers.clear();
	map<int,GLayer*>::iterator iter;
	for (iter=layerMap.begin();iter!=layerMap.end();iter++)
	{
		GLayer* l=iter->second;
		sortedLayers.insert(map<int,GLayer*>::value_type(l->z,l));
	}
}

GLayer * GScene::getLayer(int id)
{
	map<int,GLayer*> :: iterator iter=layerMap.find(id);
	if(iter==layerMap.end()) 
		return null;
	return (*iter).second;
 
}

void GScene::removeLayer(int id)
{
	map<int,GLayer*> :: iterator iter=layerMap.find(id);
	if(iter!=layerMap.end()) 
	{
		if (iter->second)
		{
			delete iter->second;
		}
		layerMap.erase(iter);
	}
}

GAnimation * GScene::createAnimation(BitMapFile * bitmap,int cell_width,int lowcolor,int highcolor)
{
	GAnimation* anim=new GAnimation();
	anim->init(bitmap,cell_width,lowcolor,highcolor);
	anim->id=++animationCount;
	animationMap.insert(map<int,GAnimation*>::value_type(anim->id,anim));
	return anim;
}


