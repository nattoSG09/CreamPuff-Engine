#include "Texture.h"

#include <filesystem>
namespace fs = std::filesystem;
#include <unordered_set>
#include "Engine/Direct3D.h"

namespace {
	std::wstring StringToWString(const std::string& utf8Str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), nullptr, 0);
		std::wstring wideString(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), &wideString[0], size_needed);
		return wideString;
	}

	bool ShouldLoadWithWIC(string _ext){
		std::unordered_set<std::string> supportedExtensions = {
			".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff"
		};

		return supportedExtensions.find(_ext) != supportedExtensions.end();
	}

	bool ShouldLoadWithTGA(string _ext) {
		std::unordered_set<std::string> supportedExtensions = {
			".tga", ".TGA", ".tpic",
		};
		return supportedExtensions.find(_ext) != supportedExtensions.end();
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
	filePath_ = _filePath;
	TexMetadata metaData;
	ScratchImage scImage;

	//画像ファイルを読み込む
	if (LoadImageFile(_filePath, metaData, scImage) == false)return false;

	// サンプラーを作成
	if (CreateSampler() == false)return false;

	//シェーダーリソースビューの作成
	if (CreateSRV(scImage, metaData) == false) return false;

	return true;
}

bool Texture::LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//拡張子を取得する
	fs::path filePath = _filePath;
	string ext = filePath.extension().string();
	if (ShouldLoadWithWIC(ext)) {
		if (FAILED(LoadFromWICFile(StringToWString(_filePath).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage))) {
#ifdef _DEBUG
			string ret = "画像ファイル(" + ext + ")の読み込み失敗しました";
			MessageBox(NULL, ret.c_str(), "エラー", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if (ShouldLoadWithTGA(ext)) {
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
	//テクスチャサンプラーの設定
	D3D11_SAMPLER_DESC samplerDesc;
	InitSamplerDesc(samplerDesc);

	// サンプラーを作成
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(d3D.Device()->CreateSamplerState(&samplerDesc, &pSampler_))) {
#ifdef _DEBUG
		MessageBox(NULL, "サンプラーの作成に失敗しました", "エラー", MB_OK);
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
		MessageBox(NULL, "シェーダーリソースビューの作成に失敗しました", "エラー", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}
