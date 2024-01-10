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
	hModel_ = ModelManager::Load("Assets/blueBox.fbx");
	assert(hModel_ >= 0);
}

void SuperObject::Update()
{

}

void SuperObject::Draw()
{
	ModelManager::SetTransform(hModel_, transform_);
	ModelManager::Draw(hModel_);
}

void SuperObject::Release()
{
}
