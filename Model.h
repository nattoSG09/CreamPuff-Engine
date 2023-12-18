#pragma once
#include "Structs.h"

class Model
{
private:
	vector<Mesh> meshes_;
public:
	Model();
	~Model();

	bool Load(string _fileName);

};

