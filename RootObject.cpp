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
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}
