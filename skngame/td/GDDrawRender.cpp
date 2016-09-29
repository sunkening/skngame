// GDDrawRender.cpp: implementation of the GDDrawRender class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>   // include important windows stuff
#include"GInput.h"
#include <ddraw.h> // include directdraw
#include "GDDrawRender.h"
#include "GMath.h"
#include "g3dlib.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GDDrawRenderer::GDDrawRenderer()
{
	canvas=null;
}

GDDrawRenderer::~GDDrawRenderer()
{

}
GViewPort * GDDrawRenderer::createViewPort(G2DPoint world,G2DPoint screen,int width,int height,int lowcolor,int highcolor)
{
	RECT viewRect;
	viewRect.left=0;
	viewRect.right=width;
	viewRect.top=0;
	viewRect.bottom=height;	
	//给此视口创建表面
	LPDIRECTDRAWSURFACE7  surface=GDDraw::createSurface(width,height,0,lowcolor,highcolor);
	//给此表面创建裁剪器
	LPDIRECTDRAWCLIPPER clipper=GDDraw::attachClipper(surface,1,&viewRect);
	GDDrawViewPort *viewport=new GDDrawViewPort(world,screen, width, height,surface,clipper);
	return viewport;
}
GFrame * GDDrawRenderer::createFrame(BitMapFile * bitmap,int lowcolor,int highcolor)
{
	GDDrawFrame *f=new GDDrawFrame(bitmap,lowcolor,highcolor);
	return f;
}
GFrame * GDDrawRenderer::createFrame(char * filename,int lowcolor,int highcolor)
{	
	BitMapFile * bitmap=new BitMapFile(filename);
	GDDrawFrame *f=new GDDrawFrame(bitmap,lowcolor,highcolor);
	return f;
}
GFrame * GDDrawRenderer::createFrame(int width,int height,int lowColor,int highColor)
{
	GDDrawFrame *f=new GDDrawFrame(width,height,lowColor,highColor);
	return f;
}
void GDDrawRenderer::render(HWND hwnd,GScene *scene,vector<GViewPort*> *viewPortlist)
{	
	GDDraw::fillBack(0);//用黑色填充窗口
	GDDraw::resetClientRect(hwnd);//窗口模式下，获取窗口的新位置
	vector<GViewPort*>::iterator viewPortIter;
	for(viewPortIter=viewPortlist->begin();viewPortIter!=viewPortlist->end();viewPortIter++){
		LPDIRECTDRAWSURFACE7 canvas=(LPDIRECTDRAWSURFACE7)(*viewPortIter)->getCanvas()->getSurface();

	//	GDDraw::fillSurface(canvas,(*viewPortIter)->backgroundColor);
		GDDraw::fillSurface(canvas,(*viewPortIter)->backgroundColor);
	
		renderToViewPort(scene->getSortedLayers(),*viewPortIter);
	
		//把视口表面画到后备缓冲
		int x=(*viewPortIter)->screen.x;
		int y=(*viewPortIter)->screen.y;	 
		GDDraw::drawToBack(canvas,x,y,(*viewPortIter)->width,(*viewPortIter)->height,1);
		
	}
	if (GInput::cursor->isDisplay)
	{
		GFrame* f=GInput::cursor->getFrameToRender();
		GDDraw::drawToBack((LPDIRECTDRAWSURFACE7)f->getSurface(),GInput::cursor->getX(),GInput::cursor->getY(), f->getWidth(),f->getHeight(),1);
	}
	

}
void GDDrawRenderer::flip()
{
	GDDraw::flip();
}
void GDDrawRenderer::renderLayer(GLayer *layer,GViewPort * viewPort)
{
	canvas=(LPDIRECTDRAWSURFACE7)viewPort->getCanvas()->getSurface();
	int renderPosition=layer->renderPosition;
	vector<GSpirit*> *v=& layer->spirits;
	vector<GSpirit*>::iterator iter;
	switch(renderPosition)
	{
		case RENDERTYPE_WORLD :
		{
			
			for (iter=v->begin();iter!=v->end();iter++)
			{
				GSpirit* spirit=*iter;
				
				if (!spirit->isDisplay)
				{
					continue;
				}
				G2DPoint viewPortPosition=viewPort->worldToViewPort(spirit->position.toIntPoint()+spirit->renderPosition);
				GFrame * frame=spirit->getFrameToRender();
				if (!frame)
				{
					return;
				}
				drawToSurface(frame,viewPortPosition.x,viewPortPosition.y-frame->getHeight(),frame->getWidth(),frame->getHeight(),canvas,  1);
		
			}
		}break;
		case RENDERTYPE_VIEWPORT :
		{
			for (iter=v->begin();iter!=v->end();iter++)
			{
				GSpirit* spirit=*iter;
				
				if (!spirit->isDisplay)
				{
					continue;
				}
				G2DPoint viewPortPosition=viewPort->worldToViewPort(spirit->position.toIntPoint());
				GFrame * frame=spirit->getFrameToRender();
				drawToSurface(frame ,viewPortPosition.x,viewPortPosition.y-frame->getHeight(),frame->getWidth(),frame->getHeight(),canvas,  1);

			}
		}break;
		case RENDERTYPE_SCREEN :
		{
			
		}break;
		default:break;
	
	
	
	}
	if (layer->showGrid)
	{
		GFrame* grid=layer->getGrid(viewPort);
		if (grid)
		{
			drawToSurface(grid,0,0,grid->getWidth(),grid->getHeight(),canvas,  1);
		}
	}
}



