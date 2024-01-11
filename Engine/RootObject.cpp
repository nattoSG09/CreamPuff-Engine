#include "RootObject.h"
#include "Mesh/ModelManager.h"
#include "GUI/ImGui/imgui.h"
#include "GUI/Input.h"

#include "SceneManager.h"

RootObject::RootObject(GameObject* _parent)
	:GameObject(_parent,"RootObject")
{
}

RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
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
