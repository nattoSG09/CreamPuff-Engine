#include "TestScene2.h"
#include "Engine/SceneManager.h"
#include "Engine/GUI/Input.h"

#include "Engine/Direct3D/CameraManager.h"
#include "Alisia.h"

TestScene2::TestScene2(GameObject* _parent)
	:GameObject(_parent, "TestScene2")

{
}

void TestScene2::Initialize()
{
	CameraManager& cm = CameraManager::GetInstance();
	cm.AddCamera(new Camera("AlisiaCamera", 0, 20, -27, 0, 9, 0));
	cm.SetCurrentCamera("AlisiaCamera");

	Instantiate<Alisia>(this);
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