void GDDrawRenderer::drawToBack(GFrame * frame ,int x, int y, int transparent)
{
	LPDIRECTDRAWSURFACE7  surface=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	GDDraw::drawToBack(surface,x,y,frame->getWidth(),frame->getHeight(),1);
}

void GDDrawRenderer::drawToBack(GFrame * frame ,int x, int y, int width,int height, int transparent)
{
	LPDIRECTDRAWSURFACE7  surface=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	GDDraw::drawToBack(surface,x,y,width,height,1);
}
void GDDrawRenderer::drawToBack(GSpirit * spirit ,  int transparent)
{
	GFrame *frame=spirit->getFrame();
	LPDIRECTDRAWSURFACE7  surface=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	GDDraw::drawToBack(surface,spirit->position.x,spirit->position.y,spirit->getWidth(),spirit->getHeight(),1);
}
void GDDrawRenderer::drawToSurface(GSpirit * spirit ,LPDIRECTDRAWSURFACE7  target,  int transparent)
{
	GFrame *frame=spirit->getFrame();

	drawToSurface(  frame ,  spirit->position.x,spirit->position.y  ,spirit->getWidth(),spirit->getHeight(),target, transparent);
	//LPDIRECTDRAWSURFACE7  spiritSurface=(LPDIRECTDRAWSURFACE7)frame->getSurface();		 
//	GDDraw::drawToSurface(spiritSurface,target,0,0,spirit->getWidth(),spirit->getHeight(),1);
}

void GDDrawRenderer::drawToSurface(GFrame * frame ,int x,int y,int width,int height,LPDIRECTDRAWSURFACE7  target,  int transparent)
{
	LPDIRECTDRAWSURFACE7  spiritSurface=(LPDIRECTDRAWSURFACE7)frame->getSurface();		 
	GDDraw::drawToSurface(spiritSurface,target,x,y,width,height,frame->transparent);
}
void GDDrawRenderer::renderToViewPort(map<int,GLayer*> *layerMap,GViewPort * viewPort)
{
	map<int,GLayer*>::iterator layerIter;
 
	for(layerIter=layerMap->begin();layerIter!=layerMap->end();layerIter++)
	{
		
		renderLayer((*layerIter).second, viewPort);
	
	}
}
void GDDrawRenderer::drawText(const char *text, int x,int y,int color,GFrame* frame)
{
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	HDC xdc; 
	if (FAILED(lpdds->GetDC(&xdc)))
		return;
	 HFONT hFont  = CreateFont
                        (
                            20,0,    //高度20, 宽取0表示由系统选择最佳值
                            0, 0,    //文本倾斜，与字体倾斜都为0
                            FW_HEAVY,    //粗体
                            0,0,0,        //非斜体，无下划线，无中划线
                            GB2312_CHARSET,    //字符集
                            OUT_DEFAULT_PRECIS,        
                            CLIP_DEFAULT_PRECIS,        
                            DEFAULT_QUALITY,        //一系列的默认值
                            DEFAULT_PITCH | FF_DONTCARE,    
                            "自定义字体"    //字体名称
                        );
            SetTextColor(xdc, color);
            SelectObject(xdc, hFont);
            //TextOut(hdc, x, y, lpszTx2, strlen(lpszTx2));
//	SetBkMode(xdc, TRANSPARENT);
	TextOut(xdc,x,y,text,strlen(text));
	lpdds->ReleaseDC(xdc);
}
void GDDrawRenderer::drawPoint(G2DPoint p,int color)const
{
	*(buffer + p.x + p.y*(pitch))= color;
}
int GDDrawRenderer::getPointColor(G2DPoint p)const
{
	int color=*(buffer + p.x + p.y*(pitch));
	return color;
}
/*
void   GDDrawRenderer::beginPaint( GFrame *frame,int **pbuffer,int & pitch)
{
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	DDSURFACEDESC2 ddsd; 
	DDRAW_INIT_STRUCT(ddsd); 
	lpdds->Lock(NULL,&ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);
	pitch=ddsd.lPitch>>2;
	*pbuffer= (int* )ddsd.lpSurface;

}*/

