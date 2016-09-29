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
	G2DPoint world;//���Ͻǵ���������,����
	int width,height;//��С,����
	int backgroundColor;
	G2DPoint screen;//����,��Ļ����
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


