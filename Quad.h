#pragma once
#include "Engine/Direct3D.h"
using namespace DirectX;

struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
};


class Quad
{
private:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

public:
	Quad();
	~Quad();

	void Initialize();
	void Draw();
	void Release();
};

