
#include <windows.h>
#include <string>
#include<list>
#include <tchar.h>   
#include <stdio.h> 
#include "LogWindow.h"
int CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...)
{
	TCHAR   szBuffer[1024];
	va_list pArgList;
	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;
	va_start(pArgList, szFormat);
	// The last argument to wvsprintf points to the arguments
	_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),
		szFormat, pArgList);
	// The va_end macro just zeroes out pArgList for no good reason
	va_end(pArgList);
	return MessageBox(NULL, szBuffer, szCaption, 0);
}
TCHAR * LogWindow::windowName = 0;
WNDCLASS LogWindow::wndclass = {0};
LRESULT CALLBACK LogWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC                                          hdc;
	PAINTSTRUCT                          ps;
	RECT                                         rect;
	LogItemList::iterator iter;
	LogWindow *logwindow= (LogWindow *)GetWindowLong(hwnd, 0);
	int i = 0;
	switch (message)
	{
	case   WM_CREATE:
		logwindow =(LogWindow *) ((CREATESTRUCT *)lParam)->lpCreateParams;
		SetWindowLong(hwnd, 0, (LONG)logwindow);       // on/off flag
		return 0;
	case   WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("点击了左建"), windowName, MB_ICONERROR);
		/*SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
		InvalidateRect(hwnd, NULL, FALSE);*/
		return 0;
	case   WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);
		
		for ( i=0,iter= logwindow->itemList.begin();iter!= logwindow->itemList.end();iter++,i++)
		{
			TextOut(hdc, 5, 5, TEXT("22222"), 5);
			//iter->info;
			TextOut(hdc,0,i*20, (PTCHAR)(iter->info.c_str()), iter->info.length());
			TextOut(hdc, 20, i * 20, TEXT("22222"), 5);
		}
		 
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

bool LogWindow::Init(HINSTANCE hinstance)
{
	windowName = TEXT("LogWindow");
	 wndclass.style = CS_HREDRAW | CS_VREDRAW;
	 wndclass.lpfnWndProc = WndProc;
	 wndclass.cbClsExtra = 0;
	 wndclass.cbWndExtra = sizeof(LogWindow*);
	 wndclass.hInstance = hinstance;
	 wndclass.hIcon = 0;
	 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	 wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	 wndclass.lpszMenuName = NULL;
	 wndclass.lpszClassName = windowName;
	 if (!RegisterClass(&wndclass))
	 {
		 MessageBox(NULL, TEXT("创建注册LogWindow窗口类别失败"), windowName, MB_ICONERROR);
		 return 0;
	 }
	 return 1;
}

LogWindow::LogWindow()
{
	
}

LogWindow::~LogWindow()
{
	
}

void LogWindow::Log(TSTRING s)
{
		LogItem logitem;
		logitem.info = s;
		itemList.push_back(logitem);
}

void LogWindow::Log(PTCHAR psw)
{
	TSTRING s = psw;
	LogItem logitem;
	logitem.info = s;
	itemList.push_back(logitem);
}

LogWindow* LogWindow::Create(HWND father, int id)
{
	LogWindow * logwindow=new LogWindow;
	logwindow->fatherHwnd = father;
	logwindow ->hwnd=CreateWindow(windowName, NULL,
		WS_CHILDWINDOW | WS_VISIBLE,//样式
		0, 0, 100, 100,//位置和大小
		father, //父窗口句柄
		(HMENU)id,//主窗口没有菜单，因此参数是NULL。对于子窗口，相同位置的参数称为子ID（或子窗口ID）。
		(HINSTANCE)GetWindowLong(father, GWL_HINSTANCE),//
		logwindow);
	return logwindow;
}
