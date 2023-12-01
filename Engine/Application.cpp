#include "Application.h"
#include "Windows/EditorWindow.h"
#include "Direct3D.h"

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
        if (wm.InitWindows(_hInstance, _nCmdShow) == false)return false;
    }

    // Direct3D-Initialize...
    Direct3D& d3D = Direct3D::GetInstance();{

        //Direct3Dを初期化
        if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;
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
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.Draw();

            pQuad_->Draw();

            d3D.Update();
        }
    }
}

void Application::Release()
{
    pQuad_->Release();
    Direct3D::GetInstance().Release();
    WindowManager::GetInstance().ReleaseWindows();
}
