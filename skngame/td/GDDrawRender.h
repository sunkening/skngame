// GDDrawRender.h: interface for the GDDrawRender class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GDDRAWRENDERER_H
#define GDDRAWRENDERER_H
#include <list>
#include <set>
using namespace std;
#include "GRender.h"
#include "GDDrawViewPort.h"
#include "GDDrawFrame.h"
#include "G2DPoint.h"
#include "GScene.h"
#include "GSpirit.h"
#include "GLayer.h"
#include "GLogger.h"
class GDDrawRenderer : public GRenderer  
{
public:
	GDDrawRenderer();
	virtual ~GDDrawRenderer();
	virtual GViewPort * createViewPort(G2DPoint world,G2DPoint screen,int width,int height,int lowColorKey=0,int highColorKey=0);
	virtual GFrame * createFrame(BitMapFile * bitmap,int lowColorKey=0,int highColorKey=0);
	virtual GFrame * createFrame(char * filename,int lowColorKey=0,int highColorKey=0);
	//lowColor=-1,表示没有关键色
	virtual GFrame * createFrame(int width,int height,int lowColor=0,int highColor=0) ;
	virtual void drawToBack(GFrame * frame ,int x, int y,  int transparent=0);
	virtual void drawToBack(GFrame * frame ,int x, int y, int width,int height, int transparent=0);
	virtual	void drawToBack(GSpirit * spirit ,  int transparent=0);
	virtual void drawText(const char *text, int x,int y,int color,GFrame* frame);
	virtual void render(HWND hwnd,GScene * s,vector<GViewPort*> *viewPortlist);
	virtual void renderLayer(GLayer *layer,GViewPort * viewPort);
	virtual	void  flip();
//	virtual void fillSurface(LPDIRECTDRAWSURFACE7 lpdds, int color, RECT *client);

	/////



	
	virtual void fillSurface(GFrame*f,int color, RECT *client=null);
	virtual void blit(GFrame * source ,int x,int y,int width,int height,GFrame * target, int transparent);
	
	
	/////
private :
	LPDIRECTDRAWSURFACE7 canvas;

	void drawToCanvas(GSpirit * spirit);
	void drawToSurface(GSpirit * spirit ,LPDIRECTDRAWSURFACE7  target,  int transparent);
	void drawToSurface(GFrame * frame ,int x,int y,int width,int height,LPDIRECTDRAWSURFACE7  target,  int transparent);
	void renderToViewPort(map<int,GLayer*> *layerMap,GViewPort * viewPort);
public:	

	virtual void beginPaint(GFrame* frame);
	
	virtual void drawClipLine(int min_clip_x,int max_clip_x,int min_clip_y,int max_clip_y, G2DPoint a,G2DPoint b,int color)const;
	virtual void drawClipLine( G2DPoint a,G2DPoint b,int color )const;
	virtual void drawPoint(G2DPoint p,int color )const;
	virtual int	getPointColor(G2DPoint p )const;
			void drawLine(G2DPoint a,G2DPoint b,int color)const;
	virtual void drawTriangle(G2DPoint p1,G2DPoint p2,G2DPoint p3,int color)const;
		//画平顶三角
		void drawTopTriangle(int,int ,int ,int ,int ,int,int )const;
		//画平底三角
		void drawBottomTriangle(int,int ,int ,int ,int ,int,int)const;
	virtual void endPaint();

	
	
};

#endif 