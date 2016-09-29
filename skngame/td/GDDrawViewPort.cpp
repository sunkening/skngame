// GDDrawViewPort.cpp: implementation of the GDDrawViewPort class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw
#include "GDDrawViewPort.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GDDrawViewPort::GDDrawViewPort()
{

}

GDDrawViewPort::~GDDrawViewPort()
{
	if(canvas){	 
//  		canvas->Release();
	//	canvas=null;
	}
	if(clipper){
	 	clipper->Release();
		clipper=null;
	}

}
GDDrawViewPort::GDDrawViewPort(G2DPoint world,G2DPoint screen,int width,int height,LPDIRECTDRAWSURFACE7 surface,LPDIRECTDRAWCLIPPER  clipper)
:GViewPort( world, screen,  width, height)
{
	this->canvas=new GDDrawFrame(width,height,surface);
	//this->canvas=surface;
	this->clipper=clipper;
	
}
/*
void* GDDrawViewPort::getCanvas()
{
	return canvas;
}
*/