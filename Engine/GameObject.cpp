#include "GameObject.h"
#include <cassert>

GameObject::GameObject()
	:GameObject(nullptr)
{
}

GameObject::GameObject(GameObject* _parent)
	:GameObject(_parent,"")
{
}

GameObject::GameObject(GameObject* _parent, const string& _name)
	:name_(_name),parent_(_parent),children_()
{
	children_.clear();

	if (_parent != nullptr)
		this->transform_.pParent_ = &(_parent->transform_);
}

void GameObject::UpdateSub()
{
	//���g�̍X�V����
	Update();

	// �q�I�u�W�F�N�g�̍X�V����
	for (auto child : children_) child->UpdateSub();
}

void GameObject::DrawSub()
{
	// ���g�̕`�揈��
	Draw();

	// �q�I�u�W�F�N�g�̕`�揈��
	for (auto child : children_) child->DrawSub();
}

void GameObject::ReleaseSub()
{
	// �q�I�u�W�F�N�g�̉������
	for (auto child : children_) child->ReleaseSub();

	// ���g�̉������
	Release();
}

GameObject* GameObject::GetRootJob()
{
	// �e�I�u�W�F�N�g�����Ȃ��ꍇ
	if (parent_ == nullptr)return this;

	//�e�I�u�W�F�N�g������ꍇ
	return parent_->GetRootJob();
}

GameObject* GameObject::FindObject(const string& _objectName)
{
	return GetRootJob()->FindChildObject(_objectName);
}

GameObject* GameObject::FindChildObject(const string& _objectName)
{
	// �q�������Ȃ��ꍇ
	if (children_.empty())return nullptr;

	// ���g�������ꍇ
	if (_objectName == this->name_)return this;

	// �q�I�u�W�F�N�g����T��
	for (auto child : children_) {
		// ���O����v���Ă���ꍇ
		if (child->name_ == _objectName)return child;

		// ���g�̎q�I�u�W�F�N�g�ɂ��Ȃ��ꍇ
		GameObject* ret = child->FindChildObject(_objectName);
		if (ret != nullptr)return ret;
	}

	// ������Ȃ��ꍇ
	return nullptr;
}

void GameObject::PushBackChild(GameObject* _object)
{
	// NULL�`�F�b�N
	assert(_object != nullptr);
	
	// �e�I�u�W�F�N�g�����g�Ɏw�肵�ǉ�
	_object->parent_ = this;
	children_.push_back(_object);
}

void GameObject::PushFrontChild(GameObject* _object)
{
	// NULL�`�F�b�N
	assert(_object != nullptr);

	// �e�I�u�W�F�N�g�����g�Ɏw�肵�ǉ�
	_object->parent_ = this;
	children_.push_front(_object);
}
