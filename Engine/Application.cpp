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
    // Window�̏�����
    WindowManager& wm = WindowManager::GetInstance();{

        //�g�p����E�B���h�E��ǉ�
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        //�p�ӂ����͂��̃E�B���h�E���󂾂����� false ��Ԃ�
        if (wm.GetWindows().empty())return false;

        //�E�B���h�E��������
        if (wm.InitWindows(_hInstance, _nCmdShow,WndProc) == false)return false;
    }

    //Direct3D��������
    Direct3D& d3D = Direct3D::GetInstance();
    if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;

#ifdef _DEBUG
    // ImGui�̏�����
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());

#endif // DEBUG

    
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
#ifdef _DEBUG
            // ImGui�̊J�n & �`��
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // Direct3D�̕`��
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 

            pQuad_->Draw();

#ifdef _DEBUG
            // ImGui�̏I��
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
    // ImGui�̊J��
    ImGuiManager::ShutDown();

#endif //DEBUG

    // Direct3D�̉��
    Direct3D::GetInstance().Release();

    //Window�̉��
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