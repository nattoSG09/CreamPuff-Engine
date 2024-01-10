#include "SuperObject.h"
#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/GUI/ImGui/imgui.h"

SuperObject::SuperObject(GameObject* _parent)
	:GameObject(_parent,"SuperObject"),hModel_(-1)
{
}

void SuperObject::Initialize()
{
	transform_ = *AddComponent<Transform>(this->parent_);
	hModel_ = ModelManager::Load("Assets/blueBox.fbx");
	assert(hModel_ >= 0);
}

void SuperObject::Update()
{
    if (Input::IsKey(DIK_W))transform_.position_.z -= 0.001f;
    if (Input::IsKey(DIK_A))transform_.position_.x += 0.001f;
    if (Input::IsKey(DIK_S))transform_.position_.z += 0.001f;
    if (Input::IsKey(DIK_D))transform_.position_.x -= 0.001f;
}

void SuperObject::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void SuperObject::Release()
{
}
