#include "Transform.h"

Transform::Transform()
{
	//変数の初期化
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT4(0, 0, 0, 0);
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
	matRotate_	= XMMatrixRotationX(rotate_.x)
				* XMMatrixRotationY(rotate_.y)
				* XMMatrixRotationZ(rotate_.z)
				* XMMatrixRotationAxis(rotationAxis_, rotate_.w);

	// scale_.xyzの値をもとに_拡大縮小行列_を作成
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::WoaldMatrix()
{
	Calclation();
	if (pParent_) 
		//親がいる場合は、親の変形行列も合わせる
		return matScale_ * matRotate_ * matTranslate_ * pParent_->WoaldMatrix();
	else 
		//いない場合は、そのままの変形行列
		return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::NormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
