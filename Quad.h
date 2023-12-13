#pragma once
#include "Engine/Direct3D.h"
#include "Engine/Texture2D.h"
#include "Engine/AssimpLoader.h"

using namespace DirectX;

struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
};

class Quad
{
private:
	std::vector<ID3D11Buffer*> meshVertexBuffers_;
	std::vector<ID3D11Buffer*> meshIndexBuffers_;
	std::vector<ID3D11Buffer*> meshConstantBuffers_;

	vector<Mesh> meshes_;
	vector<Vertex> vertices_;
	vector<uint32_t> indices_;
	vector<Texture2D*> textures_;
public:
	Quad();
	~Quad();

	void Initialize();
	void Draw();
	void Release();
};

