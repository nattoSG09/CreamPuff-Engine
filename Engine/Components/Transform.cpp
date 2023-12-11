#include "Transform.h"

Transform::Transform()
{
	//変数の初期化
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
	// position_.xyzの値をもとに_平行移動行列(移動量は０)_を作成
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// rotate_.xyzの値をもとに_回転行列_を作成
	


	// scale_.xyzの値をもとに_拡大縮小行列_を作成
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
