#pragma once
#include "Windows/WindowManager.h"

class Model;

class Application
{
	Model* pModel_;
public:
	Application();
	~Application();

	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);
	void Excute();
	void Release();
	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
};
