#include "TestScene.h"
#include "SuperObject.h"

#include "SuperObject.h"
#include "Engine/SceneManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/Direct3D/CameraManager.h"
#include "Alisia.h"

#include "NormalObject.h"

TestScene::TestScene(GameObject* _parent)
	:GameObject(_parent,"TestScene")
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	sm->ChangeScene(SCENE_ID_TEST2);
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
