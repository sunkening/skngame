//存放宏,全局变量

#ifndef GL_H
#define GL_H
 
#include <windows.h>
#include <IOSTREAM>
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;
#define null 0
// default screen size
#define SCREEN_WIDTH    800 // size of screen
#define SCREEN_HEIGHT   600
#define SCREEN_BPP      32  // bits per pixel
#define DIRECT_DRAW 1
#define GUI	2

#define RENDERTYPE_WORLD 2
#define RENDERTYPE_SCREEN 1
#define RENDERTYPE_VIEWPORT 3
#define TIME_PER_FRAM 15 //每帧的时间间隔
// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// this builds a 16 bit color value in 5.5.5 format (1-bit alpha mode)
#define _RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))
//24位bitmap 的三原色顺序是BGR，draw使用的顺序是ARGB，RGB()宏参数的顺序是BGR
// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))
#define _RGB32BIT(a,r,g,b) ((b ) + ((g) << 8) + ((r ) << 16)+((a)<<24))
#define RAND_RANGE(x,y) ( (x) + (rand()%((y)-(x)+1)))
// initializes a direct draw struct
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
//  FILE *fp_error;                           // general error file
// int Write_Error(char *string, ...);
#include <stdio.h>
#include <string>

class GameApp;
class GLayer;
class GLogger;
class GScene;
class GRenderer;
using namespace std;

string& operator+( string& s,double x);
string& operator+( string& s,float x);
string& operator+( string& s,int x);

#define OBJECT_MAX_VERTICES 10000
#define OBJECT_MAX_POLYS 5000
#define RENDERLIST_MAX_POLYS 100000
#endif

