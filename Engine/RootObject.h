#pragma once
#include "GameObject.h"

class RootObject: public GameObject
{
public:
	RootObject(GameObject* _parent);
	~RootObject();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

