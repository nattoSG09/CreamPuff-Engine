#pragma once
#include <string>
#include <DirectXTex.h>

// DirectXTex‚Ìƒ‰ƒCƒuƒ‰ƒŠ‚ðƒŠƒ“ƒN
#pragma comment(lib, "DirectXTex.lib")

using std::string;
using namespace DirectX;

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	string fileName_;
public:
	Texture();
	~Texture();

	bool Load(string _fileName);
};

