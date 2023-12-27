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
	ID3D11VertexShader* pVertexShader_;			/*���_�V�F�[�_�[*/
	ID3D11PixelShader* pPixelShader_;			/*�s�N�Z���V�F�[�_�[*/
	ID3D11InputLayout* pInputLayout_;			/*���_���̓��C�A�E�g*/
	ID3D11RasterizerState* pRasterizerState_;	/*���X�^���C�U���*/

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

