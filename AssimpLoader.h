#pragma once
#include "Structs.h"

struct aiMesh;
struct aiMaterial;

class AssimpLoader
{
public:
	AssimpLoader();
	~AssimpLoader();

	bool Load(string _fileName, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV);

private:
	void InitFlags(int& _flags);
	bool LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV);
	bool LoadMaterial(string _fileName, Material& _dst, const aiMaterial* _src);
	bool LoadTexture(Material& _dst, const aiMaterial* _src);
};

