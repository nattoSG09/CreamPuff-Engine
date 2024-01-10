#pragma once
#include "Windows/WindowManager.h"
#include "RootObject.h"

/// <summary>
/// アプリケーションを管理するクラス
/// </summary>
class Application
{
	RootObject* pRootObject;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Application();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Application();

	/// <summary>
	/// アプリケーションの初期化処理を行う
	/// </summary>
	/// <param name="_hInstance">インスタンスハンドル</param>
	/// <param name="_nCmdShow">ウィンドウの表示状態</param>
	/// <returns>正常に初期化が完了したら true を返す</returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);

	/// <summary>
	/// アプリケーションの更新処理を行う
	/// </summary>
	void Update();

	/// <summary>
	/// アプリケーションの開放処理を行う
	/// </summary>
	void Release();

	/// <summary>
	/// ウィンドウプロシージャ―
	/// </summary>
	/// <param name="_hWnd">ウィンドウのハンドル</param>
	/// <param name="_msg">ウィンドウプロシージャ―に送られるメッセージ</param>
	/// <param name="_wParam">メッセージに関連する追加情報</param>
	/// <param name="_lParam">メッセージに関連する追加情報</param>
	/// <returns>LRESULT型の値</returns>
	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);


private:
	int fps_;
	bool ShouldUpdate();
	void DisplayFPS(DWORD& _nowTime, DWORD& _startTime);
};
