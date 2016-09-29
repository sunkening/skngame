// G3DScene.h: interface for the G3DScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G3DSCENE_H__95F9611B_9F04_4A14_8A21_4BEDF4DEB3AD__INCLUDED_)
#define AFX_G3DSCENE_H__95F9611B_9F04_4A14_8A21_4BEDF4DEB3AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GScene.h"
#include "GRender.h"
#include "GFrame.h"
#include "GCamera.h"
#include "GRenderList.h"
#include "GPoly.h"
#include "G3DRender.h"
#include "G3DObject.h"
#include "GLightInfinit.h"
#include "GLightAmbient.h"
class G3DScene : public GScene  
{
public :
	GRenderer *render;
	GFrame * screen;
	GBackgroundLayer* layer;

	GCamera cam;
	GPoly poly1;
	GRenderList rend_list;
	G3DRender *render3d;
	G3DObjectIndex obj;
	G3DObjectIndex tank;
G3DObjectIndex sph;
	GLightLib lights;
	int tank_speed;
	int wire;
	int back;
	int sortp;
public:
	G3DScene();
	virtual ~G3DScene();
	void play();
	
	virtual int onLoad(GBandle *bandle);
	
};

#endif // !defined(AFX_G3DSCENE_H__95F9611B_9F04_4A14_8A21_4BEDF4DEB3AD__INCLUDED_)
