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
	

	//assimpLoaderで情報を取得
	AssimpLoader al;
	al.Load(_fileName, meshes_, true, false);

	return false;
}
