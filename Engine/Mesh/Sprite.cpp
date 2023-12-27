#include "Sprite.h"

using std::vector;

Sprite::Sprite()
	:pTexture_(nullptr)
{
}

Sprite::~Sprite()
{
}

bool Sprite::Load(string _filePath)
{
	// �e�N�X�`�������[�h����
	pTexture_ = new Texture;
	if (pTexture_->Load(_filePath) == false)return false;
	
	// ���_����������
	if (InitVertex() == false)return false;

	// �C���f�b�N�X����������
	if (InitIndex() == false)return false;

	// �R���X�^���g�o�b�t�@��������
	if (InitConstantBuffer() == false)return false;

	return true;
}

void Sprite::Draw(Transform& _transform, RECT _rect, float alpha)
{

}

XMFLOAT2 Sprite::GetTextureSize()
{
	return pTexture_->GetSize();
}

bool Sprite::InitVertex()
{
	//���_���
	vector<Vertex> vertices{
		{ XMFLOAT3(-1.0f,1.0f, 0.0f),	XMFLOAT2(0.0f, 0.0f) },   // �l�p�`�̒��_�i����j
		{ XMFLOAT3(1.0f,1.0f, 0.0f),	XMFLOAT2(1.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j
		{ XMFLOAT3(-1.0f,-1.0f, 0.0f),	XMFLOAT2(0.0f, 1.0f) },   // �l�p�`�̒��_�i�����j
		{ XMFLOAT3(1.0f, -1.0f, 0.0f),	XMFLOAT2(1.0f, 1.0f) },   // �l�p�`�̒��_�i�E���j
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(Vertex)*vertices.size();
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices.data();
	Direct3D& d3d = Direct3D::GetInstance();
	if (FAILED(d3d.Device()->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_))) {
#ifdef _DEBUG
		MessageBox(NULL,"���_�o�b�t�@�̐����Ɏ��s���܂���","���s",MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}

bool Sprite::InitIndex()
{
	//�C���f�b�N�X���
	vector<int> index{ 
		2,1,0, 2,3,1 
	};

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int)*index.size();
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	Direct3D& d3d = Direct3D::GetInstance();
	if (FAILED(d3d.Device()->CreateBuffer(&bd, &InitData, &pIndexBuffer_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "���s", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}

bool Sprite::InitConstantBuffer()
{
	//�K�v�Ȑݒ荀��
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(Constant_Buffer);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	Direct3D& d3d = Direct3D::GetInstance();
	if (FAILED(d3d.Device()->CreateBuffer(&cb, NULL, &pConstantBuffer_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���", "���s", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}
