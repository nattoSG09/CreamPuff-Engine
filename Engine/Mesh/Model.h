#pragma once
#include "../Components/Transform.h"
#include "../Direct3D.h"
#include "Structs.h"

#include <string>
using std::string;

/// <summary>
/// ���f�����Ǘ�����N���X
/// </summary>
class Model
{
private:
	vector<ID3D11Buffer*> meshVertexBuffers_;///< ���b�V���̒��_�o�b�t�@�[
	vector<ID3D11Buffer*> meshIndexBuffers_;///< ���b�V���̃C���f�b�N�X�o�b�t�@�[
	vector<ID3D11Buffer*> meshConstantBuffers_;///< ���b�V���̒萔�o�b�t�@�[

	vector<Mesh> meshes_;///< ���[�h���ꂽ���b�V���̃��X�g
public:
	/// <summary>
	/// �w�肳�ꂽ�t�@�C���p�X���烂�f�������[�h���܂��B
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool Load(string _filePath);

	/// <summary>
	/// �w�肳�ꂽ�t�@�C���p�X���烂�f�������[�h���܂��B
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_inverseU">U���̔��]���s�����ǂ���</param>
	/// <param name="_inverseV">V���̔��]���s�����ǂ���</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool Load(string _filePath,bool _inverseU,bool _inverseV);

	/// <summary>
	/// ���f����`�悵�܂��B
	/// </summary>
	/// <param name="_transform">���f���̕ϊ����</param>
	void Draw(Transform _transform);
private:
	/// <summary>
	/// ���b�V���̒��_�����������܂��B
	/// </summary>
	/// <param name="_mesh">���������郁�b�V��</param>
	/// <returns>�������������������ǂ����������^�U�l</returns>
	bool InitVertex(const Mesh& _mesh);

	/// <summary>
	/// ���b�V���̃C���f�b�N�X�����������܂��B
	/// </summary>
	/// <param name="_mesh">���������郁�b�V��</param>
	/// <returns>�������������������ǂ����������^�U�l</returns>
	bool InitIndex(const Mesh& _mesh);

	/// <summary>
	/// ���b�V���̒萔�o�b�t�@�[�����������܂��B
	/// </summary>
	/// <returns>�������������������ǂ����������^�U�l</returns>
	bool InitConstantBuffer();
};

