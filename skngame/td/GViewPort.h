// GViewPort.h: interface for the GViewPort class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GVIEWPORT_H
#define GVIEWPORT_H
#include <stdio.h>
#include <string>
#include "GObject.h"
#include "G2DPoint.h"
#include "GFrame.h"
#include "gl.h"
class GViewPort : public GObject  
{
public:
	string name;
	G2DPoint world;//左上角的世界坐标,像素
	int width,height;//大小,像素
	int backgroundColor;
	G2DPoint screen;//像素,屏幕坐标
	bool enable;
	GFrame* canvas;
	//GFrame  *surface    ;   // dd back surface
public:
	GViewPort();
	GViewPort(G2DPoint world,G2DPoint screen,int width,int height);
	virtual ~GViewPort();
	virtual	GFrame* getCanvas() {return canvas;};
	void scrollRight(int pix);
	void scrollLeft(int pix);
	void scrollUp(int pix);
	void scrollDown(int pix);
	G2DPoint   worldToViewPort(G2DPoint & w);
	G2DPoint   worldToViewPort(G2DPointf & w);
	G2DPoint screenToWorld(G2DPoint & s);
	G2DPoint screenToWorld(int x,int y);
};

#endif  


