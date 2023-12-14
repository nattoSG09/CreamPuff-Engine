#pragma once
#include "Component.h"

#include <DirectXMath.h>
using namespace DirectX;

class Transform : public Component
{
public:
	XMFLOAT3 position_;		/*�ʒu*/
	XMFLOAT4 rotate_;		/*����*/
	XMFLOAT3 scale_;		/*�g�嗦*/

private:
	XMMATRIX matTranslate_;	/*�ړ��s��*/
	XMMATRIX matRotate_;	/*��]�s��*/
	XMMATRIX matScale_;		/*�g��s��*/

	XMVECTOR rotationAxis_;

	Transform* pParent_;	/*�e�I�u�W�F�N�g�̕ϊ��s��*/
public:
	Transform();
	void Calclation();

// �A�N�Z�X�֐� //
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

