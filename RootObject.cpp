#include "RootObject.h"
#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/ImGui/imgui.h"
#include "Engine/GUI/Input.h"

RootObject::RootObject(GameObject* _parent)
	:GameObject(_parent,"RootObject")
{
}

RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	hModel_ = ModelManager::Load("Assets/blueBox.fbx");
	assert(hModel_ >= 0);
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
    // transformÇÃà⁄ìÆèàóù
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

    ModelManager::SetTransform(hModel_, transform);
    ModelManager::Draw(hModel_);
}

void RootObject::Release()
{
}
