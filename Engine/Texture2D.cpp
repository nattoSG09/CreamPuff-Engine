#include "Texture2D.h"

#include <locale>
#include <codecvt>

#include "Direct3D.h"


namespace {
	string GetExtension(const string& _fileName) {

		//�u.(�h�b�g)�������������ڂ��𒊏o�v
		auto idx = _fileName.rfind('.');

		//sample.fbx = f�̕������疖���ɂ����Ắu�R�����vsample.fbx(10����) - idx(6) - 1 ���擾
		return _fileName.substr(idx + 1, _fileName.length() - idx - 1);
	}

	std::wstring StringToWString(const std::string& str) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str);
	}
}

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}

bool Texture2D::Load(string _fileName)
{
	TexMetadata metaData;
	ScratchImage scImage;
	fileName_ = _fileName;

	// �摜�t�@�C����ǂݍ���
	if (LoadImageFile(_fileName, metaData, scImage) == false)return false;

	// �T���v���[���쐬
	if (CreateSampler() == false)return false;

	//�V�F�[�_�[���\�[�X�r���[�̍쐬
	if (CreateSRV(scImage, metaData) == false) return false;

	return true;
}

bool Texture2D::LoadImageFile(string _fileName, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//�g���q�𕶎���Ƃ��Ď擾
	string ext = GetExtension(_fileName);

	if (ext == "png") {
		if (FAILED(LoadFromWICFile(StringToWString(_fileName).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage))) {
#ifdef _DEBUG
			MessageBox(NULL, "�摜�t�@�C��(.png)�̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if(ext == "tga") {
		HRESULT hr;
		if (FAILED(hr = LoadFromTGAFile(StringToWString(_fileName).c_str(), &_metaData, _scImage))) {
#ifdef _DEBUG
			MessageBox(NULL, "�摜(.tga)�t�@�C���̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
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

bool Texture2D::CreateSampler()
{
	// �e�N�X�`���T���v���[��ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	InitSamplerDesc(samplerDesc);

	// �T���v���[���쐬
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(d3D.Device()->CreateSamplerState(&samplerDesc, &pSampler_))) {
#ifdef _DEBUG
		MessageBox(NULL,"�T���v���[�̍쐬�Ɏ��s���܂���","�G���[",MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}

void Texture2D::InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc)
{
	ZeroMemory(&_samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	_samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	_samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	_samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	_samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
}

bool Texture2D::CreateSRV(ScratchImage& _scImage, TexMetadata& _metaData)
{
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(CreateShaderResourceView(d3D.Device(), _scImage.GetImages(), _scImage.GetImageCount(), _metaData, &pSRV_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}
