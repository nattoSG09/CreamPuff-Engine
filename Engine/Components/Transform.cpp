#include "Transform.h"
#include "../GameObject.h"

Transform::Transform(GameObject* _parent)
	:pParent_(nullptr)
{

	//変数の初期化
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
	//変数の初期化
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
	// position_.xyzの値をもとに_平行移動行列(移動量は０)_を作成
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// rotate_.xyzの値をもとに_回転行列_を作成
	matRotate_	= XMMatrixRotationX(XMConvertToRadians(rotate_.x))
				* XMMatrixRotationY(XMConvertToRadians( rotate_.y))
				* XMMatrixRotationZ(XMConvertToRadians(rotate_.z))
				* XMMatrixRotationAxis(rotationAxis_, XMConvertToRadians(rotate_.w));

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
	// モデルの拡大縮小行列を考慮した逆行列を計算
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
