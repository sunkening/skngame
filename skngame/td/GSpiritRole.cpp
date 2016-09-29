// GSpiritRole.cpp: implementation of the GSpiritRole class.
//
//////////////////////////////////////////////////////////////////////

#include "GSpiritRole.h"
#include "GScene.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
 

GSpiritRole::GSpiritRole(int d)
{
	directionAmount=d;
	roleDirections=d;
	animationGroup=new GAnimationGroup(d);
	for (int i=0;i<d;i++)
	{
		animationGroup->directionVector[i].resize(6,null);
	}
	
}

GSpiritRole::~GSpiritRole()
{

}





void GSpiritRole::addAnimations(GScene* scene,int state,BitMapFile* bitmap,int cell_width,int l,int h)
{
	int totalWidth=bitmap->bitmapinfoheader.biWidth;
	int cell_height=bitmap->bitmapinfoheader.biHeight/roleDirections;
 
	for (int i=0;i<roleDirections;i++)
	{
		BitMapFile *bitmap1=bitmap->getSubImageByIndex(0,i,totalWidth,cell_height);
		
		//animation资源由scene管理
		GAnimation* anim=scene->createAnimation(bitmap1,cell_width,l,h);
		
		animationGroup->add(i,state,anim);
		
		delete bitmap1;
	}



}

void GSpiritRole::changeDirectionByOffset(int x,int y)
{

	if (x>0&&y>0)
	{
		changeDirection(DIRECTION_UP_RIGHT);
	/*	mario->positionOffset.y=2.8;
		mario->positionOffset.x=2.8;*/
	}else
	if (x<0&&y>0)
	{
		changeDirection(DIRECTION_UP_LEFT);
		/*mario->positionOffset.y=2.8;
		mario->positionOffset.x=-2.8;*/
	}else
	if (x<0&&y<0)
	{
		changeDirection(DIRECTION_DOWN_LEFT);
		/*mario->positionOffset.y=-2.8;
		mario->positionOffset.x=-2.8;*/
	}else
	if (x>0&&y<0)
	{
		changeDirection(DIRECTION_DOWN_RIGHT);
		/*mario->positionOffset.y=-2.8;
		mario->positionOffset.x=2.8;*/
	}else
	if (x>0)
	{
		changeDirection(DIRECTION_RIGHT);
		
	//	mario->positionOffset.x=4;
	}else
	if (y>0)
	{
		changeDirection( DIRECTION_UP);
	//	mario->positionOffset.y=4;
	}else
	
	if (x<0)
	{
		changeDirection(DIRECTION_LEFT);
		
	//	mario->positionOffset.x=-4;
	}else
	
	if (y<0)
	{
		changeDirection( DIRECTION_DOWN);
	//	mario->positionOffset.y=-4;
	}
}

 
