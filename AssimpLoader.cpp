#include "AssimpLoader.h"

// assimp�֘A�f�[�^�̃C���N���[�h
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Windows.h>

AssimpLoader::AssimpLoader()
{
}

AssimpLoader::~AssimpLoader()
{
}

bool AssimpLoader::Load(string _filePath, vector<Mesh>& _meshes)
{
    return Load(_filePath, _meshes,false,false);
}

bool AssimpLoader::Load(string _filePath, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV)
{
    int flags = 0;
    InitFlags(flags);

    Assimp::Importer importer{};
    const aiScene* scene = importer.ReadFile(_filePath, flags);

    if (scene == nullptr) {
#ifdef _DEBUG
        MessageBox(NULL, importer.GetErrorString(), "�G���[", MB_OK);
#endif // _DEBUG
        return false;
    }

    _meshes.clear();
    _meshes.resize(scene->mNumMeshes);

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        if (scene->HasMeshes()) {
            if (LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV) == false)
        }
    }

    return false;
}

void AssimpLoader::InitFlags(int& _flags)
{
    _flags |= aiProcess_Triangulate;             // �|���S�������ׂĎO�p�`�ɕϊ�
    _flags |= aiProcess_PreTransformVertices;    // ���f���̒��_�����[���h��Ԃɕϊ�
    _flags |= aiProcess_CalcTangentSpace;        // �ڋ�Ԃ��v�Z
    _flags |= aiProcess_GenSmoothNormals;        // �X���[�Y�Ȗ@�����v�Z
    _flags |= aiProcess_GenUVCoords;             // UV���W�𐶐�
    _flags |= aiProcess_RemoveRedundantMaterials;// �s�v�ȃ}�e���A�����폜
    _flags |= aiProcess_OptimizeMeshes;          // ���b�V�����œK��
}
