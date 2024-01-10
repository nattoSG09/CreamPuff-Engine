#pragma once
#include "Engine/GameObject.h"
class SuperObject : public GameObject
{
	Transform transform_;
	int hModel_;
public:
	SuperObject(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

