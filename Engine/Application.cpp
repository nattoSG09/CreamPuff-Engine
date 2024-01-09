#include "Application.h"
#include "Direct3D/Direct3D.h"
#include "GUI/ImGuiManager.h"
#include "Windows/EditorWindow.h"
#include "GUI/Input.h"
#include "Direct3D/CameraManager.h"
#include "Mesh/ModelManager.h"

#include "../RootObject.h"
#include "Global.h"

namespace {
    RootObject* g_pRootObject = nullptr;
}

Application::Application()
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
    g_pRootObject = new RootObject(nullptr);
    g_pRootObject->Initialize();

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
            // カメラの更新
            CameraManager& cm = CameraManager::GetInstance();
            cm.UpdateCurrentCamera();

            // 入力デバイスの更新
            Input::Update();

            // 全オブジェクトの更新
            g_pRootObject->UpdateSub();

#ifdef _DEBUG
            // ImGuiの開始 & 描画
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // Direct3Dの描画
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 
            
            // 全オブジェクトの更新
            g_pRootObject->DrawSub();

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
    g_pRootObject->ReleaseSub();
    SAFE_DELETE(g_pRootObject);

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