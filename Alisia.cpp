#include "Alisia.h"

#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/GUI/ImGui/imgui.h"

Alisia::Alisia(GameObject* _parent)
	:GameObject(_parent,"Alisia")
{
}

void Alisia::Initialize()
{
	hModel_ = ModelManager::Load("Assets/Alicia/FBX/Alicia_solid_Unity.FBX", false, true);
	assert(hModel_ >= 0);

    transform_.scale_ = { 0.1f,0.1f,0.1f };
    transform_.rotate_.y = 0;
}

void Alisia::Update()
{
    if (Input::IsKey(DIK_W))transform_.position_.z += 0.1f;
    if (Input::IsKey(DIK_S))transform_.position_.z -= 0.1f;
    if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
    if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;

    DebugMove();

}

void Alisia::Draw()
{
    Direct3D* d3D = &Direct3D::GetInstance();
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void Alisia::Release()
{
}
