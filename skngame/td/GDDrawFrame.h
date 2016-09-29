// GDDrawFrame.h: interface for the GDDrawFrame class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GDDRAWFRAM_H
#define GDDRAWFRAM_H
#include <ddraw.h> // include directdraw
#include "GDDraw.h"
#include "GFrame.h"
#include "BitMapFile.h"
class GDDrawFrame : public GFrame  
{
public :
	LPDIRECTDRAWSURFACE7  surface ;
public:
	GDDrawFrame();
	GDDrawFrame(int width,int height,LPDIRECTDRAWSURFACE7 s);
	GDDrawFrame(BitMapFile * bitmap,int lowColor,int highColor);
	GDDrawFrame(char* fileName,int lowColor,int highColor);
	GDDrawFrame(int width,int height, int lowColor,int highColor);
	virtual ~GDDrawFrame();
	virtual void* getSurface();


};

#endif  
