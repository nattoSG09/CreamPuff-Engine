#include "TestScene.h"
#include "SuperObject.h"

#include "Engine/Mesh/Image.h"

TestScene::TestScene(GameObject* _parent)
	:GameObject(_parent,"TestScene")
{

}

void TestScene::Initialize()
{
	Instantiate<SuperObject>(this);
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
