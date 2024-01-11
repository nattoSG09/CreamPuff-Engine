#include "sceneManager.h"
#include "Mesh/ModelManager.h"
#include "../TestScene.h"
#include "../TestScene2.h"

SceneManager::SceneManager(GameObject * _parent)
	: GameObject(_parent, "SceneManager")
	,currentSceneID_(),nextSceneID_()
{
}

void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TEST;	
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		ModelManager::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_TEST2: Instantiate<TestScene2>(this); break;
		}

		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}