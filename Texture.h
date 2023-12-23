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

private:
	void SetFilePath(string _filePath) { filePath_ = _filePath; }
	bool LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage);
};

