#include "Application.h"
#include "Direct3D/Direct3D.h"
#include "GUI/ImGuiManager.h"
#include "Mesh/Model.h"
#include "Windows/EditorWindow.h"
#include <thread>


namespace {
    bool g_ModelLoaded = false;
}

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
    // Window�̏�����
    WindowManager& wm = WindowManager::GetInstance(); {

        // �g�p����E�B���h�E��ǉ�
        wm.AddWindow("Editor", new EditorWindow("CreamPuff", 80 * 9, 80 * 16));

        // �p�ӂ����͂��̃E�B���h�E���󂾂����� false ��Ԃ�
        if (wm.GetWindows().empty())return false;

        // �E�B���h�E��������
        if (wm.InitWindows(_hInstance, _nCmdShow, WndProc) == false)return false;
    }

    // Direct3D��������
    Direct3D& d3D = Direct3D::GetInstance();
    if (d3D.Initialize(wm.GetWindow("Editor")) == false)return false;

#ifdef _DEBUG
    // ImGui�̏�����    
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());
#endif // DEBUG

    // �E�B���h�E������
    wm.GetWindow("Editor")->Show(_nCmdShow);

    // 3D���f���������������[�h
    pModel_ = new Model;
    pModel_->Load("Assets/blueBox.fbx", false, false);

    return true;
}

void Application::Update()
{
    // ���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // ���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // ���b�Z�[�W�Ȃ�
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

            static Transform transform;
            transform.SetRotateAxis(XMVectorSet(1, 1, 0, 0));

#ifdef _DEBUG
            ImGui::Begin("transform"); {
                if (ImGui::CollapsingHeader("position_")) {
                    ImGui::SliderFloat("position_x", &transform.position_.x, -100.0f, 100.0f);
                    ImGui::SliderFloat("position_y", &transform.position_.y, -100.0f, 100.0f);
                    ImGui::SliderFloat("position_z", &transform.position_.z, -100.0f, 100.0f);
                }

                if (ImGui::CollapsingHeader("rotate_")) {
                    ImGui::SliderFloat("rotate_x", &transform.rotate_.x, -5.0f, 5.0f);
                    ImGui::SliderFloat("rotate_y", &transform.rotate_.y, -5.0f, 5.0f);
                    ImGui::SliderFloat("rotate_z", &transform.rotate_.z, -5.0f, 5.0f);
                    ImGui::SliderFloat("rotate_q", &transform.rotate_.w, -5.0f, 5.0f);
                }

                if (ImGui::CollapsingHeader("scale_")) {
                    ImGui::SliderFloat("scale_x", &transform.scale_.x, -5.0f, 5.0f);
                    ImGui::SliderFloat("scale_y", &transform.scale_.y, -5.0f, 5.0f);
                    ImGui::SliderFloat("scale_z", &transform.scale_.z, -5.0f, 5.0f);
                }
            }
            ImGui::End();
#endif //_DEBUG

            // ���f���̕`��
            pModel_->Draw(transform);
            
#ifdef _DEBUG
            // ImGui�̏I��
            ImGuiManager::EndFlame();

#endif //DEBUG

            // Direct3D�̕`������Z�b�g���鏈��
            d3D.EndDraw();
        }
    }
}

void Application::Release()
{
#ifdef _DEBUG
    // ImGui�̊J��
    ImGuiManager::ShutDown();

#endif //DEBUG

    // Direct3D�̉��
    Direct3D::GetInstance().Release();

    // Window�̉��
    WindowManager::GetInstance().ReleaseWindows();
}

// ImGui���C�u�����ɂ�����Windows�v���b�g�t�H�[�������̃E�B���h�E�v���V�[�W���\
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