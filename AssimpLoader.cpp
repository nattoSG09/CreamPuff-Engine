#include "AssimpLoader.h"

// assimp関連データのインクルード
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

AssimpLoader::AssimpLoader()
{
}

AssimpLoader::~AssimpLoader()
{
}

bool AssimpLoader::Load(string _fileName, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV)
{
    return false;
}
