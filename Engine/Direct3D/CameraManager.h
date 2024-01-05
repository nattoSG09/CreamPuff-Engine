#pragma once
#include "Camera.h"
#include <map>
using std::map;

class CameraManager
{
private:
	map<string, Camera*> cameras_;
	Camera* currentCamera_;

	CameraManager();
	~CameraManager();

public:
	static CameraManager& GetInstance();
	void AddCamera(Camera* _camera);
	bool HasCamera() { return cameras_.empty() == false; }
	void AddDefaultCamera();
	void UpdateCameras();
	void ReleaseCameras();

	Camera* GetCurrentCamera() { return currentCamera_; }
	void SetCurrentCamera(string _key) { currentCamera_ = GetCamera(_key); }
	void UpdateCurrentCamera();

	Camera* GetCamera(const string& _key);
	map<string, Camera*>& GetCameras() { return cameras_; }

};

