// BitMapFile.cpp: implementation of the BitMapFile class.
//
//////////////////////////////////////////////////////////////////////

#include "BitMapFile.h"
#include <fstream>
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BitMapFile::BitMapFile()
{
	buffer=0;
}
BitMapFile::BitMapFile(char *filename)
{
	buffer=0;
	load( filename);
}
BitMapFile::~BitMapFile()
{
	unload();
}


int BitMapFile::load(const char *filename)
{
	ifstream bmpFile(filename,ios::binary);
	
	// now load the bitmap file header
	int index;
	bmpFile.read((char*)&bitmapfileheader,sizeof(BITMAPFILEHEADER));
	if (bitmapfileheader.bfType!=BITMAP_ID)
	{
		printf("n");
		return(0);
	} 
	bmpFile.read((char*)&bitmapinfoheader,sizeof(BITMAPINFOHEADER));
	if (bitmapinfoheader.biBitCount == 8)
	{
		bmpFile.read((char *)&palette,MAX_COLORS_PALETTE*sizeof(PALETTEENTRY));

		// now set all the flags in the palette correctly and fix the reversed 
		// BGR RGBQUAD data format
		for (index=0; index < MAX_COLORS_PALETTE; index++)
       {
       // reverse the red and green fields
       int temp_color                = palette[index].peRed;
       palette[index].peRed  = palette[index].peBlue;
       palette[index].peBlue = temp_color;
       
       // always set the flags word to this
       palette[index].peFlags = PC_NOCOLLAPSE;
       } // end for index
		printf("8");
	} 

	if (bitmapinfoheader.biBitCount==8 || bitmapinfoheader.biBitCount==16 || 
		bitmapinfoheader.biBitCount==24)
	{
	
		// delete the last image if there was one
		if (buffer)
		{
			delete[] buffer;
				
		}
			
		buffer=new UCHAR[bitmapinfoheader.biSizeImage];
			
		bmpFile.read((char *)buffer,bitmapinfoheader.biSizeImage);
			
		flip(buffer,bitmapinfoheader.biWidth*(bitmapinfoheader.biBitCount/8),bitmapinfoheader.biHeight);
	 
	} else
	{// serious problem
	 return(0);
   } 
	
	//printf("w");
	return 1;
}

int BitMapFile::load(string filename)
{
	return load(  filename.c_str());
}

int BitMapFile::unload()
{
	if(buffer)
	delete [] buffer;
	return(1);
}

