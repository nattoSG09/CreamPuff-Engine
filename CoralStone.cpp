#include "CoralStone.h"
#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/GUI/ImGui/imgui.h"
CoralStone::CoralStone(GameObject* _parent)
	:GameObject(_parent,"CoralStone")
{
}

void CoralStone::Initialize()
{
	hModel_ = ModelManager::Load("Assets/coral_stone_wall.fbx");
	assert(hModel_ >= 0);

    transform_.scale_ = { 2.0f,2.0f ,2.0f };
    transform_.position_.y = 7.5f;

}

void CoralStone::Update()
{
    if (Input::IsKey(DIK_W))transform_.position_.z += 0.1f;
    if (Input::IsKey(DIK_S))transform_.position_.z -= 0.1f;
    if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
    if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;

#ifdef _DEBUG
    ImGui::Begin("transform"); {
        if (ImGui::CollapsingHeader("position_")) {
            ImGui::SliderFloat("position_x", &transform_.position_.x, -100.0f, 100.0f);
            ImGui::SliderFloat("position_y", &transform_.position_.y, -100.0f, 100.0f);
            ImGui::SliderFloat("position_z", &transform_.position_.z, -100.0f, 100.0f);
        }

        if (ImGui::CollapsingHeader("rotate_")) {
            ImGui::SliderFloat("rotate_x", &transform_.rotate_.x, -0.0f, 180.0f);
            ImGui::SliderFloat("rotate_y", &transform_.rotate_.y, -0.0f, 180.0f);
            ImGui::SliderFloat("rotate_z", &transform_.rotate_.z, -0.0f, 180.0f);
            ImGui::SliderFloat("rotate_q", &transform_.rotate_.w, -0.0f, 180.0f);
        }

        if (ImGui::CollapsingHeader("scale_")) {
            ImGui::SliderFloat("scale_x", &transform_.scale_.x, -5.0f, 5.0f);
            ImGui::SliderFloat("scale_y", &transform_.scale_.y, -5.0f, 5.0f);
            ImGui::SliderFloat("scale_z", &transform_.scale_.z, -5.0f, 5.0f);
        }
    }
    ImGui::End();
#endif //_DEBUG

}

void CoralStone::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void CoralStone::Release()
{
}