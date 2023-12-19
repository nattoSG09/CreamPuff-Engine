#include "AssimpLoader.h"

// assimp関連データのインクルード
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
        MessageBox(NULL, importer.GetErrorString(), "エラー", MB_OK);
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
    _flags |= aiProcess_Triangulate;             // ポリゴンをすべて三角形に変換
    _flags |= aiProcess_PreTransformVertices;    // モデルの頂点をワールド空間に変換
    _flags |= aiProcess_CalcTangentSpace;        // 接空間を計算
    _flags |= aiProcess_GenSmoothNormals;        // スムーズな法線を計算
    _flags |= aiProcess_GenUVCoords;             // UV座標を生成
    _flags |= aiProcess_RemoveRedundantMaterials;// 不要なマテリアルを削除
    _flags |= aiProcess_OptimizeMeshes;          // メッシュを最適化
}
