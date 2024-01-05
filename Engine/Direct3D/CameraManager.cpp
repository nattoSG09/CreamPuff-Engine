#include "CameraManager.h"
#include "../Global.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::UpdateCurrentCamera()
{
	currentCamera_->Update();
}

Camera* CameraManager::GetCamera(const string& _key)
{
	if (cameras_.count(_key) > 0) return cameras_[_key];
	else return nullptr;
}

void CameraManager::AddCamera(Camera* _camera)
{
	cameras_[_camera->Name()] = _camera;
}

void CameraManager::AddDefaultCamera()
{
	if (currentCamera_ != nullptr)return;
	AddCamera(new Camera("default"));
	SetCurrentCamera("default");
}

void CameraManager::UpdateCameras()
{
	for (auto it = cameras_.begin(); it != cameras_.end(); ++it) {
		it->second->Update();
	}
}

void CameraManager::ReleaseCameras()
{
	for (auto& window : cameras_) delete window.second;
	cameras_.clear();
}

CameraManager& CameraManager::GetInstance()
{
	static CameraManager instance;
	return instance;
}
