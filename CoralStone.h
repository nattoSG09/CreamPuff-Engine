#pragma once
#include "Engine/GameObject.h"
class CoralStone : public GameObject
{
	int hModel_;
public:
	CoralStone(GameObject* _parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

