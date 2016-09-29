#include <windows.h>  
#include <tchar.h>
#include "GameApp.h"
#include "LOG.h"
#include "GWindow.h"


GWindow::GWindow(void)
{
	windowed=1;
	windowHeight=600;
	windowWidth=800;
	tital=_T("skn Game");
	windowAttr=WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	app=0;;
}


GWindow::~GWindow(void)
{
}

int WINAPI GWindow::WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

WNDCLASSEX winclass; // this will hold the class we create
HWND	   hwnd;	 // generic window handle

HDC        hdc;      // graphics device context

// first fill in the window class stucture
winclass.cbSize         = sizeof(WNDCLASSEX);
winclass.style			= CS_DBLCLKS | CS_OWNDC | 
                          CS_HREDRAW | CS_VREDRAW;
winclass.lpfnWndProc	= DefWindowProc;
winclass.cbClsExtra		= 0;
winclass.cbWndExtra		= 0;
winclass.hInstance		= hinstance;
winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
winclass.lpszMenuName	= NULL;
winclass.lpszClassName	= _T("WINCLASS1");
winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

// save hinstance in global
hinstance_app = hinstance;

// register the window class
if (!RegisterClassEx(&winclass))
	return(0);

// create the window
if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                            _T("WINCLASS1"),     // class
						    tital, // title
						    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    windowWidth,windowHeight,  // initial width, height
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hinstance,// instance of this application
						    NULL)))	// extra creation parms
					
/*
if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                            WINDOW_CLASS_NAME,     // class
						    "DirectDraw 16-Bit Full-Screen Demo", // title
						    WS_POPUP | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    SCREEN_WIDTH,SCREEN_HEIGHT,  // initial width, height
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hinstance,// instance of this application
						    NULL)))	// extra creation parms*/
							
return(0);

main_window_handle = hwnd;
 
GameApp::setInstance(app);
GameApp::getInstance()->init(hinstance_app,windowed,hwnd,1,0,0,0);
//enter main event loop


// closedown game here
//Game_Shutdown();

// return to Windows like this
return 1;

} // end WinMain

int GWindow::create(HINSTANCE hinstance,int windowed,int width,int height,GameApp* app)
{
	windowHeight=height;
	windowWidth=width;
	this->windowed=windowed;
	this->app=app;
	if (!windowed)
	{
		windowAttr= WS_POPUP | WS_VISIBLE;
	}
	if (!app)
	{
		LOG::e("gameapp 为空");
		return 0;
	}
	return WinMain( hinstance, 0,0, SW_SHOWNORMAL);
}

void GWindow::run()
{
	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		//游戏主循环
		GameApp::mainLoop();
	} // end while
}


/*

LRESULT CALLBACK WindowProc(HWND hwnd, 
	UINT msg, 
	WPARAM wparam, 
	LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context
	char buffer[80];        // used to print strings

	// what is the message 
	switch(msg)
	{	
	case WM_CREATE: 
		{
			// do initialization stuff here
			// return success
			return(0);
		} break;

	case WM_PAINT: 
		{
			// simply validate the window 
			hdc = BeginPaint(hwnd,&ps);	 

			// end painting
			EndPaint(hwnd,&ps);

			// return success
			return(0);
		} break;

	case WM_DESTROY: 
		{

			// kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);

			// return success
			return(0);
		} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc*/