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
	//自身の更新処理
	Update();

	// 子オブジェクトの更新処理
	for (auto child : children_) child->UpdateSub();
}

void GameObject::DrawSub()
{
	// 自身の描画処理
	Draw();

	// 子オブジェクトの描画処理
	for (auto child : children_) child->DrawSub();
}

void GameObject::ReleaseSub()
{
	// 子オブジェクトの解放処理
	for (auto child : children_) child->ReleaseSub();

	// 自身の解放処理
	Release();
}

GameObject* GameObject::GetRootJob()
{
	// 親オブジェクトがいない場合
	if (parent_ == nullptr)return this;

	//親オブジェクトがいる場合
	return parent_->GetRootJob();
}

GameObject* GameObject::FindObject(const string& _objectName)
{
	return GetRootJob()->FindChildObject(_objectName);
}

GameObject* GameObject::FindChildObject(const string& _objectName)
{
	// 子供がいない場合
	if (children_.empty())return nullptr;

	// 自身だった場合
	if (_objectName == this->name_)return this;

	// 子オブジェクトから探す
	for (auto child : children_) {
		// 名前が一致している場合
		if (child->name_ == _objectName)return child;

		// 自身の子オブジェクトにいない場合
		GameObject* ret = child->FindChildObject(_objectName);
		if (ret != nullptr)return ret;
	}

	// 見つからない場合
	return nullptr;
}

void GameObject::PushBackChild(GameObject* _object)
{
	// NULLチェック
	assert(_object != nullptr);
	
	// 親オブジェクトを自身に指定し追加
	_object->parent_ = this;
	children_.push_back(_object);
}

void GameObject::PushFrontChild(GameObject* _object)
{
	// NULLチェック
	assert(_object != nullptr);

	// 親オブジェクトを自身に指定し追加
	_object->parent_ = this;
	children_.push_front(_object);
}
