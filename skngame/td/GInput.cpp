// GInput.cpp: implementation of the GInput class.
//
//////////////////////////////////////////////////////////////////////

#include "GInput.h"
#include "gl.h"
#include "LOG.h"
#include <IOSTREAM>
#include <MEMORY.h>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LPDIRECTINPUT8        GInput::lpdi      = NULL; 
LPDIRECTINPUTDEVICE8  GInput::lpdikey   = NULL;    // dinput keyboard
LPDIRECTINPUTDEVICE8  GInput::lpdimouse = NULL;    // dinput mouse
_DIKEYSTATE GInput::keyboard_state={0};
DIMOUSESTATE GInput::mouse_state={0};
GCursor* GInput::cursor=null;
 
 
GInput::GInput()
{

}

GInput::~GInput()
{

}

int GInput::init(HWND main_window_handle,HINSTANCE hinstance_app)
{
	// first create the direct input object
	if (DirectInput8Create(hinstance_app,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
		 return(0);
	
	// create a keyboard device  //////////////////////////////////
	if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK)
		return(0);
	// set cooperation level
	if (lpdikey->SetCooperativeLevel(main_window_handle, 
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
		return(0);
	// set data format
	if (lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
		return(0);
	// acquire the keyboard
	if (lpdikey->Acquire()!=DI_OK)
		return(0);


	if (lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL)!=DI_OK)
		return(0);
	
	if (lpdimouse->SetCooperativeLevel(main_window_handle, 
		 DISCL_NONEXCLUSIVE|DISCL_BACKGROUND )!=DI_OK)
		return(0);
	
	// set data format
	if (lpdimouse->SetDataFormat(&c_dfDIMouse)!=DI_OK)
		return(0);
	
	// acquire the keyboard
	if (lpdimouse->Acquire()!=DI_OK)
		return(0);
	cursor=new GCursor;	 
	try{
		BitMapFile bitmap;
		bitmap.load("res/img/cursor.bmp");
		cursor->init(&bitmap,32,RGB(0,0,0));
		cursor->speed=100;
		//ShowCursor(false);
	}catch(...)
	{
		LOG::e("加载鼠标出错");
	}

	return 1;
}

void GInput::getKeyState()
{
		lpdikey->GetDeviceState(256, (LPVOID)keyboard_state);
}

bool GInput::isKeyPress(UCHAR key)
{
	if (keyboard_state[key])return true;
	return false;
}
/*

int GInput::getLeftKey()
{
	if (keyboard_state[DIK_LEFT])return 1;
	return 0;
}

int GInput::getRightKey()
{
	if (keyboard_state[DIK_RIGHT])return 1;
	return 0;
}

int GInput::getUpKey()
{
	if (keyboard_state[DIK_UP])return 1;
	return 0;
}

int GInput::getDownKey()
{
	if (keyboard_state[DIK_DOWN])return 1;
	return 0;
}
*/

void GInput::release()
{
	//释放键盘设备
	if(lpdikey)
	{
		lpdikey->Unacquire();
		lpdikey->Release();
	}
	//释放鼠标设备
	if(lpdimouse)
	{
		lpdimouse->Unacquire();
		lpdimouse->Release();
	}
	//释放输入接口
	if(lpdi)
		lpdi->Release();
}

void GInput::getMouseState()
{
	if(lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state)
		==DIERR_INPUTLOST)
	{
		if(FAILED(lpdimouse->Acquire()))
			LOG::e("获取鼠标失败");
	}
	cursor->x+=mouse_state.lX;
	cursor->y+=mouse_state.lY;
	if (cursor->x<0)cursor->x=0;
	if (cursor->y<0)cursor->y=0;
	if (cursor->y>=SCREEN_HEIGHT)cursor->y=SCREEN_HEIGHT-1;
	if (cursor->x>=SCREEN_WIDTH)cursor->x=SCREEN_WIDTH-1;
 
	cursor->leftButton=mouse_state.rgbButtons[0];
	cursor->rightButton=mouse_state.rgbButtons[1];
}

void GInput::getInputState()
{
	getKeyState();
	getMouseState();
}

void GInput::pressKey(UCHAR key)
{
	keyboard_state[key]=1;
}

 




