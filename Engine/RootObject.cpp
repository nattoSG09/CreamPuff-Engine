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
	transform_ = *AddComponent<Transform>();

	Instantiate<SuperObject>(this);

}

void RootObject::Update()
{
	transform_.position_.x += 0.1f;
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}
