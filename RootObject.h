#pragma once
#include "Engine/GameObject.h"

class RootObject: public GameObject
{
	int hModel_;
public:
	RootObject(GameObject* _parent);
	~RootObject();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

