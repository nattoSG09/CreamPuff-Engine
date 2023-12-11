#include "Transform.h"

Transform::Transform()
{
	//•Ï”‚Ì‰Šú‰»
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);

	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}

void Transform::Calclation()
{

}

XMMATRIX Transform::WoaldMatrix()
{
	return XMMATRIX();
}

XMMATRIX Transform::NormalMatrix()
{
	return XMMATRIX();
}
