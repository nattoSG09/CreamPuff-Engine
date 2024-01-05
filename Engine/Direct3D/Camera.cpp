#include "Camera.h"
#include "../Windows/WindowManager.h"

namespace {
	const XMVECTOR DEFAULT_POSITION = XMVectorSet(0, 3, 7, 0);
	const XMVECTOR DEFAULT_TARGET = XMVectorSet(0, 0, 0, 0);
	const XMVECTOR DEFAULT_UP_DIRECTION = XMVectorSet(0, 1, 0, 0);
}

Camera::Camera(string _name)
	:name_(_name),position_(DEFAULT_POSITION),target_(DEFAULT_TARGET)
{
	CreateProjectionMatrix();
}

Camera::Camera(string _name, XMVECTOR _position, XMVECTOR _target)
	:name_(_name), position_(_position), target_(_target)
{
	CreateProjectionMatrix();
}

Camera::Camera(string _name, XMFLOAT3 _position, XMFLOAT3 _target)
	:name_(_name), position_(XMLoadFloat3(&_position)), target_(XMLoadFloat3(&_target))
{
	CreateProjectionMatrix();
}

Camera::Camera(string _name, float _pX, float _pY, float _pZ, float _tX, float _tY, float _tZ)
	:name_(_name), position_(XMVectorSet(_pX,_pY,_pZ,0)), target_(XMVectorSet(_tX,_tY,_tZ,0))
{
	CreateProjectionMatrix();
}

void Camera::Update()
{
	CreateViewMatrix();
}

void Camera::CreateViewMatrix()
{
	matView_ = XMMatrixLookAtLH(position_,target_, DEFAULT_UP_DIRECTION);
}

void Camera::CreateProjectionMatrix()
{
	float FovAngleY = XM_PIDIV4;  // Y軸に対する視野角（ラジアン単位）
	WindowManager& wm = WindowManager::GetInstance();
	float AspectRatio = (float)wm.GetWindow("Editor")->Width() / (float)wm.GetWindow("Editor")->Height(); // アスペクト比（画面の幅 / 画面の高さ）
	float NearZ = 0.1f;      // 近いビューフラスト面までの距離
	float FarZ = 1000.0f;         // 遠いビューフラスト面までの距離

	matProjection_ = XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ); // メッシュごとの射影行列
}
