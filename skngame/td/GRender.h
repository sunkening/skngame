// GRender.h: interface for the GRender class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GRENDER_H
#define GRENDER_H
#include <list>
#include <set>
#include <vector>
#include <string>
using namespace std;
#include "GObject.h"
#include "GViewPort.h"
#include "GFrame.h"
#include "G2DPoint.h"
#include "BitMapFile.h"
 
class GScene;
class GRenderer : public GObject  
{
public:
	int *buffer;
	int  pitch;
	GFrame* screen;
	int min_clip_x;
	int max_clip_x;
	int min_clip_y;
	int max_clip_y;
public:
	GRenderer();
	virtual ~GRenderer();
	virtual GViewPort *createViewPort(G2DPoint world,G2DPoint screen,int width,int height,int lowColor=0,int highColor=0)=0;
	virtual GFrame * createFrame(BitMapFile * bitmap,int lowColor=0,int highColor=0)=0;
	virtual GFrame * createFrame(int width,int height,int lowColor=0,int highColor=0)=0;
	virtual GFrame * createFrame(char * filename,int lowColor=0,int highColor=0)=0;
	virtual void drawToBack(GFrame * frame ,int x, int y,   int transparent)=0;
	virtual void render(HWND hwnd,GScene *s,vector<GViewPort*> *viewPortList)=0;
	virtual	void  flip()=0;
	virtual void drawText(const char *text, int x,int y,int color,GFrame* frame)=0;
	virtual void fillSurface(GFrame*f,int color, RECT *client=null)=0;
	virtual void blit(GFrame * source ,int x,int y,int width,int height,GFrame *   target,  int transparent)=0;
	//virtual void fillSurface(LPDIRECTDRAWSURFACE7 lpdds, int color, RECT *client=0)=0;

	//
	//virtual void   beginPaint(GFrame* frame,int **pbuffer,int & pitch)=0;
//	virtual void  endPaint(GFrame* frame)=0;

	virtual void   beginPaint(GFrame* frame )=0;
	
	
	virtual void drawClipLine(int min_clip_x,int max_clip_x,int min_clip_y,int max_clip_y,G2DPoint a,G2DPoint b,int color)const =0 ;
	virtual void drawClipLine( G2DPoint a,G2DPoint b,int color)const=0 ;
	virtual void drawPoint(G2DPoint p,int color)const=0 ;
	virtual int getPointColor(G2DPoint p)const=0 ;
	virtual void drawTriangle(G2DPoint p1,G2DPoint p2,G2DPoint p3,int color)const=0 ;
	
 virtual void  endPaint( )=0;
	//virtual void renderToViewPort(list<GFrame*> frameList,GViewPort * viewPort)=0;
};

#endif  
