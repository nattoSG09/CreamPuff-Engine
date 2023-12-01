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

        //�g�p����E�B���h�E��ǉ�
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        //�p�ӂ����͂��̃E�B���h�E���󂾂����� false ��Ԃ�
        if (wm.GetWindows().empty())return false;

        //�E�B���h�E��������
        if (wm.InitWindows(_hInstance, _nCmdShow) == false)return false;
    }

    // Direct3D-Initialize...
    Direct3D& d3D = Direct3D::GetInstance();{

        //Direct3D��������
        if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;
    }

    pQuad_ = new Quad;
    pQuad_->Initialize();

    return true;
}

void Application::Excute()
{
    //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
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
