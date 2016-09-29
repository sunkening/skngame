// GameSceneJX.h: interface for the GameSceneJX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMESCENEJX_H__1ED6C4A6_F525_4772_B2F5_4992B482ED97__INCLUDED_)
#define AFX_GAMESCENEJX_H__1ED6C4A6_F525_4772_B2F5_4992B482ED97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSceneDefault.h"
#include "GSpiritRole.h"
#include "GColorLayer.h"
class GameSceneJX : public GSceneDefault  
{
public:
	GameSceneJX();
	virtual ~GameSceneJX();
	virtual int onLoad(GBandle *bandle);
	virtual void play();
	GSpiritRole * mario;
GColorLayer *terrainLayer;
G2DPoint target;
GViewPort* view;
};

#endif // !defined(AFX_GAMESCENEJX_H__1ED6C4A6_F525_4772_B2F5_4992B482ED97__INCLUDED_)
