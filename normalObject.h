#pragma once
#include  "Engine/GameObject.h"

class NormalObject : public GameObject
{
	int hModel_;
public:
	NormalObject(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

