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
    DebugMove();
}


void NormalObject::Draw()
{
    Direct3D* d3D = &Direct3D::GetInstance();
    d3D->SetShader(DEBUG_3D);
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
    d3D->SetShader(SIMPLE_3D);
}

void NormalObject::Release()
{
}
