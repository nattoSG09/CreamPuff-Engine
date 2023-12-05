#include "Application.h"
#include "Windows/EditorWindow.h"
#include "Direct3D.h"
#include "ImGuiManager.h"

#include "../Quad.h"

Application::Application()
    :pQuad_(nullptr)
{
}

Application::~Application()
{
}

bool Application::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
    // Windowの初期化
    WindowManager& wm = WindowManager::GetInstance();{

        //使用するウィンドウを追加
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        //用意したはずのウィンドウが空だったら false を返す
        if (wm.GetWindows().empty())return false;

        //ウィンドウを初期化
        if (wm.InitWindows(_hInstance, _nCmdShow,WndProc) == false)return false;
    }

    //Direct3Dを初期化
    Direct3D& d3D = Direct3D::GetInstance();
    if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;

#ifdef _DEBUG
    // ImGuiの初期化
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());

#endif // DEBUG

    
    pQuad_ = new Quad;
    pQuad_->Initialize();

    return true;
}

void Application::Excute()
{
    //メッセージループ（何か起きるのを待つ）
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
#ifdef _DEBUG
            // ImGuiの開始 & 描画
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // Direct3Dの描画
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 

            pQuad_->Draw();

#ifdef _DEBUG
            // ImGuiの終了
            ImGuiManager::EndFlame();

#endif //DEBUG

            d3D.EndDraw();
        }
    }
}

void Application::Release()
{

    pQuad_->Release();

#ifdef _DEBUG
    // ImGuiの開放
    ImGuiManager::ShutDown();

#endif //DEBUG

    // Direct3Dの解放
    Direct3D::GetInstance().Release();

    //Windowの解放
    WindowManager::GetInstance().ReleaseWindows();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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