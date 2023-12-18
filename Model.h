#pragma once
#include "Structs.h"
#include "Engine/Direct3D.h"
#include "Engine/Components/Transform.h"

struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
};

class Model
{
private:
	vector<ID3D11Buffer*> meshVertexBuffers_;
	vector<ID3D11Buffer*> meshIndexBuffers_;
	vector<ID3D11Buffer*> meshConstantBuffers_;

	vector<Mesh> meshes_;
	vector<Vertex> vertices_;
	vector<uint32_t> indices_;
public:
	Model();
	~Model();

	bool Load(string _fileName);
	void Draw(Transform _transform);
	void Release();
private:
	void InitVertex(const Mesh& _mesh);
	void InitIndex(const Mesh& _mesh);
	void InitConstantBuffer();
};

