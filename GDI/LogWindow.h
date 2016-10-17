#pragma once
#ifdef UNICODE
typedef std::wstring TSTRING;
#else
typedef std::string TSTRING;
#endif
int CDECL MessageBoxPrintf(TCHAR * szCaption, TCHAR * szFormat, ...);
struct LogItem {
	TSTRING info;
};
typedef std::list<LogItem> LogItemList;
class LogWindow {
public:
	static TCHAR *windowName;
	static WNDCLASS wndclass;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static bool Init(HINSTANCE hinstance);
	static LogWindow* Create(HWND father, int id);
public:
	LogWindow();
	~LogWindow();
	LogItemList itemList;
	HWND hwnd;
	HWND fatherHwnd;
	void Log(TSTRING s);
	void Log(PTCHAR s);

};