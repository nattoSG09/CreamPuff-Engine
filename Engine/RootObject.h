#pragma once
#include "GameObject.h"

class RootObject: public GameObject
{
	Transform transform_;
public:
	RootObject(GameObject* _parent);
	~RootObject();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

