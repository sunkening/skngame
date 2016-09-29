// GInput.h: interface for the GInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GINPUT_H__51F2D1C4_1BA2_4C2C_A23D_3424FE74191F__INCLUDED_)
#define AFX_GINPUT_H__51F2D1C4_1BA2_4C2C_A23D_3424FE74191F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>  
#include "GCursor.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
typedef UCHAR  _DIKEYSTATE[256];
class GInput  
{
public:
	GInput();
	virtual ~GInput();
	static GCursor* cursor;
 
 
	static _DIKEYSTATE keyboard_state;	
	static DIMOUSESTATE mouse_state;
	static LPDIRECTINPUT8        lpdi      ; 
	static LPDIRECTINPUTDEVICE8  lpdikey   ;    // dinput keyboard
	static LPDIRECTINPUTDEVICE8  lpdimouse ;    // dinput mouse
	static int init(HWND main_window_handle,HINSTANCE hinstance_app);
	 
	static void release();

	static void getKeyState();
	static void getMouseState();
	static void getInputState();
 

	static bool isKeyPress(UCHAR key);
	static void pressKey(UCHAR key);
/*
	static int pressLeftKey();
	static int pressRightKey();
	static int pressUpKey();
	static int pressDownKey();*/
	
};

#endif // !defined(AFX_GINPUT_H__51F2D1C4_1BA2_4C2C_A23D_3424FE74191F__INCLUDED_)
