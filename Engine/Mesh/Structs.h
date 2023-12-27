#pragma once
#include "Texture.h"
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;
using std::vector;

/// <summary>
/// 頂点情報-構造体
/// </summary>
struct Vertex {
	XMFLOAT3 position;	//位置座標
	XMFLOAT3 normal;	//法線
	XMFLOAT2 uv;		//uv座標
	XMFLOAT3 tangent;	//接空間
	XMFLOAT4 color;		//頂点色
};

/// <summary>
/// マテリアル情報-構造体
/// </summary>
struct Material {
	bool hasTexture;
	vector<Texture*> diffuseTextures;	//ディヒューズテクスチャ情報
	XMFLOAT4 diffuse;					//ディヒューズカラー情報
};

/// <summary>
/// メッシュ情報-構造体
/// </summary>
struct Mesh {
	vector<Vertex> vertices;	//頂点情報の配列
	vector<uint32_t> indices;	//インデックス情報の配列
	Material material;
};

/// <summary>
/// コンスタントバッファ-構造体
/// </summary>
struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;			//ワールド・ビュー・プロジェクション行列
	XMMATRIX	matNormal;		//法線行列
	XMFLOAT4	diffuseColor;	//ディヒューズカラー
	bool hasTexture;			//テクスチャの有無
};
