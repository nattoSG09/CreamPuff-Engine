#include "Application.h"
#include "Windows/EditorWindow.h"
#include "Direct3D.h"

//ImGui関連データのインクルード
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "../Quad.h"

Application::Application()
{
}

Application::~Application()
{
}


bool Application::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
    // Window-Initialize...
    WindowManager& wm = WindowManager::GetInstance();{

        //使用するウィンドウを追加
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        //用意したはずのウィンドウが空だったら false を返す
        if (wm.GetWindows().empty())return false;

        //ウィンドウを初期化
        if (wm.InitWindows(_hInstance, _nCmdShow,WndProc) == false)return false;
    }

    // Direct3D-Initialize...
    Direct3D& d3D = Direct3D::GetInstance();{

        //Direct3Dを初期化
        if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;
    }

    // ImGui-Initialize...
    {
        IMGUI_CHECKVERSION();	//ImGui導入バージョンを確認
        ImGui::CreateContext();	//コンテキストを作成
        ImGuiIO& io = ImGui::GetIO();	//必要なデータを取得
        ImGui::StyleColorsDark();	//カラーを黒に設定

        //ImGuiを初期化
        ImGui_ImplWin32_Init(wm.GetWindow("Editor"));
        ImGui_ImplDX11_Init(d3D.Device(), d3D.Context());
    }

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
            //ImGuiの更新処理
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello, world!");//ImGuiの処理を開始
            {
                //この中にしたい処理を記述
                //描画されるボタンを押したら...
                if (ImGui::Button("button")) {
                    PostQuitMessage(0);	//プログラム終了
                }
            }
            ImGui::End();//ImGuiの処理を終了

            //ImGuiの描画処理
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            // Direct3Dの描画処理
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 

            pQuad_->Draw();
            
            d3D.EndDraw();
        }
    }
}

void Application::Release()
{
    //ImGuiの開放処理
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();

    pQuad_->Release();

    Direct3D::GetInstance().Release();
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