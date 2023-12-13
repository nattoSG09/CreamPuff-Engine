#include "Texture2D.h"

#include <locale>
#include <codecvt>

#include "Direct3D.h"


namespace {
	string GetExtension(const string& _fileName) {

		//「.(ドット)部分が何文字目かを抽出」
		auto idx = _fileName.rfind('.');

		//sample.fbx = fの部分から末尾にかけての「３文字」sample.fbx(10文字) - idx(6) - 1 を取得
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

	// 画像ファイルを読み込む
	if (LoadImageFile(_fileName, metaData, scImage) == false)return false;

	// サンプラーを作成
	if (CreateSampler() == false)return false;

	//シェーダーリソースビューの作成
	if (CreateSRV(scImage, metaData) == false) return false;

	return true;
}

bool Texture2D::LoadImageFile(string _fileName, TexMetadata& _metaData, ScratchImage& _scImage)
{
	//拡張子を文字列として取得
	string ext = GetExtension(_fileName);

	if (ext == "png") {
		if (FAILED(LoadFromWICFile(StringToWString(_fileName).c_str(), WIC_FLAGS_NONE, &_metaData, _scImage))) {
#ifdef _DEBUG
			MessageBox(NULL, "画像ファイル(.png)の読み込み失敗しました", "エラー", MB_OK);
#endif // _DEBUG
			return false;
		}
	}
	else if(ext == "tga") {
		HRESULT hr;
		if (FAILED(hr = LoadFromTGAFile(StringToWString(_fileName).c_str(), &_metaData, _scImage))) {
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

bool Texture2D::CreateSampler()
{
	// テクスチャサンプラーを設定
	D3D11_SAMPLER_DESC samplerDesc;
	InitSamplerDesc(samplerDesc);

	// サンプラーを作成
	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(d3D.Device()->CreateSamplerState(&samplerDesc, &pSampler_))) {
#ifdef _DEBUG
		MessageBox(NULL,"サンプラーの作成に失敗しました","エラー",MB_OK);
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
		MessageBox(NULL, "シェーダーリソースビューの作成に失敗しました", "エラー", MB_OK);
#endif // _DEBUG
		return false;
	}
	return true;
}