void GDDrawRenderer::beginPaint(GFrame* frame)
{
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	DDSURFACEDESC2 ddsd; 
	DDRAW_INIT_STRUCT(ddsd); 
	lpdds->Lock(NULL,&ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,NULL);
	pitch=ddsd.lPitch>>2;
	buffer= (int* )ddsd.lpSurface;
	screen=frame;
	min_clip_x=0;
	max_clip_x=frame->getWidth()-1;
	min_clip_y=0;
	max_clip_y=frame->getHeight()-1;
}

/*
void GDDrawRenderer::endPaint(GFrame *frame)
{
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	lpdds->Unlock(null);
}*/

void GDDrawRenderer::endPaint()
{
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)screen->getSurface();
	lpdds->Unlock(null);
	screen=0;
	pitch=0;
	buffer=0;
}

void GDDrawRenderer::drawToCanvas(GSpirit * spirit)
{
	
}

void GDDrawRenderer::fillSurface(GFrame*frame,int color, RECT *client/*=null*/)
{
	
	LPDIRECTDRAWSURFACE7  lpdds=(LPDIRECTDRAWSURFACE7)frame->getSurface();
	
	GDDraw::fillSurface(lpdds,color,client);
}

void GDDrawRenderer::blit(GFrame * source ,int x,int y,int width,int height,GFrame * target, int transparent)
{
	LPDIRECTDRAWSURFACE7  t=(LPDIRECTDRAWSURFACE7)target->getSurface();

  	LPDIRECTDRAWSURFACE7  s=(LPDIRECTDRAWSURFACE7)source->getSurface();
				 
	GDDraw::drawToSurface(s,t,x,y,width,height,source->transparent);
}

void GDDrawRenderer::drawClipLine(int min_clip_x,int max_clip_x,int min_clip_y,int max_clip_y, 
								  G2DPoint a,G2DPoint b,int color)const
{	
	if (  GMath::clipLine(a.x,a.y,b.x,b.y,
			  min_clip_x,  max_clip_x,  min_clip_y,  max_clip_y))
	{
		drawLine(a, b, color);
	}
}

void GDDrawRenderer::drawClipLine(G2DPoint a,G2DPoint b,int color)const
{
	if (  GMath::clipLine(a.x,a.y,b.x,b.y,
		min_clip_x,  max_clip_x,  min_clip_y,  max_clip_y))
	{
		drawLine(a, b, color);
	}
}

void GDDrawRenderer::drawLine(G2DPoint a,G2DPoint b,int color)const
{
	int *vb_start=buffer;
int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping
	//lpitch=lpitch>>2;
// pre-compute first pixel address in video buffer
	vb_start = vb_start + a.x + a.y*pitch;

// compute horizontal and vertical deltas
dx = b.x-a.x;
dy = b.y-a.y;

// test which direction the line is going in i.e. slope angle
if (dx>=0)
   {
   x_inc = 1;

   } // end if line is moving right
else
   {
   x_inc = -1;
   dx    = -dx;  // need absolute value

   } // end else moving left

// test y component of slope

if (dy>=0)
   {
   y_inc = pitch;
   } // end if line is moving down
else
   {
   y_inc = -pitch;
   dy    = -dy;  // need absolute value

   } // end else moving up

// compute (dx,dy) * 2
dx2 = dx << 1;
dy2 = dy << 1;

// now based on which delta is greater we can draw the line
if (dx > dy)
   {
   // initialize error term
   error = dy2 - dx; 

   // draw the line
   for (index=0; index <= dx; index++)
       {
       // set the pixel
       *vb_start = color;

       // test if error has overflowed
       if (error >= 0) 
          {
          error-=dx2;

          // move to next line
          vb_start+=y_inc;

	   } // end if error overflowed

       // adjust the error term
       error+=dy2;

       // move to the next pixel
       vb_start+=x_inc;

       } // end for

   } // end if |slope| <= 1
else
   {
   // initialize error term
   error = dx2 - dy; 

   // draw the line
   for (index=0; index <= dy; index++)
       {
       // set the pixel
       *vb_start = color;

       // test if error overflowed
       if (error >= 0)
          {
          error-=dy2;

          // move to next line
          vb_start+=x_inc;

          } // end if error overflowed

       // adjust the error term
       error+=dx2;

       // move to the next pixel
       vb_start+=y_inc;

       } // end for

   } // end else |slope| > 1

 
}

