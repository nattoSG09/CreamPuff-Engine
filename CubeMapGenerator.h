#pragma once
#include <DirectXTex.h>
#include "Engine/Direct3D/Direct3D.h"
using namespace DirectX;

class CubeMapGenerator
{
private:
	// キューブマップ(読み取り用)
	ID3D11ShaderResourceView* srvCubeMap_;

	// キューブマップ(書き込み用)
	ID3D11RenderTargetView* rtvCubeMap_;

	// 描画時に使用するZバッファ
	ID3D11DepthStencilView* dsv_;
public:
	CubeMapGenerator();
	~CubeMapGenerator();

	// 生成されたキューブマップを取得
	ID3D11ShaderResourceView* const* GetCubeMap() const { return &srvCubeMap_; }

	// 指定サイズのキューブマップを生成し、風景を描画する。
	// size ：キューブマップテクスチャのサイズ。
	// position ：撮影の中心となるワールド座標。
	// drawProc ：各方向で実行したい描画処理を渡す。
	void Generate(int _size, const XMVECTOR _position, std::function<void()> drawProc);

	// 解放
	void Release();

	// キューブマップをDDSファイルへ保存する
	void SaveToFile();

private:
	void CreateCubeMap(int _size, Direct3D* _d3d);
	
	void InitCubeMapTextureDesc(D3D11_TEXTURE2D_DESC& _desc,int _size);
	void InitCubeMapRTVDesc(D3D11_RENDER_TARGET_VIEW_DESC& _desc, D3D11_TEXTURE2D_DESC& _texDesc);
	void InitCubeMapSRVDesc(D3D11_SHADER_RESOURCE_VIEW_DESC& _desc, D3D11_TEXTURE2D_DESC& _texDesc);

	void CreateZBuffer(int _size, Direct3D* _d3d);
	void InitZBufferTextureDesc(D3D11_TEXTURE2D_DESC& _desc, int _size);
	void InitZBufferDSVDesc(D3D11_DEPTH_STENCIL_VIEW_DESC& _desc);
};

