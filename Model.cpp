#include "Model.h"
#include "AssimpLoader.h"
#include <filesystem>

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Load(string _fileName)
{
	

	//assimpLoader‚Åî•ñ‚ğæ“¾
	AssimpLoader al;
	al.Load(_fileName, meshes_, true, false);

	return false;
}
