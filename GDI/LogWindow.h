namespace skn_window{

struct LogItem {
	TSTRING info;
};
//typedef std::list<LogItem> LogItemList;
typedef std::vector<LogItem> LogItemVector;
class LogWindow {
public:
	static TCHAR *windowName;
	static WNDCLASS wndclass;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static bool Init(HINSTANCE hinstance);
	static LogWindow* Create(HWND father, int id);
	static const float logitemHeight;
public:
	LogWindow();
	~LogWindow();
	LogItemVector itemList;
	HWND hwnd;
	HWND fatherHwnd;
	void Log(TSTRING s);
	void Log(PTCHAR s,...);
private:
	bool isAutoScroll;
};

}