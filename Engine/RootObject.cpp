#include "RootObject.h"
#include "Mesh/ModelManager.h"
#include "GUI/ImGui/imgui.h"
#include "GUI/Input.h"

#include "../SuperObject.h"

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
