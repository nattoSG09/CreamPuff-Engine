#include "SuperObject.h"
#include "Engine/Mesh/ModelManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/GUI/ImGui/imgui.h"
#include "Engine/Direct3D/CameraManager.h"

SuperObject::SuperObject(GameObject* _parent)
	:GameObject(_parent,"SuperObject"),hModel_(-1)
{
}

void SuperObject::Initialize()
{
	hModel_ = ModelManager::Load("Assets/floor_tiles_06.fbx");
	assert(hModel_ >= 0);
}

void SuperObject::Update()
{
}

void SuperObject::Draw()
{
    Direct3D* d3D = &Direct3D::GetInstance();
    d3D->SetShader(SIMPLE_3D);
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void SuperObject::Release()
{
}
