// BitMapFile.h: ∂¡»°ŒªÕº
//
//////////////////////////////////////////////////////////////////////

#ifndef BITMAPFILE_H
#define BITMAPFILE_H
#include <windows.h>

#include <io.h>
#include <STRING>
using namespace std;

#define BITMAP_ID            0x4D42 // universal id for a bitmap
#define MAX_COLORS_PALETTE   256
class BitMapFile  
{
public:
	BitMapFile();
	BitMapFile(char *filename);
	virtual ~BitMapFile();
public:
//	int getSubImage(LPDIRECTDRAWSURFACE7 lpdds, int cx, int cy);
//	int getSubImage2(LPDIRECTDRAWSURFACE7 lpdds, int cx, int cy);
 
BitMapFile*  getSubImage( int x1,int y1 ,int x2,int y2);
BitMapFile*  getSubImageByIndex( int index_x,int index_y,int width,int height);
	int flip(UCHAR* img,int width,int height);
	int load(const char* filename);
	int load(string filename);
	int unload();
	BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
    BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
    PALETTEENTRY     palette[256];      // we will store the palette here
    UCHAR            *buffer;           // this is a pointer to the data
	
};

#endif // !defined(AFX_BITMAPFILE_H__D59CBF64_E309_4B9D_86F2_0B6A67DBE7C6__INCLUDED_)
