#include "stdafx.h"

#include <dinput.h>
  

 
#include<d3d9.h>
#include<d3dx9.h>
 
using namespace std;
#include "Input.h"
#include "D3DUtil.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace skn_d3d {
	LPDIRECTINPUT8        Input::lpdi = NULL;
	LPDIRECTINPUTDEVICE8  Input::lpdikey = NULL;    // dinput keyboard
	LPDIRECTINPUTDEVICE8  Input::lpdimouse = NULL;    // dinput mouse
	_DIKEYSTATE Input::keyboard_state = { 0 };
	DIMOUSESTATE Input::mouse_state = { 0 };
	SknCursor Input::cursor = {};


	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	int Input::init(HWND main_window_handle, HINSTANCE hinstance_app)
	{
		// first create the direct input object
		if (DirectInput8Create(hinstance_app, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&lpdi, NULL) != DI_OK)
			return(0);

		// create a keyboard device  //////////////////////////////////
		if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL) != DI_OK)
			return(0);
		// set cooperation level
		if (lpdikey->SetCooperativeLevel(main_window_handle,
			DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
			return(0);
		// set data format
		if (lpdikey->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
			return(0);
		// acquire the keyboard
		if (lpdikey->Acquire() != DI_OK)
			return(0);


		if (lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL) != DI_OK)
			return(0);

		if (lpdimouse->SetCooperativeLevel(main_window_handle,
			DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
			return(0);

		// set data format
		if (lpdimouse->SetDataFormat(&c_dfDIMouse) != DI_OK)
			return(0);

		// acquire the keyboard
		if (lpdimouse->Acquire() != DI_OK)
			return(0);
		return 1;
	}

	void Input::getKeyState()
	{
		lpdikey->GetDeviceState(256, (LPVOID)keyboard_state);
	}

	bool Input::isKeyPress(UCHAR key)
	{
		if (keyboard_state[key])return true;
		return false;
	}

	void Input::release()
	{
		//释放键盘设备
		if (lpdikey)
		{
			lpdikey->Unacquire();
			lpdikey->Release();
		}
		//释放鼠标设备
		if (lpdimouse)
		{
			lpdimouse->Unacquire();
			lpdimouse->Release();
		}
		//释放输入接口
		if (lpdi)
			lpdi->Release();
	}

	void Input::getMouseState()
	{
		if (lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state)
			== DIERR_INPUTLOST)
		{
			if (FAILED(lpdimouse->Acquire()))
				::MessageBox(0, _T("获取鼠标状态 - FAILED"), 0, 0);
		}
		cursor.x += mouse_state.lX;
		cursor.y += mouse_state.lY;
		if (cursor.x < 0)cursor.x = 0;
		if (cursor.y < 0)cursor.y = 0;
		if (cursor.y >= D3DUtil::screenWidth)cursor.y = D3DUtil::screenWidth - 1;
		if (cursor.x >= D3DUtil::screenHeight)cursor.x = D3DUtil::screenHeight - 1;

		cursor.leftButton = mouse_state.rgbButtons[0];
		cursor.rightButton = mouse_state.rgbButtons[1];
	}

	void Input::getInputState()
	{
		getKeyState();
		getMouseState();
	}

	void Input::pressKey(UCHAR key)
	{
		keyboard_state[key] = 1;
	}


}