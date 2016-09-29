// GColor.cpp: implementation of the GColor class.
//
//////////////////////////////////////////////////////////////////////

#include "GColor.h"
#include <WINDOWS.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GColor::GColor()
{
	value=0;
}

GColor::GColor(int a,int r,int g,int b)
{
	this->a=a;
	this->b=b;
	this->g=g;
	this->r=r;
}

GColor::~GColor()
{

}

int GColor::RGBA(int r,int g,int b,int a/*=0*/)
{
	return a + (b<<8) + (g<<16) + (r<<24);
}
int GColor::ARGB(int a,int r,int g,int b )
{
	return b + (g<<8) + (r<<16) + (a<<24);
}
 
void GColor::assign(int r,int g,int b,int a)
{
	this->a=a;
	this->b=b;
	this->g=g;
	this->r=r;
}

void GColor::assign(int v)
{
	value=v;
}

int GColor::RGB_(int r,int g,int b)
{
	return b + (g<<8) + (r<<16) ;
}



//******************************************************
int GColorInt::getColor()
{
 
return RGB((b > 255 ? 255 : b),(g > 255 ? 255 : g),(r > 255 ? 255 : r));
}

GColorInt::GColorInt()
{
	this->a=0;
	this->b=0;
	this->g=0;
	this->r=0;
}

GColorInt::GColorInt(int r,int g,int b,int a)
{
	this->a=a;
	this->b=b;
	this->g=g;
	this->r=r;
}
//***********************************************************
GColorFloat::GColorFloat()
{
	this->a=0;
	this->b=0;
	this->g=0;
	this->r=0;
}

GColorFloat::GColorFloat(float r,float g,float b,float a/*=0*/)
{
	this->a=a;
	this->b=b;
	this->g=g;
	this->r=r;
}

int GColorFloat::getColor()
{
	return 	GColor::RGBA((r > 1 ? 255 : r*255),(g > 1 ? 255 : g*255),(b > 1 ? 255 : b*255),(a > 1 ? 255 : a*255));
}

GColorRGBA::GColorRGBA()
{
	
}

GColorRGBA::GColorRGBA(int r,int g,int b,int a)
{
	this->a=a;
	this->b=b;
	this->g=g;
	this->r=r;
}
