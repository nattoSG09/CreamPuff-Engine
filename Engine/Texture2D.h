#pragma once
#include <string>
#include <DirectXTex.h>
// DirectXTex‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚ðƒŠƒ“ƒN
#pragma comment(lib, "DirectXTex.lib")


using std::string;
using namespace DirectX;

class Texture2D
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture2D();
	~Texture2D();

	bool Load(string _fileName);
	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
private:
	bool LoadImageFile(string _fileName, TexMetadata& _metaData, ScratchImage& _scImage);
	bool CreateSampler();
	void InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc);
	bool CreateSRV(ScratchImage& _scImage,TexMetadata& _metaData);
};

