#include "Transform.h"

Transform::Transform()
{
	//�ϐ��̏�����
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);

	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();

	rotationAxis_ = XMVectorSet(0, 0, 0, 0);
}

void Transform::Calclation()
{
	// position_.xyz�̒l�����Ƃ�_���s�ړ��s��(�ړ��ʂ͂O)_���쐬
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// rotate_.xyz�̒l�����Ƃ�_��]�s��_���쐬
	


	// scale_.xyz�̒l�����Ƃ�_�g��k���s��_���쐬
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::WoaldMatrix()
{
	return XMMATRIX();
}

XMMATRIX Transform::NormalMatrix()
{
	return XMMATRIX();
}
