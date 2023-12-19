#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;
using std::vector;

/// <summary>
/// ���_���-�\����
/// </summary>
struct Vertex {
	XMFLOAT3 position;	//�ʒu���W
	XMFLOAT3 normal;	//�@��
	XMFLOAT2 uv;		//uv���W
	XMFLOAT3 tangent;	//�ڋ��
	XMFLOAT4 color;		//���_�F
};

/// <summary>
/// �}�e���A�����-�\����
/// </summary>
struct Material {
	// vector<Texture*> diffuseTextures;	//�f�B�q���[�Y�e�N�X�`�����
	XMFLOAT4 diffuse;					//�f�B�q���[�Y�J���[���
};

/// <summary>
/// ���b�V�����-�\����
/// </summary>
struct Mesh {
	vector<Vertex> vertices;	//���_���̔z��
	vector<uint32_t> indices;	//�C���f�b�N�X���̔z��
	Material material;
};

struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
	XMFLOAT4	diffuseColor;
};
