// GCursor.cpp: implementation of the GCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "GCursor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GCursor::GCursor()
{
	x=0;
	y=0;
	leftButton=false;
	rightButton=false;
}

GCursor::~GCursor()
{

}

void GCursor::init(BitMapFile*bitmap,int width,int lowcolor/*=0*/,int heighcolor/*=0*/)
{
	animationGroup=new GAnimationGroup(1);
	addAnimation(bitmap,width,lowcolor,heighcolor);
}

void GCursor::addAnimation(BitMapFile*bitmap,int width,int lowcolor/*=0*/,int heighcolor/*=0*/)
{
	GAnimation *anim=new GAnimation;
	anim->init(bitmap,width,lowcolor,heighcolor);
	animationGroup->add(0,anim);
}

int GCursor::getX()
{
	return x;
}

int GCursor::getY()
{
	return y;
}

bool GCursor::pressLeft()
{
	return leftButton;
}

bool GCursor::pressRight()
{
	return rightButton;
}


