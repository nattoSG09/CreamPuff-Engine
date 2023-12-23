#include "Texture.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace {
	std::wstring StringToWString(const std::string& utf8Str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), nullptr, 0);
		std::wstring wideString(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), &wideString[0], size_needed);
		return wideString;
	}
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Load(string _filePath)
{
	SetFilePath(_filePath);
	TexMetadata metaData;
	ScratchImage scImage;

	//�摜�t�@�C����ǂݍ���
	if (LoadImageFile(_filePath, metaData, scImage) == false)return false;

	return true;
}

bool Texture::LoadFromWICFile(string _ext)
{
	return _ext == "png";
}

bool Texture::LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//�g���q���擾����
	fs::path filePath = _filePath;
	std::string ext = filePath.extension().string();
	HRESULT hr{};
	if (ext == "png") {
		hr = LoadFromWICFile(StringToWString(_filePath).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage);
		if (FAILED(hr)) {
#ifdef _DEBUG
			MessageBox(NULL, "�摜�t�@�C��(.png)�̓ǂݍ��ݎ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if (ext == "tga") {

		if (FAILED(LoadFromTGAFile(StringToWString(_filePath).c_str(), &_metaData, _scImage))) {
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
