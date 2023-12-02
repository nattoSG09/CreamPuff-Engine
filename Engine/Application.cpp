#include "Application.h"
#include "Windows/EditorWindow.h"
#include "Direct3D.h"

//ImGui�֘A�f�[�^�̃C���N���[�h
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

        //�g�p����E�B���h�E��ǉ�
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        //�p�ӂ����͂��̃E�B���h�E���󂾂����� false ��Ԃ�
        if (wm.GetWindows().empty())return false;

        //�E�B���h�E��������
        if (wm.InitWindows(_hInstance, _nCmdShow,WndProc) == false)return false;
    }

    // Direct3D-Initialize...
    Direct3D& d3D = Direct3D::GetInstance();{

        //Direct3D��������
        if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;
    }

    // ImGui-Initialize...
    {
        IMGUI_CHECKVERSION();	//ImGui�����o�[�W�������m�F
        ImGui::CreateContext();	//�R���e�L�X�g���쐬
        ImGuiIO& io = ImGui::GetIO();	//�K�v�ȃf�[�^���擾
        ImGui::StyleColorsDark();	//�J���[�����ɐݒ�

        //ImGui��������
        ImGui_ImplWin32_Init(wm.GetWindow("Editor"));
        ImGui_ImplDX11_Init(d3D.Device(), d3D.Context());
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
            //ImGui�̍X�V����
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Hello, world!");//ImGui�̏������J�n
            {
                //���̒��ɂ������������L�q
                //�`�悳���{�^������������...
                if (ImGui::Button("button")) {
                    PostQuitMessage(0);	//�v���O�����I��
                }
            }
            ImGui::End();//ImGui�̏������I��

            //ImGui�̕`�揈��
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            // Direct3D�̕`�揈��
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 

            pQuad_->Draw();
            
            d3D.EndDraw();
        }
    }
}

void Application::Release()
{
    //ImGui�̊J������
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