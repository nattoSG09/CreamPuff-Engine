#pragma once
#include "Structs.h"
#include <string>

using std::string;
struct aiMesh;
struct aiMaterial;

/// <summary>
/// Assimpを使用してモデルを読み込むためのクラスです。
/// </summary>
class AssimpLoader
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AssimpLoader();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AssimpLoader();

	/// <summary>
	/// 指定されたファイルパスからメッシュをロードする
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_meshes">ロードされたメッシュを格納するベクター</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool Load(string _filePath, vector<Mesh>& _meshes);

	/// <summary>
	/// 指定されたファイルパスからメッシュをロードする
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_meshes">ロードされたメッシュを格納するベクター</param>
	/// <param name="_inverseU">U軸の反転を行うかどうか</param>
	/// <param name="_inverseV">V軸の反転を行うかどうか</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool Load(string _filePath,vector<Mesh>& _meshes,bool _inverseU,bool _inverseV);
private:
	/// <summary>
    /// Assimpのフラグを初期化します
    /// </summary>
    /// <param name="_flags">初期化するフラグ</param>
	void InitFlags(int& _flags);

	/// <summary>
	/// Assimpのメッシュをロードする
	/// </summary>
	/// <param name="_dst">ロード先のMeshオブジェクト</param>
	/// <param name="_src">元となるAssimpのメッシュ</param>
	/// <param name="_inverseU">U軸の反転を行うかどうか</param>
	/// <param name="_inverseV">V軸の反転を行うかどうか</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV);

	/// <summary>
	/// Assimpのマテリアルをロードする
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_dst">ロード先のMaterialオブジェクト</param>
	/// <param name="_src">元となるAssimpのマテリアル</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool LoadMaterial(string _filePath, Material& _dst, const aiMaterial* _src);

	/// <summary>
	/// テクスチャをロードしてMaterialに適用する
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_dst">ロード先のMaterialオブジェクト</param>
	/// <param name="_src">元となるAssimpのマテリアル</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool LoadTexture(string _filePath,Material& _dst, const aiMaterial* _src);
};

