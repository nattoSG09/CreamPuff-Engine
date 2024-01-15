#pragma once
#include "Engine/GameObject.h"
class Alisia : public GameObject
{
	int hModel_;
public:
	Alisia(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

