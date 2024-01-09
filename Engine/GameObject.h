#pragma once
#include <string>
#include <list>

using std::string;
using std::list;

class GameObject
{
protected:
	string name_;					// 名前
	GameObject* parent_;			// 親オブジェクト
	list<GameObject*> children_;	// 子オブジェクトの配列

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

	// オブジェクトを作成するテンプレート
	template <class T>
	GameObject* Instantiate(GameObject* _parent){
		T* newObject = new T(_parent);
		if (_parent != nullptr)_parent->PushBackChild(newObject);
		newObject->Initialize();
		return newObject;
	}
};

