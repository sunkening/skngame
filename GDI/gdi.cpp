#include <windows.h>
#include "sknwindow.h"
using namespace skn_window;
#define NUM 100

#define TWOPI      (2 * 3.14159)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LogWindow::Init(hInstance);
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND   hwnd;
	MSG    msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))

	{

		MessageBox(NULL, TEXT("This program requires Windows NT!"),

			szAppName, MB_ICONERROR);

		return 0;

	}

	hwnd = CreateWindow(szAppName,      // window class name

		TEXT("The Hello Program"),   // window caption

		WS_OVERLAPPEDWINDOW| WS_VSCROLL,  // window style

		CW_USEDEFAULT,// initial x position

		CW_USEDEFAULT,// initial y position

		CW_USEDEFAULT,// initial x size

		CW_USEDEFAULT,// initial y size

		NULL,                 // parent window handle

		NULL,            // window menu handle

		hInstance,   // program instance handle

		NULL);      // creation parameters



	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);



	while (GetMessage(&msg, NULL, 0, 0))

	{

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxClient, cyClient;
	static int cxChar, cyChar;
	static int num=0, iVertPos =0;
	static LogWindow * logwindow = 0;
	int         i;
	SCROLLINFO  si;
	static int logIndex=65;
	POINT       apt[NUM];
	HDC                   hdc;
	PAINTSTRUCT ps;
	RECT          rect;
	switch (message)
	{
	case   WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 99;
		si.nPage = cyClient / cyChar;
		si.nPos = iVertPos;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		return 0;
	case WM_CREATE:
		PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//SetTimer(hwnd,1,15,0);
		/*int cxChar = LOWORD(GetDialogBaseUnits());
		int cyChar = HIWORD(GetDialogBaseUnits());*/
		CreateWindow(TEXT("button"), TEXT("PUSHBUTTON"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 200, 100, 100, hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		
		logwindow =LogWindow::Create(hwnd,0);
		MoveWindow(logwindow->hwnd, 0, 0, 500, 100, false);

		hdc = GetDC(hwnd);
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hwnd, hdc);
		 
		return 0;
	case WM_COMMAND: {
		TSTRING s = TEXT("µ«ÊÇ");
		s.append(1,(TCHAR)logIndex);
		logwindow->Log(s);
		logIndex++;
		SCROLLINFO  si;
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(logwindow->hwnd, SB_VERT, &si);
		//MessageBoxPrintf(TEXT(""),TEXT("%d"),si.nPos);
		return 0;
	}
			
	case WM_VSCROLL:
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_VERT, &si);
		// Save the position for comparison later on

		iVertPos = si.nPos;

		switch (LOWORD(wParam)) {
		case   SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;
		case   SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		}
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &si);
		// If the position has changed, scroll the window and update it
		if (si.nPos != iVertPos)
		{
			ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos),
				NULL, NULL);
			UpdateWindow(hwnd);
		}
		return 0;
	case WM_TIMER:
		//InvalidateRect(hwnd, NULL, TRUE);
		hdc = GetDC(hwnd);
		//MoveToEx(hdc, 0, cyClient / 2, NULL);
		//LineTo(hdc, cxClient, cyClient / 2);
		num++;
		if (num > NUM)
		{
			num = 1;
		}
		for (i = 0; i < num; i++)
		{
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
		}
		
	//	Polyline(hdc, apt, num);

		ReleaseDC(hwnd,hdc);
		return 0;
	case   WM_PAINT:
		//ValidateRect(hwnd, NULL);
		 
		 hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, Windows 98!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		  
		EndPaint(hwnd, &ps); 
		return 0;
	case   WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}
