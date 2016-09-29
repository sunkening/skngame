// GDDraw.h: interface for the GDDraw class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GDDRAW_H
#define GDDRAW_H
#include "BitMapFile.h"
#include "gl.h"
 

class GDDraw  
{
public:
	static LPDIRECTDRAW7 directDraw7 ;   // dd object
	static	LPDIRECTDRAWSURFACE7  primarySurface  ;   // dd primary surface
	static	LPDIRECTDRAWSURFACE7  backSurface     ;   // dd back surface
	static	int	clientHeight  ;//客户显示区高,像素
	static int	clientWidth    ;//客户显示区宽,像素
	static int	clientBpp      ;//像素格式
	static int lowColorKey;//关键色/透明色
	static int highColorKey;//关键色/透明色
	static bool isWindow;
	static RECT clientRect; 
private:
//	LPDIRECTDRAWPALETTE   lpddpal       ;   // a pointer to the created dd palette
//	LPDIRECTDRAWCLIPPER  clipper;          // dd clipper for back surface
//	LPDIRECTDRAWCLIPPER  clipperWin;       // dd clipper for window
//	DDSURFACEDESC2        surfaceDesc; 
	//RECT clientRect;  // used to hold client rectangle

public:
	GDDraw();
	virtual ~GDDraw();
	static void	initBack(HWND main_window_handle);
	static int		init(bool windowed,HWND main_window_handle,int width, int height, int bpp );
	static 	int		fillSurface(LPDIRECTDRAWSURFACE7 surface,int color, RECT *client=NULL);
	static 	LPDIRECTDRAWSURFACE7	createSurface(int width, int height, int mem_flags, int lowColor=0 ,int highColor=0);
	static 	LPDIRECTDRAWSURFACE7	createSurface(UCHAR * bitmapBuffer,int width,int height,int lowColor=0 ,int highColor=0);
	static LPDIRECTDRAWSURFACE7  createSurface(const BitMapFile * bitmap,int lowColor,int highColor );
	static LPDIRECTDRAWCLIPPER	attachClipper(LPDIRECTDRAWSURFACE7 lpdds, int num_rects, LPRECT clip_list);
	static int  drawToBack(LPDIRECTDRAWSURFACE7 source, int x, int y, int width, int height,  int transparent=1);
	static int  drawToSurface(LPDIRECTDRAWSURFACE7 source,LPDIRECTDRAWSURFACE7 target, int x, int y, int width, int height,  int transparent=1);
	static void release();
	static int  flip();
	static	void  initWindowRect(HWND main_window_handle);
	static void resetClientRect(HWND main_window_handle);
	static 	int		fillBack(int color, RECT *client=NULL);
};

#endif  
