#pragma once
#include "global.h"
#include "GameObject.h"

enum SCENE_ID
{
	SCENE_ID_TEST,
	SCENE_ID_TEST2,
};

class SceneManager : public GameObject
{
private:
	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン

public:
	SceneManager(GameObject* _parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void ChangeScene(SCENE_ID _next);

};