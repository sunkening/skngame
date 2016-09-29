// GSpiritAnimation1.cpp: implementation of the GSpiritAnimation class.
//
//////////////////////////////////////////////////////////////////////

#include "GSpiritAnimation.h"
#include "System.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GSpiritAnimation::GSpiritAnimation()
{
	animationGroup=null;
	directionAmount=0;
	curDirection=0;
	curState=0;
	lastTime=0;
	speed=0;
}

GSpiritAnimation::GSpiritAnimation(int i)
{
	new(this) GSpiritAnimation;
	id=i;
}

GSpiritAnimation::~GSpiritAnimation()
{
	if (animationGroup)
	{
		delete animationGroup;
		animationGroup=null;
	}
}



GFrame * GSpiritAnimation::getFrameToRender()
{
	
	return	nextFrame();
}

void GSpiritAnimation::setDirectionAmount(int num)
{
	animationGroup->directionVector.resize(num);
	directionAmount=num;
}

void GSpiritAnimation::addAnimation(GAnimation* anim,int direction/*=0*/)
{
	animationGroup->add(direction,anim);
}
void GSpiritAnimation::change (int d,int s)
{
	curDirection=d;
	curState=s;
}

void GSpiritAnimation::changeState(int s)
{
	curState=s;
}

void GSpiritAnimation::changeDirection(int d)
{
	curDirection=d;
	
}

GFrame * GSpiritAnimation::nextFrame()
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
	
	if(curFrameIndex<0)curFrameIndex=0;//-1代表最后一帧
	if(curFrameIndex>=animation->totalFrames)curFrameIndex=0;	
		
	return animation->framesVector.at(curFrameIndex);
}
