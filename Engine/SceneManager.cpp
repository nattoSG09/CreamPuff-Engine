#include "sceneManager.h"
#include "Mesh/ModelManager.h"
#include "../TestScene.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_SPLASH;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//�g�����W�V�������s���A�V�[���ؑւ̃^�C�~���O�ŃV�[����ύX����
	if (Transition::IsChangePoint())nextSceneID_ = tmpID_;

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
		}

		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type,float _time)
{
	//�g�����W�V���������쒆�̓V�[���J�ڂ��s��Ȃ�
	if (!Transition::IsActive()) {
		//�g�����W�V�������g��Ȃ��ꍇ�A�V�[��ID���Z�b�g
		if (!Transition::SetTransition(_type))nextSceneID_ = next;
		
		//���Ԃ��Z�b�g
		Transition::SetTime(_time);

		//�g�����W�V�������J�n���A�V�[��ID���Z�b�g
		Transition::Start();tmpID_ = next;
	}
}
void SceneManager::ChangeScene(SCENE_ID next, TRANSITION_ID _type){ChangeScene(next, _type, 2);}
void SceneManager::ChangeScene(SCENE_ID next){ChangeScene(next, TID_NONE);}


