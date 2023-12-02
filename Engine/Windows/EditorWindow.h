#pragma once
#include "Window.h"

/// <summary>
/// 「エディターウィンドウ」を操作するクラス
/// </summary>
class EditorWindow : public Window
{
public:
	EditorWindow();
	EditorWindow(const string _name, const int _height, const int _width);
	~EditorWindow();

	bool Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc) override;

private:
	void InitWindowClass(WNDCLASSEX& _wc, HINSTANCE _hInstance, WndProcType _wndProc);
	void CalcWindowSize(int& _height, int& _width);
};