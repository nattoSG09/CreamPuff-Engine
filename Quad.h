#pragma once
#include "Engine/Direct3D.h"
using namespace DirectX;

struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
};


class Quad
{
private:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

public:
	Quad();
	~Quad();

	void Initialize();
	void Draw();
	void Release();
};

