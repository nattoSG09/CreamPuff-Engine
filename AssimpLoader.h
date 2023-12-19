#pragma once
#include "Structs.h"
#include <string>
using std::string;

class AssimpLoader
{
private:

public:
	AssimpLoader();
	~AssimpLoader();
	bool Load(string _filePath, vector<Mesh>& _meshes);
	bool Load(string _filePath,vector<Mesh>& _meshes,bool _inverseU,bool _inverseV);
private:
	void InitFlags(int& _flags);
	bool LoadMesh(Mesh& _dst, const aiMesh* _src)
};

