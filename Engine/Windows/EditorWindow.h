#pragma once
#include "Window.h"

/// <summary>
/// 「エディターウィンドウ」を操作するクラス
/// </summary>
class EditorWindow : public Window
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EditorWindow();

	/// <summary>
	/// 引数付きコンストラクタ
	/// </summary>
	/// <param name="_name">ウィンドウの名前</param>
	/// <param name="_height">ウィンドウの高さ</param>
	/// <param name="_width">ウィンドウの幅</param>
	EditorWindow(const string _name, const int _height, const int _width);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EditorWindow();

	/// <summary>
	/// 初期化を行う
	/// </summary>
	/// <param name="_hInstance">インスタンスハンドル</param>
	/// <param name="_nCmdShow">ウィンドウの表示状態</param>
	/// <param name="_wndProc">ウィンドウプロシージャ―</param>
	/// <returns>正常に初期化を完了したら ture を返す</returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc) override;

private:
	/// <summary>
	/// ウィンドウ情報の設定・初期化を行う
	/// </summary>
	/// <param name="_wc">ウィンドウクラス構造体への参照</param>
	/// <param name="_hInstance">インスタンスハンドル</param>
	/// <param name="_wndProc">ウィンドウプロシージャ</param>
	void InitWindowClass(WNDCLASSEX& _wc, HINSTANCE _hInstance, WndProcType _wndProc);

	/// <summary>
	/// ウィンドウサイズの計算を行う
	/// </summary>
	/// <param name="_height">ウィンドウの高さ</param>
	/// <param name="_width">ウィンドウの幅</param>
	void CalcWindowSize(int& _height, int& _width);
};