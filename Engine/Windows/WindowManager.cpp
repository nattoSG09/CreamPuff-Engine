#include "WindowManager.h"

WindowManager::WindowManager()
	:windows_()
{
}

WindowManager::~WindowManager()
{
}

WindowManager& WindowManager::GetInstance()
{
	static WindowManager instance;
	return instance;
}

Window* WindowManager::GetWindow(const string& key)
{
	if (windows_.count(key) > 0) return windows_[key];
	else return nullptr;
}

bool WindowManager::InitWindows(HINSTANCE _hInstance, int _nCmdShow)
{
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (it->second->Initialize(_hInstance, _nCmdShow, WndProc) == false) return false;
	}
	return true;
}

void WindowManager::ReleaseWindows()
{
	for (auto& window : windows_) delete window.second;
	windows_.clear();
}

void WindowManager::AddWindow(const string& _key, Window* _window)
{
	windows_[_key] = _window;
}

LRESULT WindowManager::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
	case WM_CLOSE:PostQuitMessage(0); return 0;
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}
