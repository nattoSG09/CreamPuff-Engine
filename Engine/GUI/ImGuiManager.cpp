#include "ImGuiManager.h"

void ImGuiManager::Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context)
{
    IMGUI_CHECKVERSION();           // ImGui�̃o�[�W�������m�F
    ImGui::CreateContext();         // ImGui�̃R���e�L�X�g���쐬����
    ImGuiIO& io = ImGui::GetIO();   // ImGui��I/O�ݒ�ɃA�N�Z�X���邽�߂̃I�u�W�F�N�g���擾
    ImGui::StyleColorsDark();       // �_�[�N�J���[�e�[�}�ɐݒ�

    ImGui_ImplWin32_Init(windowHandle);     // indows�v���b�g�t�H�[���ɑΉ������邽�߂̏�����
    ImGui_ImplDX11_Init(device, context);   // DirectX 11��ImGui�𓝍����邽�߂̏�����
}

void ImGuiManager::Draw()
{
    

    //// ���[���h�A�E�g���C�i�̐ݒ�...
    //ImGui::Begin("World Outliner"); {
    //    if(ImGui::CollapsingHeader("Help")){

    //    }

    //    if (ImGui::Button("button")) {
    //        PostQuitMessage(0);
    //    }
    //}
    //ImGui::End();

    // �ڍ׃p�l���̐ݒ�...
    ImGui::Begin("Details"); {
        if (ImGui::Button("button")) {
            PostQuitMessage(0);
        }
    }
    ImGui::End();
    
    //�R���e���c�u���E�U�̐ݒ�...
    ImGui::Begin("Content Browser"); {
        if (ImGui::Button("button")) {
            PostQuitMessage(0);
        }
    }
    ImGui::End();
}

void ImGuiManager::BeginFlame()
{
    ImGui_ImplDX11_NewFrame();  // DirectX 11�p�̕`��f�[�^�̏���
    ImGui_ImplWin32_NewFrame(); // Windows�v���b�g�t�H�[���̓��͂�E�B���h�E�T�C�Y�̍X�V
    ImGui::NewFrame();          // ImGui�̓�����Ԃ��X�V���A�V����GUI�v�f��`�悷�邽�߂̏���
}

void ImGuiManager::EndFlame()
{
    ImGui::Render();    //  ImGui�̕`��R�}���h�𐶐�
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());   // ImGui�̕`��f�[�^��DirectX 11�ɓn���A���ۂ̕`����s�� 
}

void ImGuiManager::ShutDown()
{
    ImGui_ImplDX11_Shutdown();  // ImGui��DirectX 11�̃��\�[�X�����
    ImGui::DestroyContext();    // ImGui�̃R���e�L�X�g��j�����A���������\�[�X�����
}
