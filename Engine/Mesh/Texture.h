#pragma once
#include <string>
#include <DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

using std::string;
using namespace DirectX;

/// <summary>
/// �e�N�X�`�����Ǘ�����N���X
/// </summary>
class Texture
{
private:
	ID3D11SamplerState* pSampler_;///< �T���v���[�X�e�[�g
	ID3D11ShaderResourceView* pSRV_;///< �V�F�[�_�[���\�[�X�r���[
	string filePath_;///< �t�@�C���̃p�X
	XMFLOAT2 size_;	///< �t�@�C���̃T�C�Y
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Texture();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Texture();

	/// <summary>
	/// �w�肳�ꂽ�t�@�C���p�X����e�N�X�`�������[�h���܂��B
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool Load(string _filePath);

	/// <summary>
	/// �e�N�X�`���̃T���v���[�X�e�[�g���擾���܂��B
	/// </summary>
	/// <returns>�T���v���[�X�e�[�g</returns>
	ID3D11SamplerState* GetSampler() { return pSampler_; }

	/// <summary>
	/// �e�N�X�`���̃V�F�[�_�[���\�[�X�r���[���擾���܂��B
	/// </summary>
	/// <returns>�V�F�[�_�[���\�[�X�r���[</returns>
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }

	XMFLOAT2 GetSize() const { return size_; }
private:
	/// <summary>
	/// �t�@�C���p�X��ݒ肵�܂��B
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	void SetFilePath(string _filePath) { filePath_ = _filePath; }

	/// <summary>
	/// �e�N�X�`���̃��^�f�[�^����摜�T�C�Y���擾����
	/// </summary>
	/// <param name="_metaData">�e�N�X�`���̃��^�f�[�^</param>
	void SetImageSize(TexMetadata& _metaData);

	/// <summary>
	/// �摜�t�@�C�������[�h���܂��B
	/// </summary>
	/// <param name="_filePath">�t�@�C���̃p�X</param>
	/// <param name="_metaData">�e�N�X�`���̃��^�f�[�^</param>
	/// <param name="_scImage">�摜�f�[�^�̈ꎞ�I�ȃC���[�W</param>
	/// <returns>���[�h�������������ǂ����������^�U�l</returns>
	bool LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage);
	
	/// <summary>
	/// �T���v���[�X�e�[�g�̐ݒ�����������܂��B
	/// </summary>
	/// <param name="_samplerDesc">�T���v���[�X�e�[�g�̐ݒ�</param>
	void InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc);
	
	/// <summary>
	/// �T���v���[�X�e�[�g���쐬���܂��B
	/// </summary>
	/// <returns>�쐬�������������ǂ����������^�U�l</returns>
	bool CreateSampler();
	
	/// <summary>
	/// �V�F�[�_�[���\�[�X�r���[���쐬���܂��B
	/// </summary>
	/// <param name="_scImage">�摜�f�[�^�̈ꎞ�I�ȃC���[�W</param>
	/// <param name="_metaData">�e�N�X�`���̃��^�f�[�^</param>
	/// <returns>�쐬�������������ǂ����������^�U�l</returns>
	bool CreateSRV(ScratchImage& _scImage, TexMetadata& _metaData);
};

