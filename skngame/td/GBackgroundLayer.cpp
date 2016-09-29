// GBackgroundLayer.cpp: implementation of the GBackgroundLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "GBackgroundLayer.h"
#include "GScene.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GBackgroundLayer::GBackgroundLayer()
{
	renderPosition=GLayer::VIEWPORT;
	needSort=false;
	imgCount=0;
}

GBackgroundLayer::~GBackgroundLayer()
{
 
}
GSpirit*  GBackgroundLayer::addImage(GScene* scene, string *str,int x,int y,int width,int height,int lowColor,int highColor)
{	
	GSpirit * spirit=new GSpirit();
	spirit->id=++imgCount;
	if (str)
	{
		BitMapFile bitmap;
		bitmap.load(*str);
		GFrame * frame=scene->createFrame(&bitmap,lowColor,highColor);
		spirit->setFrame(frame);
	}else
	{
		GFrame * frame=GameApp::getInstance()->getRender()->createFrame(width,height,lowColor,highColor);
		spirit->setFrame(frame);
	}
  	spirit->width=width;
  	spirit->height=height;
  	spirit->position.x=x;
  	spirit->position.y=y;	 
	addSpirit(spirit);
	return spirit;
}