int BitMapFile::flip(UCHAR *image, int bytes_per_line, int height)
{

	UCHAR *buffer; // used to perform the image processing
	int index;     // looping index

	// allocate the temporary buffer
	if (!(buffer = (UCHAR *)malloc(bytes_per_line*height)))
	   return(0);

	// copy image to work area
	memcpy(buffer,image,bytes_per_line*height);

	// flip vertically
	for (index=0; index < height; index++)
		memcpy(&image[((height-1) - index)*bytes_per_line],
			   &buffer[index*bytes_per_line], bytes_per_line);

	// release the memory
	free(buffer);

	// return success
	return(1);
}
BitMapFile* BitMapFile::getSubImage( int x1,int y1 ,int x2,int y2)
{
	UCHAR	* source_ptr;  // working pointers
	BitMapFile* newBitMap=new BitMapFile();
	int gwidth   = x2-x1+1;
	int gheight = y2-y1+1;
	int ucharWidth=gwidth*3;
	int ucharHeight=gheight*3;
	int ucharWidth_source=bitmapinfoheader.biWidth*3;
	newBitMap->bitmapinfoheader.biWidth=gwidth;
	newBitMap->bitmapinfoheader.biHeight=gheight;
	UCHAR	* dest_ptr=new UCHAR[ucharWidth*ucharHeight];
	newBitMap->buffer=dest_ptr;
	source_ptr = buffer +(bitmapinfoheader.biWidth*3)*y1+x1*3;
	for (int index_y=0; index_y < gheight; index_y++)
	{
		memcpy(dest_ptr,source_ptr,ucharWidth);
		dest_ptr+=ucharWidth;
		source_ptr+=ucharWidth_source;
	} // end for index_y
	return newBitMap;
}
BitMapFile* BitMapFile::getSubImageByIndex( int index_x,int index_y,int width,int height)
{
	int x1=index_x*width;
	int x2=x1+width-1;
	int y1=index_y*height;
	int y2=y1+height-1;

	return getSubImage(   x1, y1 ,  x2,  y2);


}
/*
int BitMapFile::getSubImage(LPDIRECTDRAWSURFACE7 lpdds, int cx, int cy)
{
	UCHAR * source_ptr;  // working pointers
    UINT* dest_ptr;
	DDSURFACEDESC2 ddsd;  
	DDRAW_INIT_STRUCT(ddsd);
	lpdds->Lock(NULL,
				&ddsd,
				DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
				NULL);
	int gwidth   = ddsd.dwWidth;
	int gheight = ddsd.dwHeight;
	dest_ptr = (UINT *)ddsd.lpSurface;
cx = cx*(gwidth*3);
cy = cy*(bitmapinfoheader.biWidth*3)*ddsd.dwHeight;

source_ptr = buffer + cy+cx;
	for (int index_y=0; index_y < ddsd.dwHeight; index_y++)
	{
		for(int index_x=0;index_x<ddsd.dwWidth;index_x++)
		{
			UCHAR blue  = (source_ptr[index_y*bitmapinfoheader.biWidth*3 + index_x*3 + 0])  ,
				 green = (source_ptr[index_y*bitmapinfoheader.biWidth*3 + index_x*3 + 1])  ,
				 red   = (source_ptr[index_y*bitmapinfoheader.biWidth*3 + index_x*3 + 2])  ;
			dest_ptr[index_y*(ddsd.lPitch >> 2)+index_x]= _RGB32BIT(0,red,green,blue);
		}
	} // end for index_y


lpdds->Unlock(NULL);


return(1);
}

int BitMapFile::getSubImage2(LPDIRECTDRAWSURFACE7 lpdds, int cx, int cy)
{
	int gwidth  = -1;
	int gheight = -1;
	UCHAR * source_ptr;  // working pointers
    USHORT* dest_ptr;

	DDSURFACEDESC2 ddsd;  
	DDRAW_INIT_STRUCT(ddsd);

	lpdds->Lock(NULL,
            &ddsd,
            DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
            NULL);
USHORT *primary_buffer = (USHORT *)ddsd.lpSurface;
for (int index_y = 0; index_y < 480; index_y++)
{
    for (int index_x = 0; index_x < 640; index_x++)
    {
        
        UCHAR blue  = (buffer[index_y*640*3 + index_x*3 + 0]) >> 3,
              green = (buffer[index_y*640*3 + index_x*3 + 1]) >> 3,
              red   = (buffer[index_y*640*3 + index_x*3 + 2]) >> 3;

        // this builds a 16 bit color value in 5.6.5 format (green dominant mode)
        USHORT pixel = _RGB16BIT565(red,green,blue);

        // write the pixel
        primary_buffer[index_x + (index_y*640 )] = pixel;

	} // end for index_x

} // end for index_y


// compute position to start scanning bits from
//cx = cx*(ddsd.dwWidt*3);
//cy = cy*(ddsd.dwHeight+1) + 1;
/*
gwidth  = ddsd.dwWidth;
gheight = ddsd.dwHeight;

// extract bitmap data
//source_ptr = buffer + cy*ddsd.dwHeight*bitmapinfoheader.biWidth*3+cx;

// assign a pointer to the memory surface for manipulation
dest_ptr = (USHORT *)ddsd.lpSurface;

// iterate thru each scanline and copy bitmap
	for (int index_y=0; index_y < ddsd.dwHeight; index_y++)
	{
		for(int index_x=0;index_x<ddsd.dwWidth;index_x++)
		{
			UCHAR blue  = (buffer[index_y*bitmapinfoheader.biWidth*3 + cx*3*ddsd.dwWidth+index_x*3 + 0]) >> 3,
				 green = (buffer[index_y*bitmapinfoheader.biWidth*3 + cx*3*ddsd.dwWidth+index_x*3 + 1]) >> 3,
				 red   = (buffer[index_y*bitmapinfoheader.biWidth*3 + cx*3*ddsd.dwWidth+index_x*3 + 2]) >> 3;
			dest_ptr[index_y*ddsd.dwWidth+index_x]= _RGB16BIT565(red,green,blue);
		}
	} // end for index_y


lpdds->Unlock(NULL);


return(1);
}
*/