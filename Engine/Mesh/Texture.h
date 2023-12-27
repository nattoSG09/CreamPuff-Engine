#pragma once
#include <string>
#include <DirectXTex.h>

#pragma comment(lib,"DirectXTex.lib")

using std::string;
using namespace DirectX;

/// <summary>
/// テクスチャを管理するクラス
/// </summary>
class Texture
{
private:
	ID3D11SamplerState* pSampler_;///< サンプラーステート
	ID3D11ShaderResourceView* pSRV_;///< シェーダーリソースビュー
	string filePath_;///< ファイルのパス
	XMFLOAT2 size_;	///< ファイルのサイズ
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Texture();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Texture();

	/// <summary>
	/// 指定されたファイルパスからテクスチャをロードします。
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool Load(string _filePath);

	/// <summary>
	/// テクスチャのサンプラーステートを取得します。
	/// </summary>
	/// <returns>サンプラーステート</returns>
	ID3D11SamplerState* GetSampler() { return pSampler_; }

	/// <summary>
	/// テクスチャのシェーダーリソースビューを取得します。
	/// </summary>
	/// <returns>シェーダーリソースビュー</returns>
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }

	XMFLOAT2 GetSize() const { return size_; }
private:
	/// <summary>
	/// ファイルパスを設定します。
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	void SetFilePath(string _filePath) { filePath_ = _filePath; }

	/// <summary>
	/// テクスチャのメタデータから画像サイズを取得する
	/// </summary>
	/// <param name="_metaData">テクスチャのメタデータ</param>
	void SetImageSize(TexMetadata& _metaData);

	/// <summary>
	/// 画像ファイルをロードします。
	/// </summary>
	/// <param name="_filePath">ファイルのパス</param>
	/// <param name="_metaData">テクスチャのメタデータ</param>
	/// <param name="_scImage">画像データの一時的なイメージ</param>
	/// <returns>ロードが成功したかどうかを示す真偽値</returns>
	bool LoadImageFile(string _filePath, TexMetadata& _metaData, ScratchImage& _scImage);
	
	/// <summary>
	/// サンプラーステートの設定を初期化します。
	/// </summary>
	/// <param name="_samplerDesc">サンプラーステートの設定</param>
	void InitSamplerDesc(D3D11_SAMPLER_DESC& _samplerDesc);
	
	/// <summary>
	/// サンプラーステートを作成します。
	/// </summary>
	/// <returns>作成が成功したかどうかを示す真偽値</returns>
	bool CreateSampler();
	
	/// <summary>
	/// シェーダーリソースビューを作成します。
	/// </summary>
	/// <param name="_scImage">画像データの一時的なイメージ</param>
	/// <param name="_metaData">テクスチャのメタデータ</param>
	/// <returns>作成が成功したかどうかを示す真偽値</returns>
	bool CreateSRV(ScratchImage& _scImage, TexMetadata& _metaData);
};