void GDDrawRenderer::drawTriangle(G2DPoint p1,G2DPoint p2,G2DPoint p3,int color)const
{
	int x1=p1.x;
	int y1=p1.y;
	int x2=p2.x;
	int y2=p2.y;
	int x3=p3.x;
	int y3=p3.y;

	int temp_x, // used for sorting
		temp_y,
		new_x;
	
	// test for h lines and v lines
	if ((x1==x2 && x2==x3)  ||  (y1==y2 && y2==y3))
		return;
	
	// sort p1,p2,p3 in ascending y order
	if (y2<y1)
	{
		temp_x = x2;
		temp_y = y2;
		x2     = x1;
		y2     = y1;
		x1     = temp_x;
		y1     = temp_y;
	} // end if
	// now we know that p1 and p2 are in order
	if (y3<y1)
	{
		temp_x = x3;
		temp_y = y3;
		x3     = x1;
		y3     = y1;
		x1     = temp_x;
		y1     = temp_y;
	} // end if
	// finally test y3 against y2
	if (y3<y2)
	{
		temp_x = x3;
		temp_y = y3;
		x3     = x2;
		y3     = y2;
		x2     = temp_x;
		y2     = temp_y;
	} // end if
	// do trivial rejection tests for clipping
	if ( y3<min_clip_y || y1>max_clip_y ||
		(x1<min_clip_x && x2<min_clip_x && x3<min_clip_x) ||
		(x1>max_clip_x && x2>max_clip_x && x3>max_clip_x) )
		return;
	// test if top of triangle is flat
	if (y1==y2)
	{
		drawTopTriangle(x1,y1,x2,y2,x3,y3,color );
	} // end if
	else if (y2==y3)
	{
		drawBottomTriangle(x1,y1,x2,y2,x3,y3,color);
	} // end if bottom is flat
	else
	{
		// general triangle that's needs to be broken up along long edge
		new_x = x1 + (int)(0.5+(float)(y2-y1)*(float)(x3-x1)/(float)(y3-y1));
		// draw each sub-triangle
		drawBottomTriangle(x1,y1,new_x,y2,x2,y2,color);
		drawTopTriangle(x2,y2,new_x,y2,x3,y3,color);
	} // end else
}

void GDDrawRenderer::drawTopTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int color)const
{
	
float dx_right,    // the dx/dy ratio of the right edge of line
      dx_left,     // the dx/dy ratio of the left edge of line
      xs,xe,       // the starting and ending points of the edges
      height;      // the height of the triangle

int temp_x,        // used during sorting as temps
    temp_y,
    right,         // used by clipping
    left;

// cast dest buffer to ushort
int *dest_buffer =  buffer;

// destination address of next scanline
int  *dest_addr = NULL;

 

// test order of x1 and x2
if (x2 < x1)
   {
   temp_x = x2;
   x2     = x1;
   x1     = temp_x;
   } // end if swap

// compute delta's
height = y3-y1;

dx_left  = (x3-x1)/height;
dx_right = (x3-x2)/height;

// set starting points
xs = (float)x1;
xe = (float)x2;

// perform y clipping
if (y1 < min_clip_y)
   {
   // compute new xs and ys
   xs = xs+dx_left*(float)(-y1+min_clip_y);
   xe = xe+dx_right*(float)(-y1+min_clip_y);

   // reset y1
   y1=min_clip_y;

   } // end if top is off screen

if (y3>max_clip_y)
   y3=max_clip_y;

// compute starting address in video memory
dest_addr = dest_buffer+y1*pitch;

// test if x clipping is needed
if (x1>=min_clip_x && x1<=max_clip_x &&
    x2>=min_clip_x && x2<=max_clip_x &&
    x3>=min_clip_x && x3<=max_clip_x)
    {
    // draw the triangle
    for (temp_y=y1; temp_y<=y3; temp_y++,dest_addr+=pitch)
        {
        // draw the line
        Mem_Set_QUAD(dest_addr+(unsigned int)xs,color,(unsigned int)((int)xe-(int)xs+1));

        // adjust starting point and ending point
        xs+=dx_left;
        xe+=dx_right;

        } // end for

    } // end if no x clipping needed
else
   {
   // clip x axis with slower version

   // draw the triangle
   for (temp_y=y1; temp_y<=y3; temp_y++,dest_addr+=pitch)
       {
       // do x clip
       left  = (int)xs;
       right = (int)xe;

       // adjust starting point and ending point
       xs+=dx_left;
       xe+=dx_right;

       // clip line
       if (left < min_clip_x)
          {
          left = min_clip_x;

          if (right < min_clip_x)
             continue;
          }

       if (right > max_clip_x)
          {
          right = max_clip_x;

          if (left > max_clip_x)
             continue;
          }

        // draw the line
        Mem_Set_QUAD(dest_addr+(unsigned int)left,color,(unsigned int)((int)right-(int)left+1));

       } // end for

   } // end else x clipping needed

}

