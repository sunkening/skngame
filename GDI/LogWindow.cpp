
#include <windows.h>
#include <string>
#include <vector>
#include "common.h"
#include "utils.h"
#include <tchar.h>   
#include <stdio.h> 
#include "LogWindow.h"
namespace skn_window {

	TCHAR * LogWindow::windowName = 0;
	WNDCLASS LogWindow::wndclass = { 0 };
	LRESULT CALLBACK LogWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HDC                                          hdc;
		PAINTSTRUCT                          ps;
		RECT                                         rect;

		LogWindow *logwindow = (LogWindow *)GetWindowLong(hwnd, 0);
		static int cxChar, cyChar;//字体的平均宽度和高度
		static int  cxClient, cyClient;

		SCROLLINFO  si;
		static int num = 0, iVertPos = 0;
		switch (message)
		{
		case   WM_CREATE: {
			logwindow = (LogWindow *)((CREATESTRUCT *)lParam)->lpCreateParams;
			SetWindowLong(hwnd, 0, (LONG)logwindow);       // on/off flag
			cxChar = LOWORD(GetDialogBaseUnits());
			cyChar = HIWORD(GetDialogBaseUnits());
			return 0;
		}
		case   WM_SIZE: {
			//MessageBoxPrintf(TEXT("WM_SIZE"), TEXT("WM_SIZE"));
			int logNum = logwindow->itemList.size();
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = logNum>0?1:0;
			si.nPage = cyClient / (cyChar*LogWindow::logitemHeight);
			si.nMax = logNum ;
			si.nPos = iVertPos;
			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
			return 0;
		}
		case   WM_LBUTTONDOWN:
			MessageBox(NULL, TEXT("点击了左建"), windowName, MB_ICONERROR);
			/*SetWindowLong(hwnd, 0, 1 ^ GetWindowLong(hwnd, 0));
			InvalidateRect(hwnd, NULL, FALSE);*/
			return 0;
		case   WM_PAINT: {
			hdc = BeginPaint(hwnd, &ps);
			int logNum = logwindow->itemList.size();
			//LogItemVector::iterator iter;
			int i = 0;
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hwnd, SB_VERT, &si);
			iVertPos = si.nPos;
			ps.rcPaint.top -= 13;
			int iPaintBeg = max(0, iVertPos + ps.rcPaint.top / cyChar-1);
			int iPaintEnd = min(logNum - 1, iVertPos + ps.rcPaint.bottom / cyChar-1);
			//MessageBoxPrintf(TEXT(""), TEXT("%d  %d  %d  %d"), iPaintBeg, iPaintEnd, iVertPos,si.nPage);
			//GetClientRect(hwnd, &rect);
			//Rectangle(hdc, 0, 0, rect.right, rect.bottom);
			for (i = iPaintBeg; i <= iPaintEnd; i++)
			{
				LogItem *item = &(logwindow->itemList.at(i));
				int y = (i - iVertPos+1)*cyChar;
				TextOut(hdc, cxChar, y, (PTCHAR)(item->info.c_str()), item->info.length());
			}
			EndPaint(hwnd, &ps);
			return 0;
		}
		case   WM_COMMAND: {
			/*ScrollWindow(hwnd, 0, -cyChar, &rect, &rect);
			hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
			TextOut(hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1),
				szBuffer,
				wsprintf(szBuffer, szFormat,
					message == WM_DRAWITEM ? TEXT("WM_DRAWITEM") :
					TEXT("WM_COMMAND"),
					HIWORD(wParam), LOWORD(wParam),
					HIWORD(lParam), LOWORD(lParam)));
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, &rect);*/

			return 0;
		}

		case WM_VSCROLL: {
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
				
			case   SB_BOTTOM:
				si.nPos = max(si.nMax-si.nPage+1,1);
				break;
			}
			si.fMask = SIF_POS;
			//GetScrollInfo(hwnd, SB_VERT, &si);
			if (si.nPos != iVertPos)
			{
				SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
				ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
				//InvalidateRect(hwnd, 0, 0);
				UpdateWindow(hwnd);
			}
			if (si.nPage>si.nMax)
			{
				InvalidateRect(hwnd, 0, 0);
			}
			return 0;
		}
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
		isAutoScroll = true;
	}

	LogWindow::~LogWindow()
	{

	}

	void LogWindow::Log(TSTRING s)
	{
		LogItem logitem;
		logitem.info = s;
		itemList.push_back(logitem);
		//InvalidateRect(hwnd, 0, 0);
		SCROLLINFO  si;
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_VERT, &si);
		si.nMax = itemList.size() ;
		si.nMin = 1;
		si.fMask = SIF_RANGE;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);//如果ScrollInfo的值改变了，会发送WM_SIZE消息。
		//if (si.nMax<(itemList.size()-1))
		//{
		//	//MessageBoxPrintf(TEXT("WM_SIZE"), TEXT("si.nPos  %d   %d"), si.nMax - si.nPage + 1, si.nPos);
		//	/*if ((si.nMax - si.nPage+1) > si.nPos)
		//	{
		//		si.fMask = SIF_RANGE | SIF_POS;
		//		si.nMax = itemList.size() - 1;
		//		si.nPos = si.nMax - si.nPage + 1;
		//		
		//	}
		//	else {
		//		si.nMax = itemList.size() - 1;
		//		si.fMask = SIF_RANGE;
		//	}*/
		//	si.nMax = itemList.size() - 1;
		//	si.fMask = SIF_RANGE;
		//	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);//如果ScrollInfo的值改变了，会发送WM_SIZE消息。
		//}
		
			//InvalidateRect(hwnd, 0, 0);
		
			SendMessage(hwnd,WM_VSCROLL, SB_BOTTOM,0);
	}

	void LogWindow::Log(PTCHAR szFormat, ...)
	{
		TCHAR buffer[1024];
		va_list pArgList;
		va_start(pArgList, szFormat);
		_vsntprintf(buffer, sizeof(buffer) / sizeof(TCHAR),
			szFormat, pArgList);
		va_end(pArgList);
		TSTRING s = buffer;
		Log(s);
	}

	LogWindow* LogWindow::Create(HWND father, int id)
	{
		LogWindow * logwindow = new LogWindow;
		logwindow->fatherHwnd = father;
		logwindow->hwnd = CreateWindow(windowName, NULL,
			WS_OVERLAPPEDWINDOW | WS_CHILDWINDOW | WS_VISIBLE | WS_VSCROLL,//样式
			0, 0, 100, 100,//位置和大小
			father, //父窗口句柄
			(HMENU)id,//主窗口没有菜单，因此参数是NULL。对于子窗口，相同位置的参数称为子ID（或子窗口ID）。
			(HINSTANCE)GetWindowLong(father, GWL_HINSTANCE),//
			logwindow);
		return logwindow;
	}

	const float LogWindow::logitemHeight = 1.0f;
}