// GAnimationManager.cpp: implementation of the GAnimationManager class.
//
//////////////////////////////////////////////////////////////////////

#include "GAnimationManager.h"
#include "System.h"
#include <IOSTREAM>
#include "GAnimation.h"
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GAnimationManager::GAnimationManager()
{
 
	curDirection=0;
	curState=0;
	curFrameIndex=0;
	speed=0;
	animationGroup=null;
	lastTime=0;
}

GAnimationManager::~GAnimationManager()
{
	if (animationGroup)
	{
		delete animationGroup;
		animationGroup=null;
	}
}



void GAnimationManager::change (int d,int s)
{
	curDirection=d;
	curState=s;
}

GFrame * GAnimationManager::nextFrame()
{ 

	if ( (GSystem::tickCount-lastTime) > speed )
	{
		curFrameIndex++;
		lastTime=GSystem::tickCount;	
	}
	GAnimation * animation=animationGroup->getAnimation(curDirection,curState);
	if (animation==null)
	{
		return null;
	}
	if(curFrameIndex<0)curFrameIndex=-1;//-1代表最后一帧
	if(curFrameIndex>=animation->totalFrames)curFrameIndex=0;	
	return animation->framesVector.at(curFrameIndex);
}


