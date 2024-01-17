#include "CubeMapGenerator.h"
#include <functional>


CubeMapGenerator::CubeMapGenerator()
	:srvCubeMap_(nullptr),rtvCubeMap_(nullptr),dsv_(nullptr)
{
}

CubeMapGenerator::~CubeMapGenerator()
{
	Release();
}

void CubeMapGenerator::Generate(int _size, const XMVECTOR _position, std::function<void()> drawProc)
{
	Direct3D* d3d = &Direct3D::GetInstance();
	//--------------------------------------------------
	// １．CubeMapテクスチャ作成(初回のみ)
	//--------------------------------------------------
	CreateCubeMap(_size, d3d);

	// Zバッファを作成(初回のみ)
	CreateZBuffer(_size, d3d);

	// テクスチャリソースを取得
	ID3D11Resource* cubeMapResource = nullptr;
	rtvCubeMap_->GetResource(&cubeMapResource);

	//--------------------------------------------------
	// ２．上下左右前後の計６回描画し、CubeMapを作成する
	//--------------------------------------------------
	// RenderTarget、ZBuffer、Viewportの変更するため、
	// 現在のRenderTargetとZBufferとViewportを取得しておく
	ID3D11RenderTargetView* currentRTV[8] = {};
	ID3D11DepthStencilView* currentDSV = nullptr;
	d3d->Context()->OMGetRenderTargets(8, currentRTV, &currentDSV);

	D3D11_VIEWPORT currentVP;
	UINT numVPs = 1;
	d3d->Context()->RSGetViewports(&numVPs, &currentVP);

	// Viewportを変更
	D3D11_VIEWPORT vp = { 0, 0, (float)_size, (float)_size, 0, 1 };
	d3d->Context()->RSSetViewports(1, &vp);

	// キューブマップの各面(6枚)を描画
	for (int i = 0; i < 6; i++)
	{
		// キューブマップの各画像(上下左右前後)用のビューを作成
		ID3D11RenderTargetView* rtv = nullptr;
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // Format
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.ArraySize = 1;
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		rtvDesc.Texture2DArray.MipSlice = 0;
		// レンダーターゲットビュー作成
		d3d->Device()->CreateRenderTargetView(cubeMapResource, &rtvDesc, &rtv);

		// RT、Zクリア
		d3d->Context()->ClearRenderTargetView(rtv,0);
		d3d->Context()->ClearDepthStencilView(dsv_, D3D11_CLEAR_DEPTH, 1, 0);

		// RTとZを変更する
		d3d->Context()->OMSetRenderTargets(1, &rtv, dsv_);

		// カメラ設定
		XMMATRIX mView;
		switch (i)
		{
			// 右面(X)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_X:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(1, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// 左面(-X)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_X:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(-1, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// 上面(Y)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 1, 0, 1), XMVectorSet(0, 0, -1, 1));
			break;
			// 下面(-Y)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, -1, 0, 1), XMVectorSet(0, 0, 1, 1));
			break;
			// 後面(Z)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 0, 1, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// 前面(-Z)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 0, -1, 1), XMVectorSet(0, 1, 0, 1));
			break;
		}


		//// カメラ座標を定数バッファにセット
		//SHADER->m_cb7_Camera.Work().CamPos = mView.Invert().Translation();

		//// ビュー行列を定数バッファにセット
		//SHADER->m_cb7_Camera.Work().mView = mView;
		//// 射影行列を定数バッファにセット
		//SHADER->m_cb7_Camera.Work().mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90), 1.0f, 0.01f, 2000);
		//// 書き込み
		//SHADER->m_cb7_Camera.Write();

		////-----------------
		//// 描画実行
		//drawProc();
		////-----------------

		// ビュー解放
		rtv->Release();
	}

}

void CubeMapGenerator::Release()
{
}

void CubeMapGenerator::SaveToFile()
{
}

