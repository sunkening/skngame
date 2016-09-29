// GFrame.cpp: implementation of the GFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "GFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GFrame::GFrame()
{
	width=0;
	height=0;
	referenceCount=0;
	id=0;
	transparent=false;
}

GFrame::~GFrame()
{

}

void* GFrame::getSurface()
{
	return null;
}
int GFrame::getWidth()
{
	return width;
}
int GFrame::getHeight()
{
	return height;
}