void GDDrawRenderer::drawBottomTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int color)const
{
	
float dx_right,    // the dx/dy ratio of the right edge of line
      dx_left,     // the dx/dy ratio of the left edge of line
      xs,xe,       // the starting and ending points of the edges
      height;      // the height of the triangle

int temp_x,        // used during sorting as temps
    temp_y,
    right,         // used by clipping
    left;

// cast dest buffer to ushort
int *dest_buffer = buffer;

// destination address of next scanline
int  *dest_addr = NULL;

 

// test order of x1 and x2
if (x3 < x2)
   {
   temp_x = x2;
   x2     = x3;
   x3     = temp_x;
   } // end if swap

// compute delta's
height = y3-y1;

dx_left  = (x2-x1)/height;
dx_right = (x3-x1)/height;

// set starting points
xs = (float)x1;
xe = (float)x1; // +(float)0.5;

// perform y clipping
if (y1<min_clip_y)
   {
   // compute new xs and ys
   xs = xs+dx_left*(float)(-y1+min_clip_y);
   xe = xe+dx_right*(float)(-y1+min_clip_y);

   // reset y1
   y1=min_clip_y;

   } // end if top is off screen

if (y3>max_clip_y)
   y3=max_clip_y;

// compute starting address in video memory
dest_addr = dest_buffer+y1*pitch;

// test if x clipping is needed
if (x1>=min_clip_x && x1<=max_clip_x &&
    x2>=min_clip_x && x2<=max_clip_x &&
    x3>=min_clip_x && x3<=max_clip_x)
    {
    // draw the triangle
    for (temp_y=y1; temp_y<=y3; temp_y++,dest_addr+=pitch)
        {
        // draw the line
        Mem_Set_QUAD(dest_addr+(unsigned int)xs,color,(unsigned int)((int)xe-(int)xs+1));

        // adjust starting point and ending point
        xs+=dx_left;
        xe+=dx_right;

        } // end for

    } // end if no x clipping needed
else
   {
   // clip x axis with slower version

   // draw the triangle
   for (temp_y=y1; temp_y<=y3; temp_y++,dest_addr+=pitch)
       {
       // do x clip
       left  = (int)xs;
       right = (int)xe;

       // adjust starting point and ending point
       xs+=dx_left;
       xe+=dx_right;

       // clip line
       if (left < min_clip_x)
          {
          left = min_clip_x;

          if (right < min_clip_x)
             continue;
          }

       if (right > max_clip_x)
          {
          right = max_clip_x;

          if (left > max_clip_x)
             continue;
          }
       // draw the line
       Mem_Set_QUAD(dest_addr+(unsigned int)left,color,(unsigned int)((int)right-(int)left+1));

       } // end for

   } // end else x clipping needed

}

/*
void GDDrawRenderer::fillSurface(LPDIRECTDRAWSURFACE7 lpdds, int color, RECT *client){
	DDBLTFX ddbltfx; // this contains the DDBLTFX structure
	// clear out the structure and set the size field 
	DDRAW_INIT_STRUCT(ddbltfx);
	// set the dwfillcolor field to the desired color
	ddbltfx.dwFillColor = color; 
	// ready to blt to surface
	lpdds->Blt(client,     // ptr to dest rectangle
			   NULL,       // ptr to source surface, NA            
			   NULL,       // ptr to source rectangle, NA
			   DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
			   &ddbltfx);  // ptr to DDBLTFX structure
}*/

