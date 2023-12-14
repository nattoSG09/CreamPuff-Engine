#pragma once
#include "Component.h"

#include <DirectXMath.h>
using namespace DirectX;

class Transform : public Component
{
public:
	XMFLOAT3 position_;		/*位置*/
	XMFLOAT4 rotate_;		/*方向*/
	XMFLOAT3 scale_;		/*拡大率*/

private:
	XMMATRIX matTranslate_;	/*移動行列*/
	XMMATRIX matRotate_;	/*回転行列*/
	XMMATRIX matScale_;		/*拡大行列*/

	XMVECTOR rotationAxis_;

	Transform* pParent_;	/*親オブジェクトの変換行列*/
public:
	Transform();
	void Calclation();

// アクセス関数 //
	XMFLOAT3 GetPosition() { return position_; }
	void SetPosition(const XMFLOAT3 _position) { position_ = _position; }
	void SetPosition(float _x, float _y, float _z) { SetPosition(XMFLOAT3(_x, _y, _z)); }

	XMFLOAT4 GetRotate() { return rotate_; }
	void SetRotate(const XMFLOAT4 _rotate) { rotate_ = _rotate; }
	void SetRotate(float _x, float _y, float _z) { SetRotate(XMFLOAT4(_x, _y, _z,0.0f)); }
	void SetRotateAxis(XMVECTOR _rotationAxis) { rotationAxis_ = _rotationAxis; }
	

	XMFLOAT3 GetScale() { return scale_; }
	void SetScale(const XMFLOAT3 _scale) { scale_ = _scale; }
	void SetScale(float _x, float _y, float _z) { SetScale(XMFLOAT3(_x, _y, _z)); }

	XMMATRIX WoaldMatrix();
	XMMATRIX NormalMatrix();
};

