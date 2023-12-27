#include "Texture.h"

#include "../Direct3D.h"
#include <filesystem>
#include <unordered_set>
namespace fs = std::filesystem;

/// <summary>
/// �t�@�C���╶����̕ϊ��A�t�@�C���g���q�̔���ȂǁA�v���C�x�[�g�ȃ��[�e�B���e�B�֐��Q���܂܂�閳�����O��Ԃł��B
/// </summary>
namespace {
	/// <summary>
	/// UTF-8�`���̕���������C�h������ɕϊ����܂��B
	/// </summary>
	/// <param name="utf8Str">UTF-8�`���̕�����</param>
	/// <returns>�ϊ����ꂽ���C�h������</returns>
	std::wstring StringToWString(const string& utf8Str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), nullptr, 0);
		std::wstring wideString(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), &wideString[0], size_needed);
		return wideString;
	}

	/// <summary>
	/// �w�肳�ꂽ�g���q�ɉ�����WIC�œǂݍ��ނ��ǂ����𔻒肵�܂��B
	/// </summary>
	/// <param name="_ext">�t�@�C���̊g���q</param>
	/// <returns>WIC�œǂݍ��ނׂ����ǂ����������^�U�l</returns>
	bool ShouldLoadWithWIC(string _ext){
		std::unordered_set<std::string> supportedExtensions = {
			".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff"
		};

		return supportedExtensions.find(_ext) != supportedExtensions.end();
	}

	/// <summary>
	/// �w�肳�ꂽ�g���q�ɉ�����TGA�œǂݍ��ނ��ǂ����𔻒肵�܂��B
	/// </summary>
	/// <param name="_ext">�t�@�C���̊g���q</param>
	/// <returns>TGA�œǂݍ��ނׂ����ǂ����������^�U�l</returns>
	bool ShouldLoadWithTGA(string _ext) {
		std::unordered_set<std::string> supportedExtensions = {
			".tga", ".TGA", ".tpic",".psd"
		};
		return supportedExtensions.find(_ext) != supportedExtensions.end();
	}

	/// <summary>
	/// �t�@�C���p�X�̊g���q���w�肳�ꂽ�V�����g���q�ɕύX���܂��B
	/// </summary>
	/// <param name="filePath">�ύX����t�@�C���p�X</param>
	/// <param name="newExtension">�V�����g���q</param>
	/// <returns>�g���q��ύX�����t�@�C���p�X</returns>
	string ChangeExtension(const string& filePath, const string& newExtension) {
		size_t dotPos = filePath.find_last_of('.');
		return (dotPos != std::string::npos) ? (filePath.substr(0, dotPos + 1) + newExtension) : (filePath + "." + newExtension);
	}
}

Texture::Texture()
	:pSRV_(nullptr),pSampler_(nullptr),filePath_("")
{
}

Texture::~Texture()
{
}

bool Texture::Load(string _filePath)
{
	//�t�@�C���p�X��ݒ肷��
	SetFilePath(_filePath);
	TexMetadata metaData;
	ScratchImage scImage;

	//�摜�t�@�C����ǂݍ���
	if (LoadImageFile(_filePath, metaData, scImage) == false)return false;
	SetImageSize(metaData);

	// �T���v���[���쐬
	if (CreateSampler() == false)return false;

	//�V�F�[�_�[���\�[�X�r���[�̍쐬
	if (CreateSRV(scImage, metaData) == false) return false;

	return true;
}

void Texture::SetImageSize(TexMetadata& _metaData)
{
	size_ = XMFLOAT2(_metaData.width, _metaData.height);
}

bool Texture::LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//�g���q���擾����
	fs::path filePath = _filePath;
	string ext = filePath.extension().string();

	if (ShouldLoadWithWIC(ext)) {
		if (FAILED(LoadFromWICFile(StringToWString(_filePath).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage))) {
#ifdef _DEBUG
			string ret = "�摜�t�@�C��(" + ext + ")�̓ǂݍ��ݎ��s���܂���";
			MessageBox(NULL, ret.c_str(), "�G���[", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if (ShouldLoadWithTGA(ext)) {
		if (ext == ".psd") _filePath = ChangeExtension(_filePath, "tga");

		if (FAILED(LoadFromTGAFile(StringToWString(_filePath).c_str(), &_metaData, _scImage))) {
#ifdef _DEBUG
			string ret = "�摜�t�@�C��(" + ext + ")�̓ǂݍ��ݎ��s���܂���";
			MessageBox(NULL, ret.c_str(), "�G���[", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else {
#ifdef _DEBUG
		MessageBox(NULL, "�`���Ή��s�̉摜�t�@�C����ǂݍ������Ƃ��܂���", "�G���[", MB_OK);
#endif // _DEBUG
		return false;
	}

	return true;
}

void Texture::InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc)
{
	ZeroMemory(&_samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	_samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	_samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	_samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	_samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
}

bool Texture::CreateSampler()
{
	//�e�N�X�`���T���v���[�̐ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	InitSamplerDesc(samplerDesc);

	// �T���v���[���쐬
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(d3D.Device()->CreateSamplerState(&samplerDesc, &pSampler_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�T���v���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}

bool Texture::CreateSRV(ScratchImage& _scImage, TexMetadata& _metaData)
{
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(CreateShaderResourceView(d3D.Device(), _scImage.GetImages(),_scImage.GetImageCount(), _metaData, &pSRV_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}
