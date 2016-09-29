// GDDraw.cpp: implementation of the GDDraw class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw
#include "Exception.h"
#include "GDDraw.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 LPDIRECTDRAW7 GDDraw::directDraw7=null ;   // dd object
LPDIRECTDRAWSURFACE7  GDDraw::primarySurface=null   ;   // dd primary surface
LPDIRECTDRAWSURFACE7  GDDraw::backSurface=null      ;   // dd back surface
int	GDDraw::clientHeight=0  ;//客户显示区高,像素
int	GDDraw::clientWidth=0    ;//客户显示区宽,像素
int	GDDraw::clientBpp =0     ;//像素格式
int GDDraw::lowColorKey=0;//关键色/透明色
int GDDraw::highColorKey=0;//关键色/透明色
 bool GDDraw::isWindow=0;
 RECT GDDraw::clientRect={0,0,0,0}; 

GDDraw::GDDraw()
{

}

GDDraw::~GDDraw()
{

}

// this function initializes directdraw
int GDDraw::init(bool windowed,HWND main_window_handle,int width, int height, int bpp )
{
	isWindow=windowed;

	// create IDirectDraw interface 7.0 object and test for error
	if (FAILED(DirectDrawCreateEx(NULL, (void **)&directDraw7, IID_IDirectDraw7, NULL)))
	   return(0);
	
	// based on windowed or fullscreen set coorperation level
	if (windowed)
	   {
	   // set cooperation level to windowed mode 
	   if (FAILED(directDraw7->SetCooperativeLevel(main_window_handle,DDSCL_NORMAL)))
		   return(0);
	   } // end if
	else
	   {
	   // set cooperation level to fullscreen mode 
	   if (FAILED(directDraw7->SetCooperativeLevel(main_window_handle,
				  DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | 
				  DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_MULTITHREADED )))
		   return(0);
	   // set the display mode
	   if (FAILED(directDraw7->SetDisplayMode(width,height,bpp,0,0)))
		  return(0);
	   } // end else
	
	//创建主表面
	DDSURFACEDESC2        ddsd; 	
	DDRAW_INIT_STRUCT(ddsd); 

	// we need to let dd know that we want a complex 
	// flippable surface structure, set flags for that
	if (!windowed)
	   {
		clientHeight   = height;
		clientWidth    = width;
		clientBpp      = bpp;
	   // fullscreen mode
	   ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	   ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	   // set the backbuffer count to 0 for windowed mode
	   // 1 for fullscreen mode, 2 for triple buffering
	   ddsd.dwBackBufferCount = 1;
	   } // end if
	else
	   {
	   // windowed mode
	   ddsd.dwFlags = DDSD_CAPS;
	   ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	   // set the backbuffer count to 0 for windowed mode
	   // 1 for fullscreen mode, 2 for triple buffering
	   ddsd.dwBackBufferCount = 0;
	   } // end else

	// create the primary surface
	directDraw7->CreateSurface(&ddsd,&primarySurface,NULL);
	if(windowed)
	{
		// get the pixel format of the primary surface
		DDPIXELFORMAT ddpf; // used to get pixel format
		DDRAW_INIT_STRUCT(ddpf);// initialize structure
		// query the format from primary surface
		primarySurface->GetPixelFormat(&ddpf);
		clientBpp = ddpf.dwRGBBitCount;
		initBack(main_window_handle);
	}else{
		// query for the backbuffer i.e the secondary surface
		ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
		// get the attached back buffer surface
		if (FAILED(primarySurface->GetAttachedSurface(&ddsd.ddsCaps, &backSurface)))
		  return(0);
	}
	// clear out both primary and secondary surfaces
	if (windowed)
	{
	   // 只填充缓冲表面,主表面就是整个屏幕
	   fillSurface(backSurface,0);
	} 
	else
	{
	   // fullscreen, simply clear everything
	   fillSurface(primarySurface,0);
	   fillSurface(backSurface,0);
	} // end else
/*
	// set software algorithmic clipping region
	min_clip_x = 0;
	max_clip_x = screenWidth - 1;
	min_clip_y = 0;
	max_clip_y = screenHeight - 1;

	// setup backbuffer clipper always
	RECT screen_rect = {0,0,screenWidth,screenHeight};
	lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);
*/
	// set up windowed mode clipper
	LPDIRECTDRAWCLIPPER  clipperWin;
	if (windowed)
	{
	   // set windowed clipper
	   if (FAILED(directDraw7->CreateClipper(0,&clipperWin,NULL)))
		   return(0);
	   if (FAILED(clipperWin->SetHWnd(0, main_window_handle)))
		   return(0);
	   if (FAILED(primarySurface->SetClipper(clipperWin)))
		   return(0);
	 } // end if screen windowed
	
	// return success
	return(1);

}
void GDDraw::initBack(HWND main_window_handle)
{
	GetWindowRect(main_window_handle, &clientRect);
	int width=clientRect.right-clientRect.left;
	int height=clientRect.bottom-clientRect.top;
	backSurface = createSurface(  width,   height,0,lowColorKey,highColorKey);
	RECT viewRect;
	viewRect.left=0;
	viewRect.right=width;
	viewRect.top=0;
	viewRect.bottom=height;	
	//给此表面创建裁剪器
	attachClipper(backSurface,1,&viewRect);
	clientHeight   = height;
	clientWidth    = width;
}
void GDDraw::resetClientRect(HWND main_window_handle)
{
	GetWindowRect(main_window_handle, &clientRect);
}
int GDDraw::fillSurface(LPDIRECTDRAWSURFACE7 surface,int color, RECT *client){
	DDBLTFX ddbltfx; // this contains the DDBLTFX structure
	DDRAW_INIT_STRUCT(ddbltfx);
	ddbltfx.dwFillColor = color; 
	surface->Blt(client,     // ptr to dest rectangle
			   NULL,       // ptr to source surface, NA            
			   NULL,       // ptr to source rectangle, NA
			   DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
			   &ddbltfx);  // ptr to DDBLTFX structure
	return(1);
}
int GDDraw::fillBack(int color, RECT *client )
{
	fillSurface(backSurface,  color,  client);
	return(1);

}

