#include "normalObject.h"

#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/ImGui/imgui.h"

NormalObject::NormalObject(GameObject* _parent)
	:GameObject(_parent,"NormalObject")
{
}

void NormalObject::Initialize()
{
	hModel_ = ModelManager::Load("Assets/coral_stone_wall.fbx");
    transform_.scale_ = { 2.f,2.f,2.f };
    transform_.position_ = { 0.f,9.f,10.f };
}

void NormalObject::Update()
{
#ifdef _DEBUG
    ImGui::Begin("NormalObject"); {
        if (ImGui::CollapsingHeader("position_")) {
            ImGui::SliderFloat("position_x", &transform_.position_.x, -100.0f, 100.0f);
            ImGui::SliderFloat("position_y", &transform_.position_.y, -100.0f, 100.0f);
            ImGui::SliderFloat("position_z", &transform_.position_.z, -100.0f, 100.0f);
        }

        if (ImGui::CollapsingHeader("rotate_")) {
            ImGui::SliderFloat("rotate_x", &transform_.rotate_.x, 0.f, 360.0f);
            ImGui::SliderFloat("rotate_y", &transform_.rotate_.y, 0.f, 360.0f);
            ImGui::SliderFloat("rotate_z", &transform_.rotate_.z, 0.f, 360.0f);
            ImGui::SliderFloat("rotate_q", &transform_.rotate_.w, 0.f, 360.0f);
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

void NormalObject::Draw()
{
    Direct3D* d3D = &Direct3D::GetInstance();
    d3D->SetShader(NORMAL_3D);
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
    d3D->SetShader(SIMPLE_3D);
}

void NormalObject::Release()
{
}
