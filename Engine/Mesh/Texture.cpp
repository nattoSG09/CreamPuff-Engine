#include "Texture.h"

#include "../Direct3D.h"
#include <filesystem>
#include <unordered_set>
namespace fs = std::filesystem;

/// <summary>
/// ファイルや文字列の変換、ファイル拡張子の判定など、プライベートなユーティリティ関数群が含まれる無名名前空間です。
/// </summary>
namespace {
	/// <summary>
	/// UTF-8形式の文字列をワイド文字列に変換します。
	/// </summary>
	/// <param name="utf8Str">UTF-8形式の文字列</param>
	/// <returns>変換されたワイド文字列</returns>
	std::wstring StringToWString(const string& utf8Str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), nullptr, 0);
		std::wstring wideString(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), &wideString[0], size_needed);
		return wideString;
	}

	/// <summary>
	/// 指定された拡張子に応じてWICで読み込むかどうかを判定します。
	/// </summary>
	/// <param name="_ext">ファイルの拡張子</param>
	/// <returns>WICで読み込むべきかどうかを示す真偽値</returns>
	bool ShouldLoadWithWIC(string _ext){
		std::unordered_set<std::string> supportedExtensions = {
			".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff"
		};

		return supportedExtensions.find(_ext) != supportedExtensions.end();
	}

	/// <summary>
	/// 指定された拡張子に応じてTGAで読み込むかどうかを判定します。
	/// </summary>
	/// <param name="_ext">ファイルの拡張子</param>
	/// <returns>TGAで読み込むべきかどうかを示す真偽値</returns>
	bool ShouldLoadWithTGA(string _ext) {
		std::unordered_set<std::string> supportedExtensions = {
			".tga", ".TGA", ".tpic",".psd"
		};
		return supportedExtensions.find(_ext) != supportedExtensions.end();
	}

	/// <summary>
	/// ファイルパスの拡張子を指定された新しい拡張子に変更します。
	/// </summary>
	/// <param name="filePath">変更するファイルパス</param>
	/// <param name="newExtension">新しい拡張子</param>
	/// <returns>拡張子を変更したファイルパス</returns>
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
	//ファイルパスを設定する
	SetFilePath(_filePath);
	TexMetadata metaData;
	ScratchImage scImage;

	//画像ファイルを読み込む
	if (LoadImageFile(_filePath, metaData, scImage) == false)return false;
	SetImageSize(metaData);

	// サンプラーを作成
	if (CreateSampler() == false)return false;

	//シェーダーリソースビューの作成
	if (CreateSRV(scImage, metaData) == false) return false;

	return true;
}

void Texture::SetImageSize(TexMetadata& _metaData)
{
	size_ = XMFLOAT2(_metaData.width, _metaData.height);
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
		if (ext == ".psd") _filePath = ChangeExtension(_filePath, "tga");

		if (FAILED(LoadFromTGAFile(StringToWString(_filePath).c_str(), &_metaData, _scImage))) {
#ifdef _DEBUG
			string ret = "画像ファイル(" + ext + ")の読み込み失敗しました";
			MessageBox(NULL, ret.c_str(), "エラー", MB_OK);
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
