#pragma once
#define DIRECTINPUT_VERSION 0x0800

typedef UCHAR  _DIKEYSTATE[256];
namespace skn_d3d {
	struct SknCursor
	{
		int x;
		int y;
		bool leftButton, rightButton;
	};
	class Input
	{
	public:
		Input();
		virtual ~Input();
		static SknCursor  cursor;


		static _DIKEYSTATE keyboard_state;
		static DIMOUSESTATE mouse_state;
		static LPDIRECTINPUT8        lpdi;
		static LPDIRECTINPUTDEVICE8  lpdikey;    // dinput keyboard
		static LPDIRECTINPUTDEVICE8  lpdimouse;    // dinput mouse
		static int init(HWND main_window_handle, HINSTANCE hinstance_app);

		static void release();

		static void getKeyState();
		static void getMouseState();
		static void getInputState();


		static bool isKeyPress(UCHAR key);
		static void pressKey(UCHAR key);


	};
}