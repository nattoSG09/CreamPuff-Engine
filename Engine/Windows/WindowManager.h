#pragma once

#include <map>
using std::map;
#include "Window.h"


/// <summary>
/// ウィンドウ管理クラス
/// </summary>
class WindowManager
{
private:
	map<string, Window*> windows_;
	WindowManager();
	~WindowManager();

public:
	static WindowManager& GetInstance();
	Window* GetWindow(const string& _key);
	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	bool InitWindows(HINSTANCE _hInstance, int nCmdShow);
	void ReleaseWindows();
	void AddWindow(const string& _key, Window* _window);

	map<string, Window*>& GetWindows() { return windows_; }

};

