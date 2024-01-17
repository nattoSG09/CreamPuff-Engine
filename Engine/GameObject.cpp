#include "GameObject.h"
#include <cassert>
#include "GUI/ImGui/imgui.h"

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

void GameObject::KillAllChildren()
{
	// 子オブジェクトがいなければreturn
	if (children_.empty())return;

	//イテレータ
	auto it = children_.begin();	//先頭
	auto end = children_.end();	//末尾

	//子オブジェクトを1個ずつ削除
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = children_.erase(it);
	}

	//リストをクリア
	children_.clear();
}

void GameObject::KillObjectSub(GameObject* _object)
{
	if (!children_.empty())
	{
		auto list = _object->children_;
		auto it = list.begin();
		auto end = list.end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete* it;
			it = list.erase(it);
		}
		list.clear();
	}
	_object->Release();
}

void GameObject::DebugMove()
{
#ifdef _DEBUG
	ImGui::Begin(name_.c_str()); {
		if (ImGui::CollapsingHeader("position_")) {
			ImGui::SliderFloat("position_x", &transform_.position_.x, -100.0f, 100.0f);
			ImGui::SliderFloat("position_y", &transform_.position_.y, -100.0f, 100.0f);
			ImGui::SliderFloat("position_z", &transform_.position_.z, -100.0f, 100.0f);
		}

		if (ImGui::CollapsingHeader("rotate_")) {
			ImGui::SliderFloat("rotate_x", &transform_.rotate_.x, 0.f, 360.0f);
			ImGui::SliderFloat("rotate_y", &transform_.rotate_.y, 0.f, 360.0f);
			ImGui::SliderFloat("rotate_z", &transform_.rotate_.z, 0.f, 360.0f);
			ImGui::SliderFloat("rotate_q", &transform_.rotate_.w, 0.f, 360.0f);
		}

		if (ImGui::CollapsingHeader("scale_")) {
			static bool fixed = false;
			ImGui::Checkbox("fixed", &fixed);
			if (fixed == false) {
				ImGui::SliderFloat("scale_x", &transform_.scale_.x, -5.0f, 5.0f);
				ImGui::SliderFloat("scale_y", &transform_.scale_.y, -5.0f, 5.0f);
				ImGui::SliderFloat("scale_z", &transform_.scale_.z, -5.0f, 5.0f);
			}

		}
	}
	ImGui::End();
#endif //_DEBUG

}
