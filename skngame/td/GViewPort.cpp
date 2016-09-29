// GViewPort.cpp: implementation of the GViewPort class.
//
//////////////////////////////////////////////////////////////////////

#include "GViewPort.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GViewPort::GViewPort()
{
	enable=true;
	width=0;
	height=0;
	backgroundColor=0;
	canvas=null;
}
GViewPort::GViewPort( G2DPoint world,G2DPoint screen,int width,int height)
{
//	canvas=c;
	this->world=world;
	this->screen=screen;
	enable=true;
	backgroundColor=0;
	this->height=height;
	this->width=width;
}
GViewPort::~GViewPort()
{
//	if(surface)delete surface;
}
void GViewPort::scrollRight(int pix)
{
	world.x+=pix;
}
void GViewPort::scrollLeft(int pix)
{
	world.x-=pix;
}
void GViewPort::scrollUp(int pix)
{
	world.y-=pix;
}
void GViewPort::scrollDown(int pix)
{
	world.y+=pix;
}
G2DPoint GViewPort::worldToViewPort(G2DPoint & w){
	G2DPoint  s;
	s.x=w.x-world.x;
	s.y=world.y-w.y;
	return s;
}

G2DPoint GViewPort::worldToViewPort(G2DPointf & w)
{
	G2DPoint new_word(w);
	G2DPoint  s;
	s.x=new_word.x-world.x;
	s.y=world.y-new_word.y;
	return s;
}

G2DPoint GViewPort::screenToWorld(G2DPoint & s)
{
	return screenToWorld(s.x,s.y);
}

G2DPoint GViewPort::screenToWorld(int x,int y)
{
	G2DPoint view(x-screen.x,y-screen.y);
	G2DPoint w;
	w.x=world.x+view.x;
	w.y=world.y-view.y;
	return w;
}