LPDIRECTDRAWSURFACE7 GDDraw::createSurface(int width, int height, int mem_flags, int lowColor ,int highColor)
{
	DDSURFACEDESC2 ddsd;
	LPDIRECTDRAWSURFACE7 lpdds;
	DDRAW_INIT_STRUCT(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
	ddsd.dwWidth=width;
	ddsd.dwHeight=height;
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|mem_flags;
	if(FAILED(directDraw7->CreateSurface(&ddsd,&lpdds,NULL)))
		return NULL;
	//设置透明色
	DDCOLORKEY color_key; // used to set color key
	if (lowColor==-1)
	{
		color_key.dwColorSpaceLowValue  = 0;
		color_key.dwColorSpaceHighValue = 0;
	}else
	{
		color_key.dwColorSpaceLowValue  = lowColor;
		color_key.dwColorSpaceHighValue = highColor;
	}


	//DDCKEY_COLORSPACE DDCKEY_SRCBLT now set the color key for source blitting
	//这个函数出错了,返回值是DDERR_NOCOLORKEYHW
	//色彩范围也是需要硬件支持的,并且HEL没有实现
	if(FAILED(lpdds->SetColorKey(DDCKEY_SRCBLT|DDCKEY_COLORSPACE, &color_key))){
		color_key.dwColorSpaceHighValue = lowColor;
		lpdds->SetColorKey(DDCKEY_SRCBLT , &color_key);
	}
	return lpdds;
}
LPDIRECTDRAWSURFACE7 GDDraw::createSurface(UCHAR * bitmapBuffer,int width,int height,int lowColor ,int highColor )
{
	//获取一个和位图一样大的表面
	LPDIRECTDRAWSURFACE7 lpdds=createSurface( width,  height, 0,lowColor,highColor);
	UCHAR * source_ptr=bitmapBuffer;  // working pointers
    UINT* dest_ptr;
	DDSURFACEDESC2 ddsd;  
	DDRAW_INIT_STRUCT(ddsd);
	lpdds->Lock(NULL,
				&ddsd,
				DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
				NULL);
	dest_ptr = (UINT *)ddsd.lpSurface;
	for (int index_y=0; index_y < height; index_y++)
	{
		for(int index_x=0;index_x<width;index_x++)
		{
			UCHAR blue  = (source_ptr[index_y*width*3 + index_x*3 + 0]) ,
			green = (source_ptr[index_y*width*3 + index_x*3 + 1])  ,
			red   = (source_ptr[index_y*width*3 + index_x*3 + 2])  ;
			UINT pixel = _RGB32BIT(0,red,green,blue);
			dest_ptr[index_x + (index_y*(ddsd.lPitch >> 2))] = pixel;

		}
	} // end for index_y
	lpdds->Unlock(NULL);
	return lpdds;
}
LPDIRECTDRAWSURFACE7 GDDraw::createSurface(const BitMapFile * bitmap,int lowColor ,int highColor)
{
	int width=	bitmap->bitmapinfoheader.biWidth ;
	int height=	bitmap->bitmapinfoheader.biHeight ;
	
	return createSurface(bitmap->buffer, width, height,  lowColor, highColor);
}
LPDIRECTDRAWCLIPPER GDDraw::attachClipper(LPDIRECTDRAWSURFACE7 lpdds, int num_rects, LPRECT clip_list)
{
	// this function creates a clipper from the sent clip list and attaches
	// it to the sent surface
	int index;                         // looping var
	LPDIRECTDRAWCLIPPER lpddclipper;   // pointer to the newly created dd clipper
	LPRGNDATA region_data;             // pointer to the region data that contains
									   // the header and clip list
	// first create the direct draw clipper
	if (FAILED(directDraw7->CreateClipper(0,&lpddclipper,NULL)))
	   return(NULL);

	// now create the clip list from the sent data

	// first allocate memory for region data
	region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+num_rects*sizeof(RECT));

	// now copy the rects into region data
	memcpy(region_data->Buffer, clip_list, sizeof(RECT)*num_rects);

	// set up fields of header
	region_data->rdh.dwSize          = sizeof(RGNDATAHEADER);
	region_data->rdh.iType           = RDH_RECTANGLES;
	region_data->rdh.nCount          = num_rects;
	region_data->rdh.nRgnSize        = num_rects*sizeof(RECT);

	region_data->rdh.rcBound.left    =  64000;
	region_data->rdh.rcBound.top     =  64000;
	region_data->rdh.rcBound.right   = -64000;
	region_data->rdh.rcBound.bottom  = -64000;

	// find bounds of all clipping regions
	for (index=0; index<num_rects; index++)
		{
		// test if the next rectangle unioned with the current bound is larger
		if (clip_list[index].left < region_data->rdh.rcBound.left)
		   region_data->rdh.rcBound.left = clip_list[index].left;

		if (clip_list[index].right > region_data->rdh.rcBound.right)
		   region_data->rdh.rcBound.right = clip_list[index].right;

		if (clip_list[index].top < region_data->rdh.rcBound.top)
		   region_data->rdh.rcBound.top = clip_list[index].top;

		if (clip_list[index].bottom > region_data->rdh.rcBound.bottom)
		   region_data->rdh.rcBound.bottom = clip_list[index].bottom;

		} // end for index

	// now we have computed the bounding rectangle region and set up the data
	// now let's set the clipping list

	if (FAILED(lpddclipper->SetClipList(region_data, 0)))
	   {
	   // release memory and return error
	   free(region_data);
	   return(NULL);
	   } // end if

	// now attach the clipper to the surface
	if (FAILED(lpdds->SetClipper(lpddclipper)))
	   {
	   // release memory and return error
	   free(region_data);
	   return(NULL);
	   } // end if

	// all is well, so release memory and send back the pointer to the new clipper
	free(region_data);
	return(lpddclipper);

} // end DDraw_Attach_Clipper 
void GDDraw::release()
{
	// now the primary surface
	if (primarySurface)
	{
	   primarySurface->Release();
	   primarySurface = NULL;
	 } // end if

	// now blow away the IDirectDraw4 interface
	if (directDraw7)
	{
	   directDraw7->Release();
	   directDraw7 = NULL;
	} // end if
}
int GDDraw::drawToBack(LPDIRECTDRAWSURFACE7 source, int x, int y, int width, int height,  int transparent)
{
	return drawToSurface(source,backSurface,x,y,width,height,transparent);

}
int GDDraw:: drawToSurface(LPDIRECTDRAWSURFACE7 source,LPDIRECTDRAWSURFACE7 target, int x, int y, int width, int height,  int transparent)
{
	RECT dest_rect; // the destination rectangle
		//RECT source_rect; // the source rectangle                             
	// fill in the destination rect
	dest_rect.left   = x;
	dest_rect.top    = y;
	dest_rect.right  = x+width;
	dest_rect.bottom = y+height;
	// test transparency flag
//	transparent=0;
	if (transparent)
	   {
	   // enable color key blit
	   // blt to destination surface
	   
	   if (FAILED( target->Blt(&dest_rect, source,
						 NULL,(DDBLT_WAIT | DDBLT_KEYSRC),
						 NULL)))
			   return(0);

	   } // end if
	else
	   {
	   // perform blit without color key
	   // blt to destination surface
	   if (FAILED( target->Blt(&dest_rect, source,
						 NULL,(DDBLT_WAIT),
						 NULL)))
			   return(0);
	   } // end if
	// return success
	return(1);
}

int GDDraw::flip()
{
	if(isWindow){
		if (FAILED(primarySurface->Blt(&clientRect, backSurface,
			NULL, (DDBLT_WAIT),
			NULL)))
		{
			throw
				new Exception("failed GDDraw::flip()");
			return(0);
	   }
	  
	}else{
		primarySurface->Flip(NULL, DDFLIP_WAIT);
	}
	return(1);
}
void GDDraw::initWindowRect(HWND main_window_handle)
{
	GetWindowRect(main_window_handle, &clientRect);
}