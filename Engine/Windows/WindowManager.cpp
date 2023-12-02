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

bool WindowManager::InitWindows(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc)
{
	for (auto it = windows_.begin(); it != windows_.end(); ++it) {
		if (it->second->Initialize(_hInstance, _nCmdShow, _wndProc) == false) return false;
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
