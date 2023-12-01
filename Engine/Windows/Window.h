#pragma once
#include <Windows.h>
#include <string>

using std::string;
typedef LRESULT(CALLBACK* WndProcType)(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// ウィンドウ操作の抽象化クラス
/// </summary>
class Window
{
protected:
	HWND hWnd_;
	int height_;
	int width_;
	string name_;

public:
	Window();
	Window(const string _name,const int _height,const int _width);
	~Window();

	virtual bool Initialize(HINSTANCE _hInstance, int nCmdShow, WndProcType _wndProc) = 0;

// ゲッター・セッター //
	HWND WindowHandle() { return hWnd_; }
	int Height() { return height_; }
	void SetHeight(int _height) { height_ = _height; }
	int Width() { return width_; }
	void SetWidth(int _width) { width_ = _width; }
	string Name() { return name_; }
	void SetName(string _name) { name_ = _name; }
};

