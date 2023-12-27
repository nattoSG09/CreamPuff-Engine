#pragma once
#include "Window.h"

#include <map>
using std::map;

/// <summary>
/// ウィンドウ管理クラス
/// </summary>
class WindowManager
{
private:
	map<string, Window*> windows_;/*ウィンドウを格納するマップ*/

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WindowManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WindowManager();

public:
	/// <summary>
	/// WindowsManagerのインスタンスを取得する
	/// </summary>
	/// <returns>WindowsManagerのインスタンス</returns>
	static WindowManager& GetInstance();

	/// <summary>
	/// 指定されたキーに対応するウィンドウを取得する
	/// </summary>
	/// <param name="_key">ウィンドウのキー</param>
	/// <returns>指定されたキーに対応するウィンドウ</returns>
	Window* GetWindow(const string& _key);
	
	/// <summary>
	/// 追加されたすべてのウィンドウの初期化を行う
	/// </summary>
	/// <param name="_hInstance">インスタンスハンドル</param>
	/// <param name="_nCmdShow">ウィンドウの表示状態</param>
	/// <param name="_wndProc">ウィンドウプロシージャ―</param>
	/// <returns>正常に初期化を完了したら true を返す</returns>
	bool InitWindows(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc);
	
	/// <summary>
	/// すべてのウィンドウの開放を行う
	/// </summary>
	void ReleaseWindows();

	/// <summary>
	/// ウィンドウを追加する
	/// </summary>
	/// <param name="_key">ウィンドウのキー</param>
	/// <param name="_window">追加するウィンドウ</param>
	void AddWindow(const string& _key, Window* _window);

	/// <summary>
	/// 登録されたすべてのウィンドウを取得する
	/// </summary>
	/// <returns>ウィンドウを格納したmap</returns>
	map<string, Window*>& GetWindows() { return windows_; }

};

