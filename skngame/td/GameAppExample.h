 
#ifndef GAMEAPPEXAMPLE_H
#define GAMEAPPEXAMPLE_H

#include "GameApp.h"

#include "GSpiritLayer.h"
#include "GameSceneExample.h"
#include "GColorLayer.h"
class GameAppExample : public GameApp  
{
public:
	GameAppExample();
	virtual ~GameAppExample();
//	int  init(bool windowed,HWND main_window_handle,int mode,int width, int height, int bpp);
	int load();

};

#endif  