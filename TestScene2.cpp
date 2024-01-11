#include "TestScene2.h"
#include "Engine/SceneManager.h"
#include "Engine/GUI/Input.h"

TestScene2::TestScene2(GameObject* _parent)
	:GameObject(_parent, "TestScene2")

{
}

void TestScene2::Initialize()
{
	int a = 0;
}

void TestScene2::Update()
{
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if (Input::IsKeyDown(DIK_G)) sm->ChangeScene(SCENE_ID_TEST);
}

void TestScene2::Draw()
{
}

void TestScene2::Release()
{
}
