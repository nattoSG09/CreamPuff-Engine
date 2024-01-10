#include "Application.h"
#include "Direct3D/Direct3D.h"
#include "GUI/ImGuiManager.h"
#include "Windows/EditorWindow.h"
#include "GUI/Input.h"
#include "Direct3D/CameraManager.h"
#include "Mesh/ModelManager.h"


#include "Global.h"

#pragma comment(lib,"Winmm.lib")

Application::Application()
    :fps_(0)
{
}

Application::~Application()
{
}

bool Application::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
    // Windowの初期化
    WindowManager& wm = WindowManager::GetInstance(); {

        // 使用するウィンドウを追加
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        // 用意したはずのウィンドウが空だったら false を返す
        if (wm.GetWindows().empty())return false;

        // ウィンドウを初期化
        if (wm.InitWindows(_hInstance, _nCmdShow, WndProc) == false)return false;
    }

    // Direct3Dを初期化
    Direct3D& d3D = Direct3D::GetInstance();
    if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;

    // カメラの初期化
    CameraManager& cm = CameraManager::GetInstance();
    if (cm.HasCamera() == false)cm.AddDefaultCamera();

    // 入力デバイスを初期化
    Input::Initialize(wm.GetWindow("Editor")->WindowHandle());

#ifdef _DEBUG
    // ImGuiの初期化    
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());
#endif // DEBUG

    // ウィンドウを可視化
    wm.GetWindow("Editor")->Show(_nCmdShow);

    // 全オブジェクトを初期化
    pRootObject = new RootObject(nullptr);
    pRootObject->Initialize();

    return true;
}

void Application::Update()
{
    // メッセージループ（何か起きるのを待つ）
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // メッセージなし
        else
        {
            //指定した時間（FPSを60に設定した場合は60分の1秒）経過していなければ更新しない
            if (ShouldUpdate() == false)continue;

            // カメラの更新
            CameraManager& cm = CameraManager::GetInstance();
            cm.UpdateCurrentCamera();

            // 入力デバイスの更新
            Input::Update();

#ifdef _DEBUG
            // ImGuiの開始 & 描画
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // 全オブジェクトの更新
            pRootObject->UpdateSub();

            // Direct3Dの描画
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 
            
            // 全オブジェクトの更新
            pRootObject->DrawSub();

#ifdef _DEBUG
            // ImGuiの終了
            ImGuiManager::EndFlame();

#endif //DEBUG

            // Direct3Dの描画をリセットする処理
            d3D.EndDraw();
        }
    }
}

void Application::Release()
{
#ifdef _DEBUG
    // ImGuiの開放
    ImGuiManager::ShutDown();

#endif //DEBUG

    // 入力デバイスの開放
    Input::Release();

    // カメラの開放
    CameraManager::GetInstance().ReleaseCameras();;
    
    // モデルの開放
    ModelManager::AllRelease();

    // 全オブジェクトの解放
    pRootObject->ReleaseSub();
    SAFE_DELETE(pRootObject);

    // Direct3Dの解放
    Direct3D::GetInstance().Release();

    // Windowの解放
    WindowManager::GetInstance().ReleaseWindows();
}

// ImGuiライブラリにおけるWindowsプラットフォーム向けのウィンドウプロシージャ―
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

LRESULT Application::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
    switch (_msg)
    {
    case WM_CLOSE:PostQuitMessage(0); return 0;
    }

    if (ImGui_ImplWin32_WndProcHandler(_hWnd, _msg, _wParam, _lParam))
        return true;

    return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

bool Application::ShouldUpdate()
{
    // システムタイマーの解像度を1ミリ秒に設定
    timeBeginPeriod(1);

    static DWORD startTime = timeGetTime();
    DWORD nowTime = timeGetTime();
    static DWORD lastUpdateTime = nowTime;

    // フレームレートを確認したい時用...
    //DisplayFPS(nowTime, startTime);

    if ((nowTime - lastUpdateTime) * 60 <= 1000) return false;

    lastUpdateTime = nowTime;
    fps_++;

    //　時間計測の制度を戻す
    timeEndPeriod(1);

    return true;
}

void Application::DisplayFPS(DWORD& _nowTime, DWORD& _startTime)
{
    if (_nowTime - _startTime >= 1000){
        char disp[16];
        wsprintf(disp, "%u",fps_);

        HWND hWnd = WindowManager::GetInstance().GetWindow("Editor")->WindowHandle();
        SetWindowText(hWnd, disp);

        fps_ = 0;
        _startTime = _nowTime;
    }
}
