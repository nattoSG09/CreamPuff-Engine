#pragma once
#include "../Components/Transform.h"
#include "../Direct3D.h"
#include "Texture.h"
#include <string>
using std::string;

class Sprite
{
private:
	struct Vertex{
		XMFLOAT3 position;
		XMFLOAT2 uv;
	};

	struct Constant_Buffer
	{
		XMMATRIX	matW;		// ���_���W�ϊ��s��
		XMMATRIX	normal;	// �e�N�X�`�����W�ϊ��s��
		XMFLOAT4	color;		// �e�N�X�`���Ƃ̍����F
	};

	Texture* pTexture_;
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
public:
	Sprite();
	~Sprite();

	bool Load(string _filePath);
	void Draw(Transform& _transform, RECT _rect, float alpha);
	XMFLOAT2 GetTextureSize();
private:
	bool InitVertex();
	bool InitIndex();
	bool InitConstantBuffer();
};

