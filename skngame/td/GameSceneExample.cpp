// GameSceneExample.cpp: implementation of the GameSceneExample class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>   // include important windows stuff
#include <ddraw.h> // include directdraw
#include "GameSceneExample.h"
#include "System.h"
#include "GBrickLayer.h"
#include <IOSTREAM>
using namespace  std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameSceneExample::GameSceneExample()
{
 
}

GameSceneExample::~GameSceneExample()
{

}

void GameSceneExample::play()
{
	GSpiritLayer * layer=	getSpiritLayerById(3);
	GSpirit * s=mario;
	if (brick&&brick->collide(s))
	{ 
		if (s->v.y>=0)
		{ 
			layer->deleteSpirit(brick);
			brick=null;
			s->v.y=0;
			((GBrickLayer*)terrainLayer)->setFollow(4,10,0);
			 
			static GSpirit *b1=new GSpirit(*brick4);
			static GSpirit *b2=new GSpirit(*brick4);
			static GSpirit *b3=new GSpirit(*brick4);
			static GSpirit *b4=new GSpirit(*brick4);
			
			G2DPointf v1(2,8);
			G2DPointf v2(3,6);
			G2DPointf v3(-3,6);
			G2DPointf v4(-2,8);
			b1->v=v1;
			b2->v=v2;
			b3->v=v3;
			b4->v=v4;
			b1->id=spiritId++;
			b2->id=spiritId++;
			b3->id=spiritId++;
			b4->id=spiritId++;
			b1->z=3;
			b2->z=4;
			b3->z=5;
			b4->z=6;
			layer->addSpirit(b1);
			layer->addSpirit(b2);
			layer->addSpirit(b3);
			layer->addSpirit(b4);
		}
	}
	if (GInput::isKeyPress(DIK_DOWN))
	{
		 	s->positionOffset.y=-6;
	}
	if (GInput::isKeyPress(DIK_UP))
	{
		 //	s->positionOffset.y=6;
		s->v.y=9;
	}
	if (GInput::isKeyPress(DIK_LEFT))
	{
		//	xianjian->changeDirection(DIRECTION_LEFT);
		s->positionOffset.x=-4;
	}
	if (GInput::isKeyPress(DIK_RIGHT))
	{	//xianjian->changeDirection(DIRECTION_RIGHT);
		s->positionOffset.x=4;
	}
}

int GameSceneExample::onLoad(GBandle *bandle)
{
	spiritId=10;
	int world_img[15][30]={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,22,0,0,0,0,0,0,0,0,0,2,2,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,31,32,0,0,0,0,0,0,0,0,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int world_follow[15][30]={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	GRenderer* render=GameApp::getInstance()->getRender();
	//ÐÂ½¨²ã
	//backgroundLayer=new GBackgroundLayer;
	//spiritlayer=new GSpiritLayer;
	GBrickLayer *terrainLayer=new GBrickLayer;
	terrainLayer->id=2;
	terrainLayer->z=2;
	terrainLayer->setTransparentColor(RGB(0,255,0));
	terrainLayer->initFollow(30,15,world_follow[0]);
	
	terrainLayer->initImg("res/img/back.bmp",world_img[0],30,15);
	
	this->setTerrainLayer(terrainLayer);

	BitMapFile bitmap;
	bitmap.load("res/img/stand.bmp");
	GAnimationGroup * ag=new GAnimationGroup;
	ag->setDirectionAmount(2);
	GAnimation* mario_stand=this->createAnimation(&bitmap,16,RGB(0,255,0));
	ag->add(0,mario_stand);
	ag->add(1,mario_stand);
	GSpiritLayer * spiritLayer=new GSpiritLayer(3);
	spiritLayer->z=3;
	mario=new GSpiritAnimation(1);
	mario->setPosition(16,200);
	//mario->renderPosition.x=0;
	G2DPoint p0(2,1);
	mario->setRigidSquare(&p0,11,16);
	mario->z=1000;
	mario->isFollow=true;
	mario->animationGroup=ag;
	mario-> speed=15*30;
	mario->isMass=true;	
	spiritLayer->addSpirit(mario);
	spiritLayer->setTransparentColor(RGB(0,255,0));
	this->addSpiritLayer(spiritLayer);
	g=0.8f;
	gravityDirection=GRAVITY_DOWN;
	brick=new GSpirit(2);
	brick->setPosition(64,64);
	G2DPoint p(0,-1);
	brick->setRigidSquare(&p,10,10);
	spiritLayer->addSpirit(brick);
	
	BitMapFile bitmap_brick;
	bitmap_brick.load("res/img/brick.bmp");
	
	
	GFrame *brickf=render->createFrame(&bitmap_brick,1,0);
	
	brick->setFrame(brickf);
 
	
	



	BitMapFile bitmap_brick4;
	bitmap_brick4.load("res/img/brick14.bmp");
	GFrame *brickf4=createFrame(&bitmap_brick4,1,1);
	brick4=new GSpirit(1111);
	brick4->setPosition(64,80);
	brick4->setFrame(brickf4);
	brick4->isMass=true;
	brick4->isFollow=true;
	brick4->setRigidSquare(null,8,8);
	brick4->z=111;
  
	BitMapFile bitmap_fire;
	bitmap_fire.load("res/img/fire.bmp");
	GFrame *fire=createFrame(&bitmap_fire,0,0);
	particle=new GParticleEngine(1);
	particle->initParticles(fire);
	particle->position.x=100;
	particle->position.y=100;
	spiritLayer->addParticleEngine(particle);

	for (int i=0;i<0;i++)
	{
		GSpirit *b1=new GSpirit(*brick4);
		G2DPointf v1(2,8);
		b1->v=v1;
		b1->id=spiritId++;
		b1->z=3;
		spiritLayer->addSpirit(b1);
	}
	
	BitMapFile bitmapx;
	bitmapx.load("res/img/xm4zw.bmp");
	BitMapFile *bitmap1=bitmapx.getSubImageByIndex(0,0,1536,128);
	BitMapFile *bitmap2=bitmapx.getSubImageByIndex(0,1,1536,128);
	BitMapFile *bitmap3=bitmapx.getSubImageByIndex(0,2,1536,128);
	BitMapFile *bitmap4=bitmapx.getSubImageByIndex(0,3,1536,128);
	//GAnimationGroup * ag=new GAnimationGroup;
	//	ag->add(bitmap1,12,128,128,RGB(0,0,0));
 
 
	xianjian=new GSpiritRole(4);
	xianjian->setPosition(100,100);
	xianjian->renderPosition.x=-32;
	xianjian->renderPosition.y=-16;
	xianjian->setRigidSquare(null,60,16);
	xianjian->z=1000;
	xianjian->isFollow=true;
	xianjian->isMass=true;
	xianjian->speed=15*10;
//	spiritLayer->addSpirit(xianjian);
 
 
	xianjian->addAnimations(this,STATE_WALK,&bitmapx,128,0,0);
	 
	xianjian->changeState(STATE_WALK);
	return 1; 
}

 