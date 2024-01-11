#pragma once
#include "Engine/GameObject.h"

class TestScene2 : public GameObject
{
public:
	TestScene2(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

