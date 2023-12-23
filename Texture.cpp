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

	//画像ファイルを読み込む
	if (LoadImageFile(_filePath, metaData, scImage) == false)return false;

	return true;
}

bool Texture::LoadFromWICFile(string _ext)
{
	return _ext == "png";
}

bool Texture::LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//拡張子を取得する
	fs::path filePath = _filePath;
	std::string ext = filePath.extension().string();
	HRESULT hr{};
	if (ext == "png") {
		hr = LoadFromWICFile(StringToWString(_filePath).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage);
		if (FAILED(hr)) {
#ifdef _DEBUG
			MessageBox(NULL, "画像ファイル(.png)の読み込み失敗しました", "エラー", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if (ext == "tga") {

		if (FAILED(LoadFromTGAFile(StringToWString(_filePath).c_str(), &_metaData, _scImage))) {
#ifdef _DEBUG
			MessageBox(NULL, "画像(.tga)ファイルの読み込み失敗しました", "エラー", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else {
#ifdef _DEBUG
		MessageBox(NULL, "形式対応不可の画像ファイルを読み込もうとしました", "エラー", MB_OK);
#endif // _DEBUG
		return false;
	}

	return true;
}
