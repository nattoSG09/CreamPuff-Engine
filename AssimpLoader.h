#pragma once
#include "Structs.h"

class AssimpLoader
{
public:
	AssimpLoader();
	~AssimpLoader();

	bool Load(string _fileName, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV);
};

