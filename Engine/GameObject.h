#pragma once
#include <string>
#include <list>
#include "Components/Transform.h"

using std::string;
using std::list;

class GameObject
{
protected:
	string name_;					// 名前
	GameObject* parent_;			// 親オブジェクト
	list<GameObject*> children_;	// 子オブジェクトの配列
	Transform transform_;			// 変換行列

public:
	GameObject();
	GameObject(GameObject* _parent);
	GameObject(GameObject* _parent, const string& _name);

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	GameObject* GetRootJob();
	GameObject* FindObject(const string& _objectName);
	GameObject* FindChildObject(const string& _objectName);
	list<GameObject*>& GetChildren() { return children_; }

	void PushBackChild(GameObject* _object);
	void PushFrontChild(GameObject* _object);

	void KillAllChildren();

	void KillObjectSub(GameObject* _object);

	// アクセス関数 //
	XMFLOAT3 GetPosition() { return transform_.GetPosition(); }
	void SetPosition(const XMFLOAT3 _position) { transform_.SetPosition(_position); }
	void SetPosition(float _x, float _y, float _z) { SetPosition(XMFLOAT3(_x, _y, _z)); }

	XMFLOAT4 GetRotate() { return transform_.GetRotate(); }
	void SetRotate(const XMFLOAT4 _rotate) { transform_.SetRotate(_rotate); }
	void SetRotate(float _x, float _y, float _z) { SetRotate(XMFLOAT4(_x, _y, _z, 0.0f)); }
	void SetRotateAxis(XMVECTOR _rotationAxis) { transform_.SetRotateAxis(_rotationAxis); }

	XMFLOAT3 GetScale() { return transform_.GetScale(); }
	void SetScale(const XMFLOAT3 _scale) { transform_.SetScale(_scale); }
	void SetScale(float _x, float _y, float _z) { SetScale(XMFLOAT3(_x, _y, _z)); }

	// オブジェクトを作成するテンプレート
	template <class T>
	GameObject* Instantiate(GameObject* _parent){
		T* newObject = new T(_parent);
		if (_parent != nullptr)_parent->PushBackChild(newObject);
		newObject->Initialize();
		return newObject;
	}
};

