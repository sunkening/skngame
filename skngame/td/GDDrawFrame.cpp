// GDDrawFrame.cpp: implementation of the GDDrawFrame class.
//
//////////////////////////////////////////////////////////////////////





#include "GDDrawFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GDDrawFrame::GDDrawFrame()
{
	 

}
GDDrawFrame::GDDrawFrame(int w ,int h ,LPDIRECTDRAWSURFACE7   s)
{
 
	width=w;
	height=h;
	surface=s;
	transparent=false;
}
GDDrawFrame::GDDrawFrame(BitMapFile * bitmap,int lowColor,int highColor)
{
	if (lowColor!=-1)
	{
		transparent=true;
	}else{
		lowColor=0;
		highColor=0;
		transparent=false;
	}
	surface=GDDraw::createSurface(bitmap,  lowColor ,highColor);
	width=bitmap->bitmapinfoheader.biWidth;
	height=bitmap->bitmapinfoheader.biHeight;
}
 
GDDrawFrame::GDDrawFrame(char* fileName,int lowColor,int highColor)
{
	if (lowColor!=-1)
	{
		transparent=true;
	}else{
		lowColor=0;
		highColor=0;
		transparent=false;
	}
	BitMapFile * bitmap=new BitMapFile(fileName);
	surface=GDDraw::createSurface(bitmap,  lowColor ,highColor);
	width=bitmap->bitmapinfoheader.biWidth;
	height=bitmap->bitmapinfoheader.biHeight;
	delete bitmap;
}
GDDrawFrame::GDDrawFrame(int width,int height,int lowColor,int highColor)
{
	if (lowColor!=-1)
	{
		transparent=true;
	}else{
		lowColor=0;
		highColor=0;
		transparent=false;
	}
	
	surface=GDDraw::createSurface(width,height, 0, lowColor ,highColor);
	this->width=width;
	this->height=height;
}
GDDrawFrame::~GDDrawFrame()
{
	if(surface)
		surface->Release();
}

void* GDDrawFrame::getSurface()
{
	return surface;
}