void CubeMapGenerator::CreateCubeMap(int _size, Direct3D* _d3d)
{
	if (srvCubeMap_ == nullptr && rtvCubeMap_ == nullptr)return;

	// テクスチャリソースを作成
	D3D11_TEXTURE2D_DESC desc = {};
	InitCubeMapTextureDesc(desc, _size);

	ID3D11Texture2D* resource = nullptr;
	_d3d->Device()->CreateTexture2D(&desc, nullptr, &resource);
	resource->GetDesc(&desc);// 正確なMipLevels取得のため、情報再取得

	// レンダーターゲットビューを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	InitCubeMapRTVDesc(rtvDesc, desc);
	_d3d->Device()->CreateRenderTargetView(resource, &rtvDesc, &rtvCubeMap_);

	// シェーダーリソースビューを作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	InitCubeMapSRVDesc(srvDesc, desc);
	_d3d->Device()->CreateShaderResourceView(resource, &srvDesc, &srvCubeMap_);

	//使用したリソースは解放
	resource->Release();
}

void CubeMapGenerator::CreateZBuffer(int _size, Direct3D* _d3d)
{
	if (dsv_ == nullptr)return;

	// テクスチャリソースを作成
	D3D11_TEXTURE2D_DESC desc = {};
	InitZBufferTextureDesc(desc,_size);

	ID3D11Texture2D* resource = nullptr;
	_d3d->Device()->CreateTexture2D(&desc, nullptr, &resource);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	InitZBufferDSVDesc(dsvDesc);
	_d3d->Device()->CreateDepthStencilView(resource, &dsvDesc, &dsv_);

	resource->Release();
}

void CubeMapGenerator::InitZBufferTextureDesc(D3D11_TEXTURE2D_DESC& _desc, int _size)
{
	_desc.Width = (UINT)_size;
	_desc.Height = (UINT)_size;
	_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	_desc.ArraySize = 1;
	_desc.MiscFlags = 0;

	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE |
		D3D11_BIND_DEPTH_STENCIL;
	_desc.CPUAccessFlags = 0;
	_desc.MipLevels = 1;
	_desc.SampleDesc.Count = 1;
	_desc.SampleDesc.Quality = 0;
}

void CubeMapGenerator::InitZBufferDSVDesc(D3D11_DEPTH_STENCIL_VIEW_DESC& _desc)
{
	_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	_desc.Texture2D.MipSlice = 0;
}

void CubeMapGenerator::InitCubeMapTextureDesc(D3D11_TEXTURE2D_DESC& _desc, int _size)
{
	_desc.Width = (UINT)_size;
	_desc.Height = (UINT)_size;
	_desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // HDRに対応する為RGBAすべてfloat型の値にする
	_desc.ArraySize = 6; // ６枚の画像を持ったテクスチャとして作成する
	_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | /*キューブマップ*/
		D3D11_RESOURCE_MISC_GENERATE_MIPS; /*MipMap生成*/
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE |
		D3D11_BIND_RENDER_TARGET;
	
	_desc.CPUAccessFlags = 0;
	_desc.MipLevels = 0; // 完全なミップマップチェーン
	_desc.SampleDesc.Count = 1;
	_desc.SampleDesc.Quality = 0;
}

void CubeMapGenerator::InitCubeMapRTVDesc(D3D11_RENDER_TARGET_VIEW_DESC& _desc, D3D11_TEXTURE2D_DESC& _texDesc)
{
	_desc.Format = _texDesc.Format; // Format
	_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY; // テクスチャ配列
	_desc.Texture2DArray.ArraySize = _texDesc.ArraySize; // 要素数
	_desc.Texture2DArray.FirstArraySlice = 0;
	_desc.Texture2DArray.MipSlice = 0;
}

void CubeMapGenerator::InitCubeMapSRVDesc(D3D11_SHADER_RESOURCE_VIEW_DESC& _desc, D3D11_TEXTURE2D_DESC& _texDesc)
{
	_desc.Format = _texDesc.Format;
	_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	_desc.TextureCube.MostDetailedMip = 0;
	_desc.TextureCube.MipLevels = _texDesc.MipLevels;
}
