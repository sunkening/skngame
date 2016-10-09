#include <windows.h>
#include <math.h>

#define NUM 100

#define TWOPI      (2 * 3.14159)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

	PSTR szCmdLine, int iCmdShow)

{

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

		WS_OVERLAPPEDWINDOW,  // window style

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
	static int num=0;
	int         i;
	POINT       apt[NUM];
	HDC                   hdc;
	PAINTSTRUCT ps;
	RECT          rect;
	switch (message)
	{
	case   WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_CREATE:
		PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		SetTimer(hwnd,1,15,0);
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
		
		Polyline(hdc, apt, num);

		ReleaseDC(hwnd,hdc);
		return 0;
	case   WM_PAINT:
		ValidateRect(hwnd, NULL);
		 
		/*hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, Windows 98!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
		EndPaint(hwnd, &ps);*/
		return 0;
	case   WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}
