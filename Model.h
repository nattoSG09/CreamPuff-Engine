#pragma once
#include "Engine/Direct3D.h"
#include "Structs.h"
#include "Engine/Components/Transform.h"

#include <string>
using std::string;

class Model
{
private:
	vector<ID3D11Buffer*> meshVertexBuffers_;
	vector<ID3D11Buffer*> meshIndexBuffers_;
	vector<ID3D11Buffer*> meshConstantBuffers_;

	vector<Mesh> meshes_;
public:
	bool Load(string _filePath);
	bool Load(string _filePath,bool _inverseU,bool _inverseV);
	void Draw(Transform _transform);
private:
	bool InitVertex(const Mesh& _mesh);
	bool InitIndex(const Mesh& _mesh);
	bool InitConstantBuffer();
};

