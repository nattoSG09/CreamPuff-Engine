#include "TestScene.h"
#include "SuperObject.h"

#include "SuperObject.h"
#include "Engine/SceneManager.h"
#include "Engine/GUI/Input.h"
#include "Engine/Direct3D/CameraManager.h"
#include "Alisia.h"



TestScene::TestScene(GameObject* _parent)
	:GameObject(_parent,"TestScene")
{
}

void TestScene::Initialize()
{
	CameraManager& cm = CameraManager::GetInstance();
	cm.AddCamera(new Camera("AlisiaCamera", 0, 20, -27, 0, 9, 0));
	cm.SetCurrentCamera("AlisiaCamera");

	Instantiate<Alisia>(this);
	Instantiate<SuperObject>(this);
}

void TestScene::Update()
{
	SceneManager* sm = (SceneManager*)FindObject("SceneManager");
	if(Input::IsKeyDown(DIK_G))	sm->ChangeScene(SCENE_ID_TEST2);
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
