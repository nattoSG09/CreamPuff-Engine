#pragma once
#include <string>
#include <list>

using std::string;
using std::list;

class GameObject
{
protected:
	string name_;					// ���O
	GameObject* parent_;			// �e�I�u�W�F�N�g
	list<GameObject*> children_;	// �q�I�u�W�F�N�g�̔z��

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

	// �I�u�W�F�N�g���쐬����e���v���[�g
	template <class T>
	GameObject* Instantiate(GameObject* _parent){
		T* newObject = new T(_parent);
		if (_parent != nullptr)_parent->PushBackChild(newObject);
		newObject->Initialize();
		return newObject;
	}
};

