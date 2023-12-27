#pragma once
#include <string>
#include <Windows.h>

using std::string;
typedef LRESULT(CALLBACK* WndProcType)(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// ウィンドウ操作の抽象化クラス
/// </summary>
class Window
{
protected:
	HWND hWnd_;/*ウィンドウハンドル*/
	int height_;/*ウィンドウの高さ*/
	int width_;/*ウィンドウの幅*/
	string name_;/*ウィンドウの名前*/

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Window();

	/// <summary>
	/// 引数付きコンストラクタ
	/// </summary>
	/// <param name="_name">ウィンドウの名前</param>
	/// <param name="_height">ウィンドウの高さ</param>
	/// <param name="_width">ウィンドウの幅</param>
	Window(const string _name,const int _height,const int _width);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Window();

	/// <summary>
	/// ウィンドウの初期化を行う
	/// </summary>
	/// <param name="_hInstance">インスタンスハンドル</param>
	/// <param name="_nCmdShow">ウィンドウの表示状態</param>
	/// <param name="_wndProc">ウィンドウプロシージャ―</param>
	/// <returns>正常に初期化を完了したら true を返す</returns>
	virtual bool Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc) = 0;
	
	/// <summary>
	/// ウィンドウを表示する
	/// </summary>
	/// <param name="_nCmdShow"></param>
	void Show(int _nCmdShow);

// ゲッター・セッター //
	HWND WindowHandle() const { return hWnd_; }
	int Height() const { return height_; }
	void SetHeight(int _height) { height_ = _height; }
	int Width() const { return width_; }
	void SetWidth(int _width) { width_ = _width; }
	string Name() const{ return name_; }
	void SetName(string _name) { name_ = _name; }
};

