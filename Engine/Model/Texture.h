#pragma once
#include <string>
#include <DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

using std::string;
using namespace DirectX;

class Texture
{
private:
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	string filePath_;
public:
	Texture();
	~Texture();

	bool Load(string _filePath);
	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
private:
	void SetFilePath(string _filePath) { filePath_ = _filePath; }
	bool LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage);
	void InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc);
	bool CreateSampler();
	bool CreateSRV(ScratchImage& _scImage, TexMetadata& _metaData);
};

