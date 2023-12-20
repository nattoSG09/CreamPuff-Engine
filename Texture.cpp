#include "Texture.h"

#include <filesystem>
#include <locale>
#include <codecvt>
namespace fs = std::filesystem;

namespace {
	std::wstring StringToWString(const std::string& str) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str);
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

bool Texture::LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//拡張子を取得する
	fs::path filePath = _filePath;
	std::string ext = filePath.extension().string();

	if (ext == "png" || ext == "jpg") {
		LoadFromWICFile(StringToWString(_filePath).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage);
	}
	return false;

}
