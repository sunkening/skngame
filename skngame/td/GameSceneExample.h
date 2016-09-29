// GameSceneExample.h: interface for the GameSceneExample class.
//
//////////////////////////////////////////////////////////////////////
#ifndef GAMESCENEEXAMPLE_H
#define GAMESCENEEXAMPLE_H

#include "GSceneDefault.h"
#include "GameApp.h"

#include "GSpiritRole.h"

class GameSceneExample : public GSceneDefault  
{
public:
	int a;
	GSpiritLayer* slayer;
	GSpirit* brick4;
	GSpiritAnimation * mario;
	GSpiritRole * xianjian;
	GSpirit * brick;
	int spiritId;
	GParticleEngine *particle;
public:
	GameSceneExample();
	virtual ~GameSceneExample();
	virtual int onLoad(GBandle *bandle);
	virtual void play();
 
};

#endif  