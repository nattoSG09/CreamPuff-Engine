#include "AssimpLoader.h"

// assimp�֘A�f�[�^�̃C���N���[�h
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
