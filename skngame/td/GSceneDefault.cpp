// GSceneDefault.cpp: implementation of the GSceneDefault class.
//
//////////////////////////////////////////////////////////////////////

#include "GSceneDefault.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GSceneDefault::GSceneDefault()
{
	backgroundLayer=null;//±³¾°²ã
	terrainLayer=null;//µØÐÎ²ã
	g=0;
	gravityDirection=GRAVITY_DOWN;
}

GSceneDefault::~GSceneDefault()
{
	if(backgroundLayer)delete backgroundLayer;
	if(terrainLayer)delete terrainLayer;
	map<int,GSpiritLayer*>::iterator iter;
	for (iter=spiritLayerMap.begin();iter!=spiritLayerMap.end();iter++)
	{
		delete (*iter).second;
		(*iter).second=null;
	}
	spiritLayerMap.clear();
}
void GSceneDefault::addSpiritLayer(GSpiritLayer* layer){
	if(layer==null)return;
	int id=layer->getId();
	if (id<=0)
	{
		return;
	}
	if(spiritLayerMap.find(id)==spiritLayerMap.end())
	{
		spiritLayerMap.insert(map<int,GSpiritLayer*>::value_type(id,layer));
		this->addLayer(layer);
	}
}
void GSceneDefault::removeSpiritLayer(int id){
	map<int,GSpiritLayer*>::iterator iter=spiritLayerMap.find(id);
	if (iter!=spiritLayerMap.end())
	{
		delete (*iter).second;
		spiritLayerMap.erase(iter);
	}
}

  
 
GSpiritLayer* GSceneDefault::getSpiritLayerById(int id)
{
	map<int,GSpiritLayer*>::iterator iter;
	iter=spiritLayerMap.find(id);
	if (iter!=spiritLayerMap.end())
	{
		return (*iter).second;
	}else return null;
}
 
void GSceneDefault::beforeDoVelocity(GSpirit*p)
{
	gravityProcess(p);
}
void GSceneDefault::beforeMoveSpirit(GSpirit*spirit)
{	
	terrainLayer->followSpirit(spirit);
}

 


void GSceneDefault::gravityProcess(GSpirit*spirit)
{
	if (spirit->isMass)
	{	
		switch (gravityDirection)
		{
			case GRAVITY_DOWN:{
				G2DPoint v(0,-1);
				if (!terrainLayer->isFollowed(spirit,&v))
				{
					spirit->v.y-=g;
				}
			}break;
			case GRAVITY_UP:{
				G2DPoint v(0,1);
				if (!terrainLayer->isFollowed(spirit,&v))
				{
					spirit->v.y+=g;
				}
			}break;
		}	
	}	 
}

void GSceneDefault::setBackgroundLayer(GBackgroundLayer *layer)
{
	if (backgroundLayer)
	{
		removeLayer(backgroundLayer->id);
		backgroundLayer=null;
	}
	backgroundLayer=layer;
	addLayer(layer);
}

void GSceneDefault::setTerrainLayer(GTerrainLayer* layer)
{
	if (terrainLayer)
	{
		removeLayer(terrainLayer->id);
		terrainLayer=null;
	}
	terrainLayer=layer;
	addLayer(layer);	 
}

void GSceneDefault::afterMoveSpirit(GSpirit*spirit)
{
	/*map<int,GSpiritLayer* >::iterator iter;
	for(iter=spiritLayerMap.begin();iter!=spiritLayerMap.end();iter++)
	{
		GSpiritLayer *layer=(*iter).second;
		layer->particleProcess();
	}*/
}




