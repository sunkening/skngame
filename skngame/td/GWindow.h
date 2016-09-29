#pragma once


class GWindow
{
public:
	GWindow(void);
	~GWindow(void);
	HWND      main_window_handle ; // globally track main window
	HINSTANCE hinstance_app; // globally track hinstance
	int windowed;
	int windowHeight;
	int windowWidth;
	LPTSTR tital;
	int windowAttr;
	GameApp* app;
	MSG		   msg;		 // generic message
	int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow);
	int create(HINSTANCE hinstance,int windowed,int width,int height,GameApp* app);
	void run();
};

