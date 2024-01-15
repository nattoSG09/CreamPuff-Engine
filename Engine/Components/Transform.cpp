#include "Transform.h"
#include "../GameObject.h"

Transform::Transform(GameObject* _parent)
	:pParent_(nullptr)
{

	//�ϐ��̏�����
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT4(0, 0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);

	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();

	rotationAxis_ = XMVectorSet(1, 0, 0, 0);
}

Transform::Transform()
	:pParent_(nullptr)
{
	//�ϐ��̏�����
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT4(0, 0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);

	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();

	rotationAxis_ = XMVectorSet(1, 0, 0, 0);
}

void Transform::Calclation()
{
	// position_.xyz�̒l�����Ƃ�_���s�ړ��s��(�ړ��ʂ͂O)_���쐬
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// rotate_.xyz�̒l�����Ƃ�_��]�s��_���쐬
	matRotate_	= XMMatrixRotationX(XMConvertToRadians(rotate_.x))
				* XMMatrixRotationY(XMConvertToRadians( rotate_.y))
				* XMMatrixRotationZ(XMConvertToRadians(rotate_.z))
				* XMMatrixRotationAxis(rotationAxis_, XMConvertToRadians(rotate_.w));

	// scale_.xyz�̒l�����Ƃ�_�g��k���s��_���쐬
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::WoaldMatrix()
{
	Calclation();
	if (pParent_) 
		//�e������ꍇ�́A�e�̕ό`�s������킹��
		return matScale_ * matRotate_ * matTranslate_ * pParent_->WoaldMatrix();
	else 
		//���Ȃ��ꍇ�́A���̂܂܂̕ό`�s��
		return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::NormalMatrix()
{
	// ���f���̊g��k���s����l�������t�s����v�Z
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
