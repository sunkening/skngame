// GDDrawViewPort.h: interface for the GDDrawViewPort class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GDDRAWVIEWPORT_H
#define GDDRAWVIEWPORT_H
#include "G2DPoint.h"
#include "GViewPort.h"
#include "GDDrawFrame.h"

class GDDrawViewPort : public GViewPort  
{
public:
	GDDrawViewPort();
	GDDrawViewPort(G2DPoint world,G2DPoint screen,int width,int height,LPDIRECTDRAWSURFACE7 surface,LPDIRECTDRAWCLIPPER lpddclipper);
	virtual ~GDDrawViewPort();
private :
//	LPDIRECTDRAWSURFACE7 canvas;
	LPDIRECTDRAWCLIPPER clipper;
	//void* getCanvas();
};

#endif  