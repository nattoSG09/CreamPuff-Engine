#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Texture.h"

using namespace DirectX;
using std::vector;
using std::string;

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
struct Material{
	vector<Texture*> textures;	//�e�N�X�`�����
};

/// <summary>
/// ���b�V�����-�\����
/// </summary>
struct Mesh{
	vector<Vertex> vertices;	//���_���̔z��
	vector<uint32_t> indices;	//�C���f�b�N�X���̔z��
	vector<Material> materials;
};