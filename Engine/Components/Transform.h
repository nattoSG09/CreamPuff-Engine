#pragma once
#include "Component.h"


#include <DirectXMath.h>
using namespace DirectX;

class GameObject;

/// <summary>
/// Transform(�ϊ��s��)�R���|�[�l���g
/// </summary>
class Transform : public Component
{
public:
	XMFLOAT3 position_;		/*�ʒu*/
	XMFLOAT4 rotate_;		/*����*/
	XMFLOAT3 scale_;		/*�g�嗦*/

	Transform* pParent_;	/*�e�I�u�W�F�N�g�̕ϊ��s��*/

private:
	XMMATRIX matTranslate_;	/*�ړ��s��*/
	XMMATRIX matRotate_;	/*��]�s��*/
	XMMATRIX matScale_;		/*�g��s��*/

	XMVECTOR rotationAxis_;	/*�C�ӂ̉�]�ɕK�v�Ȏ�*/

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Transform(GameObject* _parent);

	Transform();

	/// <summary>
	/// ���������ϊ��s����v�Z
	/// </summary>
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

	/// <summary>
	/// ���[���h�s��𐶐��E�擾���s��
	/// </summary>
	/// <returns>���[���h�s��</returns>
	XMMATRIX WoaldMatrix();

	/// <summary>
	/// �@���s��𐶐��E�擾���s��
	/// </summary>
	/// <returns>�@���s��</returns>
	XMMATRIX NormalMatrix();
};

