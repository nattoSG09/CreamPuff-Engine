#pragma once
#include <string>
#include <DirectXMath.h>
using std::string;
using namespace DirectX;

class Camera
{
private:
	string name_;
	XMVECTOR position_;
	XMVECTOR target_;
	XMVECTOR upDirection_;

	XMMATRIX matView_;
	XMMATRIX matProjection_;
public:
	Camera(string _name);
	Camera(string _name, XMVECTOR _position, XMVECTOR _target);
	Camera(string _name, XMFLOAT3 _position, XMFLOAT3 _target);
	Camera(string _name,float _pX,float _pY,float _pZ,float _tX,float _tY,float _tZ);
	void Update();
	
// アクセス関数 //
	string Name() { return name_; }
	XMVECTOR Position() const { return position_; }
	XMVECTOR Target() const { return target_; }

	void SetPosition(XMVECTOR _position) { position_ = _position; }
	void SetPosition(XMFLOAT3 _position) { SetPosition(XMLoadFloat3(&_position)); }
	void SetPosition(float _x, float _y, float _z) { SetPosition(XMFLOAT3(_x,_y,_z)); }

	void SetTarget(XMVECTOR _target) { target_ = _target; }
	void SetTarget(XMFLOAT3 _target) { SetTarget(XMLoadFloat3(&_target)); }
	void SetTarget(float _x, float _y, float _z) { SetTarget(XMFLOAT3(_x, _y, _z)); }

	XMMATRIX GetViewMatrix() const { return matView_; }
	XMMATRIX GetProjectionMatrix() const { return matProjection_; }
private:
	void CreateViewMatrix();
	void CreateProjectionMatrix();
};

