#pragma once
#include "Texture.h"
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
	bool hasTexture;
	vector<Texture*> diffuseTextures;	//�f�B�q���[�Y�e�N�X�`�����
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

/// <summary>
/// �R���X�^���g�o�b�t�@-�\����
/// </summary>
struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;			//���[���h�E�r���[�E�v���W�F�N�V�����s��
	XMMATRIX	matNormal;		//�@���s��
	XMFLOAT4	diffuseColor;	//�f�B�q���[�Y�J���[
	bool hasTexture;			//�e�N�X�`���̗L��
};
