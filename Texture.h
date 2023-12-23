#pragma once
#include <string>
#include <DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

using std::string;
using namespace DirectX;

class Texture
{
private:
	string filePath_;
public:
	Texture();
	~Texture();

	bool Load(string _filePath);
	void SetFilePath(string _filePath) { filePath_ = _filePath; }
	bool LoadFromWICFile(string _ext);
	bool LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage);
};

