#include "Application.h"
#include "Direct3D/Direct3D.h"
#include "GUI/ImGuiManager.h"
#include "Windows/EditorWindow.h"
#include "GUI/Input.h"
#include "Direct3D/CameraManager.h"
#include "Mesh/ModelManager.h"


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
    cm.AddCamera(new Camera("camera1", 0, 3, -7, 0, 0, 0));

    // 入力デバイスを初期化
    Input::Initialize(wm.GetWindow("Editor")->WindowHandle());

#ifdef _DEBUG
    // ImGuiの初期化    
    ImGuiManager::Initialize(wm.GetWindow("Editor")->WindowHandle(), d3D.Device(), d3D.Context());
#endif // DEBUG

    // ウィンドウを可視化
    wm.GetWindow("Editor")->Show(_nCmdShow);

    //// 3Dモデルを初期化しロード
    hModel_ = ModelManager::Load("Assets/blueBox.fbx");
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
            if (Input::IsKeyDown(DIK_0))cm.SetCurrentCamera("default");
            if (Input::IsKeyDown(DIK_1))cm.SetCurrentCamera("camera1");
            cm.UpdateCurrentCamera();

            // 入力デバイスの更新
            Input::Update();

#ifdef _DEBUG
            // ImGuiの開始 & 描画
            ImGuiManager::BeginFlame();
            ImGuiManager::Draw();

#endif //DEBUG

            // Direct3Dの描画
            Direct3D& d3D = Direct3D::GetInstance();
            d3D.BeginDraw(); 
            
            // transformの移動処理
            static Transform transform; 
            {
                transform.SetRotateAxis(XMVectorSet(1, 1, 0, 0));

                if (Input::IsKey(DIK_W))transform.position_.z -= 0.001f;
                if (Input::IsKey(DIK_A))transform.position_.x += 0.001f;
                if (Input::IsKey(DIK_S))transform.position_.z += 0.001f;
                if (Input::IsKey(DIK_D))transform.position_.x -= 0.001f;

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

            }
           
            // モデルの描画
            ModelManager::SetTransform(hModel_, transform);
            ModelManager::Draw(hModel_);

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