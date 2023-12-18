#include "ImGuiManager.h"

void ImGuiManager::Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(device, context);
}

void ImGuiManager::Draw()
{
    

    //// ワールドアウトライナの設定...
    //ImGui::Begin("World Outliner"); {
    //    if(ImGui::CollapsingHeader("Help")){

    //    }

    //    if (ImGui::Button("button")) {
    //        PostQuitMessage(0);
    //    }
    //}
    //ImGui::End();

    // 詳細パネルの設定...
    ImGui::Begin("Details"); {
        if (ImGui::Button("button")) {
            PostQuitMessage(0);
        }
    }
    ImGui::End();
    
    //コンテンツブラウザの設定...
    ImGui::Begin("Content Browser"); {
        if (ImGui::Button("button")) {
            PostQuitMessage(0);
        }
    }
    ImGui::End();
}

void ImGuiManager::BeginFlame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFlame()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::ShutDown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();
}
