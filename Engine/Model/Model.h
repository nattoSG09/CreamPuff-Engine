#pragma once
#include "../Components/Transform.h"
#include "../Direct3D.h"
#include "Structs.h"

#include <string>
using std::string;

/// <summary>
/// モデルを管理するクラス
/// </summary>
class Model
{
private:
	vector<ID3D11Buffer*> meshVertexBuffers_;///< メッシュの頂点バッファー
	vector<ID3D11Buffer*> meshIndexBuffers_;///< メッシュのインデックスバッファー
	vector<ID3D11Buffer*> meshConstantBuffers_;///< メッシュの定数バッファー

	vector<Mesh> meshes_;///< ロードされたメッシュのリスト
public:
	/// <summary>
	/// 指定されたファイルパスからモデルをロードします。
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool Load(string _filePath);

	/// <summary>
	/// 指定されたファイルパスからモデルをロードします。
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_inverseU">U軸の反転を行うかどうか</param>
	/// <param name="_inverseV">V軸の反転を行うかどうか</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool Load(string _filePath,bool _inverseU,bool _inverseV);

	/// <summary>
	/// モデルを描画します。
	/// </summary>
	/// <param name="_transform">モデルの変換情報</param>
	void Draw(Transform _transform);
private:
	/// <summary>
	/// メッシュの頂点を初期化します。
	/// </summary>
	/// <param name="_mesh">初期化するメッシュ</param>
	/// <returns>初期化が成功したかどうかを示す真偽値</returns>
	bool InitVertex(const Mesh& _mesh);

	/// <summary>
	/// メッシュのインデックスを初期化します。
	/// </summary>
	/// <param name="_mesh">初期化するメッシュ</param>
	/// <returns>初期化が成功したかどうかを示す真偽値</returns>
	bool InitIndex(const Mesh& _mesh);

	/// <summary>
	/// メッシュの定数バッファーを初期化します。
	/// </summary>
	/// <returns>初期化が成功したかどうかを示す真偽値</returns>
	bool InitConstantBuffer();
};

