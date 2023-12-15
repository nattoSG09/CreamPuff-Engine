#pragma once
#include <string>
#include <DirectXMath.h>
using std::string;
using namespace DirectX;

class Camera
{
private:
	string name_;
	XMFLOAT3 position_;
	XMFLOAT3 target_;

public:
	Camera(string _name, XMFLOAT3 _position, XMFLOAT3 _target);
	Camera(string _name);

};

