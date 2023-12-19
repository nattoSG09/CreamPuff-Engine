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
            if (LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV) == false)return false;
        }

        if (scene->HasMaterials()) {
            if (LoadMaterial(_filePath, _meshes[i].material, scene->mMaterials[i]))return false;
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

bool AssimpLoader::LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV)
{
    if (_src == nullptr)return false;

    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

    _dst.vertices.clear();
    _dst.vertices.resize(_src->mNumVertices);

    // 頂点数分の位置・法線・UV・接空間・頂点色・インデックス情報を取得
    for (int i = 0; i < _src->mNumVertices; ++i) {
        aiVector3D* pos = &(_src->mVertices[i]);
        aiVector3D* nor = &(_src->mNormals[i]);
        aiVector3D* uv = (_src->HasTextureCoords(0)) ? &(_src->mTextureCoords[0][i]) : &zero3D;
        aiVector3D* tan = (_src->HasTangentsAndBitangents()) ? &(_src->mTangents[i]) : &zero3D;
        aiColor4D* col = (_src->HasVertexColors(0)) ? &(_src->mColors[0][i]) : &zeroColor;

        // 反転オプションがあったらUVを反転させる
        if (_inverseU)uv->x = 1 - uv->x;
        if (_inverseV)uv->y = 1 - uv->y;

        // 頂点情報を格納
        Vertex vertex{};
        vertex.position = DirectX::XMFLOAT3(-pos->x, pos->y, pos->z);
        vertex.normal = DirectX::XMFLOAT3(nor->x, nor->y, nor->z);
        vertex.uv = DirectX::XMFLOAT2(uv->x, uv->y);
        vertex.tangent = DirectX::XMFLOAT3(tan->x, tan->y, tan->z);
        vertex.color = DirectX::XMFLOAT4(col->r, col->g, col->b, col->a);
        _dst.vertices[i] = vertex;

        _dst.indices.resize(_src->mNumFaces * 3);
        for (auto i = 0u; i < _src->mNumFaces; ++i) {
            const auto& face = _src->mFaces[i];
            _dst.indices[i * 3 + 0] = face.mIndices[0];
            _dst.indices[i * 3 + 1] = face.mIndices[1];
            _dst.indices[i * 3 + 2] = face.mIndices[2];
        }
    }

    if (_dst.vertices.empty())return false;
    if (_dst.indices.empty())return false;
    return true;
}

bool AssimpLoader::LoadMaterial(string _filePath, Material& _dst, const aiMaterial* _src)
{
    if (_src == nullptr)return false;

    //ディヒューズカラーを取得
    aiColor3D diffuseColor(0.f, 0.f, 0.f);
    if (AI_SUCCESS == _src->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
        _dst.diffuse = XMFLOAT4(diffuseColor.r, diffuseColor.g, diffuseColor.b, 0.f);
    }

    return true;
}
