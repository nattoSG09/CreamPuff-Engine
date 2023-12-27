#include "ImGuiManager.h"

void ImGuiManager::Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context)
{
    IMGUI_CHECKVERSION();           // ImGuiのバージョンを確認
    ImGui::CreateContext();         // ImGuiのコンテキストを作成する
    ImGuiIO& io = ImGui::GetIO();   // ImGuiのI/O設定にアクセスするためのオブジェクトを取得
    ImGui::StyleColorsDark();       // ダークカラーテーマに設定

    ImGui_ImplWin32_Init(windowHandle);     // indowsプラットフォームに対応させるための初期化
    ImGui_ImplDX11_Init(device, context);   // DirectX 11とImGuiを統合するための初期化
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
    ImGui_ImplDX11_NewFrame();  // DirectX 11用の描画データの準備
    ImGui_ImplWin32_NewFrame(); // Windowsプラットフォームの入力やウィンドウサイズの更新
    ImGui::NewFrame();          // ImGuiの内部状態を更新し、新しいGUI要素を描画するための準備
}

void ImGuiManager::EndFlame()
{
    ImGui::Render();    //  ImGuiの描画コマンドを生成
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());   // ImGuiの描画データをDirectX 11に渡し、実際の描画を行う 
}

void ImGuiManager::ShutDown()
{
    ImGui_ImplDX11_Shutdown();  // ImGuiがDirectX 11のリソースを解放
    ImGui::DestroyContext();    // ImGuiのコンテキストを破棄し、メモリリソースを解放
}
