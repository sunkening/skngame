#ifndef GSCENEDEFAULT_H
#define GSCENEDEFAULT_H

#include "GScene.h"
#include "GBackgroundLayer.h"
#include "GTerrainLayer.h"
#include "GSpiritLayer.h"
#include "GameApp.h"
#include "GAnimationManager.h"
#include "LOG.h"
#include "GSpiritAnimation.h"
#include "GInput.h"
class GSceneDefault : public GScene  
{
public:
	GSceneDefault();
	virtual ~GSceneDefault();
protected:
	GBackgroundLayer* backgroundLayer;//背景层
	GTerrainLayer* terrainLayer;//地形层
	map<int,GSpiritLayer*> spiritLayerMap;//精灵层
	int gravityDirection;
	float g;
	//这里还需要 UI层
public:
	void setBackgroundLayer(GBackgroundLayer *layer);
	GBackgroundLayer* getBackgroundLayer(){
		return backgroundLayer;
	};
	void setTerrainLayer(GTerrainLayer* layer);
	GTerrainLayer* getTerrainLayer(){
		return terrainLayer;
	};
	void addSpiritLayer(GSpiritLayer* layer);
	GSpiritLayer* getSpiritLayerById(int id);
	void removeSpiritLayer(int id);
 
	void beforeMoveSpirit(GSpirit*);
	void beforeDoVelocity(GSpirit*);
	void afterMoveSpirit(GSpirit*);

	void gravityProcess(GSpirit* );	 
};
#endif  