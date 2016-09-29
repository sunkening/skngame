// GameSceneJX.cpp: implementation of the GameSceneJX class.
//
//////////////////////////////////////////////////////////////////////

#include "GameSceneJX.h"
#include "GColorLayer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameSceneJX::GameSceneJX()
{

}

GameSceneJX::~GameSceneJX()
{

}

int GameSceneJX::onLoad(GBandle *bandle)
{
	GTerrainPiece *world_img=new GTerrainPiece();
	//world_img[0][0].bottomPath=
	world_img->topPath="res/img/bitmap24.bmp";
	world_img->bottomPath="res/img/bitmap24-cf.bmp";
	GRenderer* render=GameApp::getInstance()->getRender();
	//ÐÂ½¨²ã
	//backgroundLayer=new GBackgroundLayer;
	//spiritlayer=new GSpiritLayer;
	terrainLayer=new GColorLayer;
	terrainLayer->id=2;
	terrainLayer->z=2;
	terrainLayer->setTransparentColor(RGB(0,255,0));
	
	terrainLayer->init(world_img,1,1,640,480);
	
	this->setTerrainLayer(terrainLayer);

	BitMapFile bitmap;
	bitmap.load("res/img/xm4zw.bmp");
	GSpiritLayer * spiritLayer=new GSpiritLayer(3);
	spiritLayer->z=3;
	mario=new GSpiritRole(8);
	mario->setPosition(116,200);
	mario->renderPosition.x=-64;
	mario->renderPosition.y=-16;
	mario->setRigidSquare(null,14,16);
	mario->z=1000;
	mario->isFollow=true;
	mario->speed=15*10;
	spiritLayer->addSpirit(mario);
	spiritLayer->setTransparentColor(RGB(0,255,0));
	this->addSpiritLayer(spiritLayer);
	mario->addAnimations(this,STATE_WALK,&bitmap,128,0,0);
	mario->changeState(STATE_WALK);
	
	view=gameApp->getViewPortByName("viewPort1");
	return 1;
}

void GameSceneJX::play()
{
	terrainLayer->getColor(& mario->position);
	if (GInput::cursor->pressLeft())
	{
		target=view->screenToWorld(GInput::cursor->getX(),GInput::cursor->getY());
		
	}
	if (true)
	{
		int dx=target.x-mario->position.x;
		int dy=target.y-mario->position.y;
		int x_direction=0;
		int y_direction=0;

		if (dx<0)
		{
			x_direction=-1;
			if (dx<-4)
			{
				dx=-4;
			}
		}else if(dx>0)
		{ 
			x_direction=1;
			if (dx>4)
			{
				dx=4;
			}
		} 
		if (dy<0)
		{
			y_direction=-1;
			if (dy<-4)
			{
				dy=-4;
			}
		}else if(dy>0)
		{
			 y_direction=1;
			if (dy>4)
			{
				dy=4;
			}
		}

		mario->positionOffset.y=dy;
		mario->positionOffset.x=dx;
		mario->changeDirectionByOffset(dx,dy);
		if (x_direction>0)
		{
			GInput::pressKey(DIK_RIGHT);
		}else if (x_direction<0)
		{
			GInput::pressKey(DIK_LEFT);
		}
		if (y_direction>0)
		{
			GInput::pressKey(DIK_UP);
		}else if (y_direction<0)
		{
			GInput::pressKey(DIK_DOWN);
		}
	}
	
/*
	if (GInput::isKeyPress(DIK_RIGHT)&&GInput::isKeyPress(DIK_UP))
	{cout<<mario->curDirection<<endl;
		mario->changeDirection(DIRECTION_UP_RIGHT);
		mario->positionOffset.y=2.8;
		mario->positionOffset.x=2.8;
	}else
	if (GInput::isKeyPress(DIK_LEFT)&&GInput::isKeyPress(DIK_UP))
	{
		mario->changeDirection(DIRECTION_UP_LEFT);
		mario->positionOffset.y=2.8;
		mario->positionOffset.x=-2.8;
	}else
	if (GInput::isKeyPress(DIK_LEFT)&&GInput::isKeyPress(DIK_DOWN))
	{
		mario->changeDirection(DIRECTION_DOWN_LEFT);
		mario->positionOffset.y=-2.8;
		mario->positionOffset.x=-2.8;
	}else
	if (GInput::isKeyPress(DIK_RIGHT)&&GInput::isKeyPress(DIK_DOWN))
	{
		mario->changeDirection(DIRECTION_DOWN_RIGHT);
		mario->positionOffset.y=-2.8;
		mario->positionOffset.x=2.8;
	}else
	if (GInput::isKeyPress(DIK_RIGHT))
	{
		mario->changeDirection(DIRECTION_RIGHT);
		
		mario->positionOffset.x=4;
	}else
	if (GInput::isKeyPress(DIK_UP))
	{
		mario->changeDirection( DIRECTION_UP);
		mario->positionOffset.y=4;
	}else
	
	if (GInput::isKeyPress(DIK_LEFT))
	{
		mario->changeDirection(DIRECTION_LEFT);
		
		mario->positionOffset.x=-4;
	}else
	
	if (GInput::isKeyPress(DIK_DOWN))
	{
		mario->changeDirection( DIRECTION_DOWN);
		mario->positionOffset.y=-4;
	}
	*/
}
