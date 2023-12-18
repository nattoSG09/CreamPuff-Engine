#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Texture.h"

using namespace DirectX;
using std::vector;
using std::string;

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
struct Material{
	vector<Texture*> textures;	//テクスチャ情報
};

/// <summary>
/// メッシュ情報-構造体
/// </summary>
struct Mesh{
	vector<Vertex> vertices;	//頂点情報の配列
	vector<uint32_t> indices;	//インデックス情報の配列
	vector<Material> materials;
};