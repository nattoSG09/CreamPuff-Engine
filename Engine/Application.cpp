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

    // �J�����̏�����
    CameraManager& cm = CameraManager::GetInstance();
    if (cm.HasCamera() == false)cm.AddDefaultCamera();

    // ���̓f�o�C�X��������
    Input::Initialize(wm.GetWindow("Editor")->WindowHandle());

#ifdef _DEBUG
    // ImGui�̏�����    
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());
#endif // DEBUG

    // �E�B���h�E������
    wm.GetWindow("Editor")->Show(_nCmdShow);

    // �S�I�u�W�F�N�g��������
    g_pRootObject = new RootObject(nullptr);
    g_pRootObject->Initialize();

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
            // �J�����̍X�V
            CameraManager& cm = CameraManager::GetInstance();
            cm.UpdateCurrentCamera();

            // ���̓f�o�C�X�̍X�V
            Input::Update();

            // �S�I�u�W�F�N�g�̍X�V
            g_pRootObject->UpdateSub();

#ifdef _DEBUG
            // ImGui�̊J�n & �`��
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // Direct3D�̕`��
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 
            
            // �S�I�u�W�F�N�g�̍X�V
            g_pRootObject->DrawSub();

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

    // ���̓f�o�C�X�̊J��
    Input::Release();

    // �J�����̊J��
    CameraManager::GetInstance().ReleaseCameras();;
    
    // ���f���̊J��
    ModelManager::AllRelease();

    // �S�I�u�W�F�N�g�̉��
    g_pRootObject->ReleaseSub();
    SAFE_DELETE(g_pRootObject);

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