#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
using namespace DirectX;
using std::vector;
using std::string;

struct aiScene;
struct aiMesh;
struct aiMaterial;

// 頂点情報-構造体
struct Vertex{
    XMFLOAT3 Position; // 位置座標
    XMFLOAT3 Normal; // 法線
    XMFLOAT2 UV; // uv座標
    XMFLOAT3 Tangent; // 接空間
    XMFLOAT4 Color; // 頂点色
};

// メッシュ情報-構造体
struct Mesh{
    vector<Vertex> Vertices; // 頂点データの配列
    vector<uint32_t> Indices; // インデックスの配列
    vector<string> DiffuseMaps; // テクスチャのファイルパス
};

/// <summary>
/// assimpによるモデルに関連するデータをロードする
/// </summary>
class AssimpLoader
{
public:
    bool Load(string _fileName,vector<Mesh>& _meshs,bool _inverseU,bool _inverseV);
private:
    void InitFlags(int& _flags);
    void LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV);
    void LoadTexture(const string _filename, Mesh& _dst, const aiMaterial* _src);
};

