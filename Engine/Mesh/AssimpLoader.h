#pragma once
#include "Structs.h"
#include <string>

using std::string;
struct aiMesh;
struct aiMaterial;

/// <summary>
/// Assimp���g�p���ă��f����ǂݍ��ނ��߂̃N���X�ł��B
/// </summary>
class AssimpLoader
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AssimpLoader();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AssimpLoader();

	/// <summary>
	/// �w�肳�ꂽ�t�@�C���p�X���烁�b�V�������[�h����
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_meshes">���[�h���ꂽ���b�V�����i�[����x�N�^�[</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool Load(string _filePath, vector<Mesh>& _meshes);

	/// <summary>
	/// �w�肳�ꂽ�t�@�C���p�X���烁�b�V�������[�h����
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_meshes">���[�h���ꂽ���b�V�����i�[����x�N�^�[</param>
	/// <param name="_inverseU">U���̔��]���s�����ǂ���</param>
	/// <param name="_inverseV">V���̔��]���s�����ǂ���</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool Load(string _filePath,vector<Mesh>& _meshes,bool _inverseU,bool _inverseV);
private:
	/// <summary>
    /// Assimp�̃t���O�����������܂�
    /// </summary>
    /// <param name="_flags">����������t���O</param>
	void InitFlags(int& _flags);

	/// <summary>
	/// Assimp�̃��b�V�������[�h����
	/// </summary>
	/// <param name="_dst">���[�h���Mesh�I�u�W�F�N�g</param>
	/// <param name="_src">���ƂȂ�Assimp�̃��b�V��</param>
	/// <param name="_inverseU">U���̔��]���s�����ǂ���</param>
	/// <param name="_inverseV">V���̔��]���s�����ǂ���</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV);

	/// <summary>
	/// Assimp�̃}�e���A�������[�h����
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_dst">���[�h���Material�I�u�W�F�N�g</param>
	/// <param name="_src">���ƂȂ�Assimp�̃}�e���A��</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool LoadMaterial(string _filePath, Material& _dst, const aiMaterial* _src);

	/// <summary>
	/// �e�N�X�`�������[�h����Material�ɓK�p����
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_dst">���[�h���Material�I�u�W�F�N�g</param>
	/// <param name="_src">���ƂȂ�Assimp�̃}�e���A��</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool LoadTexture(string _filePath,Material& _dst, const aiMaterial* _src);
};

