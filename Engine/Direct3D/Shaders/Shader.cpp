#include "Shader.h"
#include <Windows.h>
#include <d3dcompiler.h>
#include "../../Global.h"

namespace {
	std::wstring StringToWString(const string& utf8Str) {
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), nullptr, 0);
		std::wstring wideString(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &utf8Str[0], static_cast<int>(utf8Str.size()), &wideString[0], size_needed);
		return wideString;
	}
}

Shader::Shader(string _filePath)
	:filePath_(StringToWString(_filePath)), vertexLayout_(), rasterizerStateDesc_(), pVertexShader_(nullptr), pPixelShader_(nullptr)
	, pInputLayout_(nullptr), pRasterizerState_(nullptr)
{
}

Shader::~Shader()
{
	Release();
}

bool Shader::Initialize()
{
	// 頂点シェーダーをコンパイルする
	if (CompileVertexShader() == false)return false;

	// ピクセルシェーダーをコンパイルする
	if (CompilePixelShader() == false)return false;

	// ラスタライザを作成する
	if (CreateRasterizer() == false)return false;

	return true;
}

void Shader::Release()
{
	SAFE_RELEASE(pRasterizerState_);
	SAFE_RELEASE(pInputLayout_);
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);
}

bool Shader::CompileVertexShader()
{
	Direct3D& d3D = Direct3D::GetInstance();

	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(filePath_.c_str(), nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	if (FAILED(d3D.Device()->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader_))) {
#ifdef _DEBUG
		MessageBox(NULL, "頂点シェーダーの作成に失敗しました", "エラー", MB_OK);
#endif 
		SAFE_RELEASE(pCompileVS);
		return false;
	}

	InitVertexLayout();

	if (FAILED(d3D.Device()->CreateInputLayout(vertexLayout_.data(), vertexLayout_.size(), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pInputLayout_))) {
#ifdef _DEBUG
		MessageBox(NULL, "頂点インプットレイアウトの作成に失敗しました", "エラー", MB_OK);
#endif 
		SAFE_RELEASE(pCompileVS);
		return false;
	}

	SAFE_RELEASE(pCompileVS);
	return true;
}

bool Shader::CompilePixelShader()
{
	Direct3D& d3D = Direct3D::GetInstance();

	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(filePath_.c_str(), nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	if (FAILED(d3D.Device()->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader_))) {
		SAFE_RELEASE(pCompilePS);
#ifdef _DEBUG
		MessageBox(NULL, "ピクセルシェーダの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}
	SAFE_RELEASE(pCompilePS);
	return true;
}

bool Shader::CreateRasterizer()
{
	InitRasterizerState();

	Direct3D& d3D = Direct3D::GetInstance();
	if (FAILED(d3D.Device()->CreateRasterizerState(&rasterizerStateDesc_, &pRasterizerState_))) {
#ifdef _DEBUG
		MessageBox(NULL, "ラスタライザの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}
	return true;
}
