#include "AssimpLoader.h"
#include <Windows.h>

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
    // フラグの設定
    int flags = 0;
    InitFlags(flags);

    // ファイルをロード
    Assimp::Importer importer{};
    const aiScene* scene = importer.ReadFile(_fileName, flags);

    if (scene == nullptr) {
#ifdef _DEBUG
        MessageBox(NULL, importer.GetErrorString(), "エラー", MB_OK);
#endif // _DEBUG
        return false;
    }

    //配列サイズをリセットし、メッシュの数と同じサイズに変更
    _meshes.clear();
    _meshes.resize(scene->mNumMeshes);
    
    // メッシュ分のメッシュ情報・マテリアル情報を取得
    for (int i = 0; i < scene->mNumMeshes; ++i) {
        // メッシュ情報の取得
        if (scene->HasMeshes()) {
            if (LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV) == false) {
#ifdef _DEBUG
                MessageBox(NULL, "メッシュのロードに失敗しました", "エラー", MB_OK);
#endif // _DEBUG
                return false;
            }
        }

        // マテリアル情報の取得
//        if (scene->HasMaterials()) {
//            if (LoadMaterial(_fileName, _meshes[i].material, scene->mMaterials[i]) == false) {
//#ifdef _DEBUG
//                MessageBox(NULL, "マテリアルのロードに失敗しました", "エラー", MB_OK);
//#endif // _DEBUG
//                return false;
//            }
//        }
    }

    scene = nullptr;
    return true;
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
    if (!_src) return false;

    // ０で初期化するための変数を用意
    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);
    
// 頂点情報を取得 //
    // 配列サイズをリセットし、頂点数と同じサイズに変更
    _dst.vertices.clear();
    _dst.vertices.resize(_src->mNumVertices);

    // 頂点数分の位置・法線・UV・接空間・頂点色・インデックス情報を取得
    for (unsigned int i = 0; i < _src->mNumVertices; ++i) {
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

// インデックス情報を取得 //
        // 配列サイズをリセットし、インデックス数と同じサイズに変更
        _dst.indices.resize(_src->mNumFaces * 3);

        // インデックス情報を格納
        for (auto i = 0u; i < _src->mNumFaces; ++i){
            const auto& face = _src->mFaces[i];
            _dst.indices[i * 3 + 0] = face.mIndices[0];
            _dst.indices[i * 3 + 1] = face.mIndices[1];
            _dst.indices[i * 3 + 2] = face.mIndices[2];
        }
    }

    //配列情報が空だったら
    if (_dst.vertices.empty())return false;
    if (_dst.indices.empty())return false;
    return true;
}

bool AssimpLoader::LoadMaterial(string _fileName, Material& _dst, const aiMaterial* _src)
{
    if (!_src) return false;

    //テクスチャを取得
    if(LoadTexture(_dst, _src) == false)return false;
    
    //ディヒューズカラーを取得
    aiColor3D diffuseColor(0.f, 0.f, 0.f);
    if (AI_SUCCESS == _src->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
        // ディフューズ（アルベド）カラーを取得し、_dst の対応するメンバにセットする
        _dst.diffuse = XMFLOAT4(diffuseColor.r, diffuseColor.g, diffuseColor.b,0.f);
    }

    return true;
}

bool AssimpLoader::LoadTexture(Material& _dst, const aiMaterial* _src)
{
    if (!_src) return false;

    //現在のカレントディレクトリを取得
    char defaultCurrentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

    // ディフューズテクスチャを取得
    _dst.diffuseTextures.clear();
    _dst.diffuseTextures.resize(_src->GetTextureCount(aiTextureType_DIFFUSE));
    for (int i = 0; i < _src->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
        aiString texturePath;
        if (_src->GetTexture(aiTextureType_DIFFUSE, i, &texturePath) == AI_SUCCESS) {

            //引数のfileNameからディレクトリ部分を取得
            char dir[MAX_PATH];
            _splitpath_s(texturePath.C_Str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);

            Texture* texture = new Texture;
            if (texture->Load(dir + string(texturePath.C_Str())) == false)return false;
            _dst.diffuseTextures[i] = texture;
        }
    }

    return true;
}
