#pragma once
#include "Engine/GameObject.h"

class TestScene : public GameObject
{
public:
	TestScene(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

