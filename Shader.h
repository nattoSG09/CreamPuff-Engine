#pragma once
#include "Engine/Direct3D.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Shader
{
protected:
	vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout_;
	D3D11_RASTERIZER_DESC rasterizerStateDesc_;

private:
	std::wstring filePath_;
	ID3D11VertexShader* pVertexShader_;			/*頂点シェーダー*/
	ID3D11PixelShader* pPixelShader_;			/*ピクセルシェーダー*/
	ID3D11InputLayout* pInputLayout_;			/*頂点入力レイアウト*/
	ID3D11RasterizerState* pRasterizerState_;	/*ラスタライザ状態*/

public:
	Shader(string _filePath);
	~Shader();
	bool Initialize();
	void Release();

	ID3D11VertexShader* VertexShader() { return pVertexShader_; }
	ID3D11PixelShader* PixelShader() { return pPixelShader_; }
	ID3D11InputLayout* InputLayout() { return pInputLayout_; }
	ID3D11RasterizerState* RasterizerState() { return pRasterizerState_; }
protected:
	virtual void InitVertexLayout() = 0;
	virtual void InitRasterizerState() = 0;

private:
	bool CompileVertexShader();
	bool CompilePixelShader();
	bool CreateRasterizer();
};

