#include "Direct3D.h"

#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Windows/Window.h"
#include "Global.h"

using std::vector;
using DirectX::XMVECTOR;

#pragma warning(disable: 6387)
#pragma warning(disable: 4267)

bool Direct3D::Initialize(Window* _window)
{
	DXGI_SWAP_CHAIN_DESC scDesc;
	InitScDesc(scDesc, _window);

	if (CreateDeviceAndSwapChain(scDesc) == false)return false;

	if (CreateRenderTargetView() == false)return false;

	D3D11_VIEWPORT vp;
	InitViewPort(vp, _window);

	D3D11_TEXTURE2D_DESC descDepth;
	InitDepthStencilView(descDepth, _window);

	if (InitGraphics(vp) == false)return false;

	if (InitShader() == false)return false;

	return true;
}

void Direct3D::BeginDraw()
{
	// 背景色
	float clearColor[4] = { 0.1f,0.2f,0.3f,1.0f };

	// 画面をクリア
	pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

	// 深度バッファクリア
	pContext_->ClearDepthStencilView(pDepthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::EndDraw()
{
	// スワップ（バックバッファを表に表示する）
	pSwapChain_->Present(0, 0);
}

void Direct3D::Release()
{
	SAFE_RELEASE(pRasterizerState_);
	SAFE_RELEASE(pVertexLayout_);
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);

	SAFE_RELEASE(pRenderTargetView_);
	SAFE_RELEASE(pSwapChain_);
	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);
	SAFE_RELEASE(pDepthStencil_);
	SAFE_RELEASE(pDepthStencilView_);
}

Direct3D::Direct3D()
	:pDevice_(nullptr), pContext_(nullptr), pSwapChain_(nullptr), pRenderTargetView_(nullptr)
	, pDepthStencil_(nullptr), pDepthStencilView_(nullptr), pVertexShader_(nullptr), pPixelShader_(nullptr)
	, pVertexLayout_(nullptr), pRasterizerState_(nullptr)
{
}

Direct3D::~Direct3D()
{
}

void Direct3D::InitScDesc(DXGI_SWAP_CHAIN_DESC& _scDesc, Window* _window)
{
	ZeroMemory(&_scDesc, sizeof(_scDesc));

	_scDesc.BufferDesc.Width = _window->Width();
	_scDesc.BufferDesc.Height = _window->Height();
	_scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	_scDesc.BufferDesc.RefreshRate.Numerator = 60;
	_scDesc.BufferDesc.RefreshRate.Denominator = 1;

	_scDesc.Windowed = TRUE;
	_scDesc.OutputWindow = _window->WindowHandle();
	_scDesc.BufferCount = 1;
	_scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_scDesc.SampleDesc.Count = 1;
	_scDesc.SampleDesc.Quality = 0;
}

bool Direct3D::CreateDeviceAndSwapChain(DXGI_SWAP_CHAIN_DESC _scDesc)
{
	D3D_FEATURE_LEVEL level;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&_scDesc,
		&pSwapChain_,
		&pDevice_,
		&level,
		&pContext_
	);

	if (FAILED(hr)) {
#ifdef _DEBUG
		MessageBox(NULL, "デバイス、コンテキスト、スワップチェインの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}
	return true;
}

bool Direct3D::CreateRenderTargetView()
{
	ID3D11Texture2D* pBackBuffer = nullptr;
	if (FAILED(pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer))) {
#ifdef _DEBUG
		MessageBox(NULL, "バックバッファの取得に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}

	if (FAILED(pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_))) {
#ifdef _DEBUG
		MessageBox(NULL, "レンダーターゲットビューの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}

	pBackBuffer->Release();

	return true;
}

void Direct3D::InitViewPort(D3D11_VIEWPORT& _vp, Window* _window)
{
	float scale = 1.0f;
#ifdef _DEBUG
	scale = 0.7f;
#endif 
	_vp.Width = (float)_window->Width() * scale;
	_vp.Height = (float)_window->Height() * scale;
	_vp.MinDepth = 0.0f;
	_vp.MaxDepth = 1.0f;
	_vp.TopLeftX = 0;
	_vp.TopLeftY = 0;
}

void Direct3D::InitDepthStencilView(D3D11_TEXTURE2D_DESC& _descDepth, Window* _window)
{
	_descDepth.Width = _window->Width();
	_descDepth.Height = _window->Height();
	_descDepth.MipLevels = 1;
	_descDepth.ArraySize = 1;
	_descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	_descDepth.SampleDesc.Count = 1;
	_descDepth.SampleDesc.Quality = 0;
	_descDepth.Usage = D3D11_USAGE_DEFAULT;
	_descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_descDepth.CPUAccessFlags = 0;
	_descDepth.MiscFlags = 0;
	pDevice_->CreateTexture2D(&_descDepth, NULL, &pDepthStencil_);
	pDevice_->CreateDepthStencilView(pDepthStencil_, NULL, &pDepthStencilView_);
}

bool Direct3D::InitGraphics(D3D11_VIEWPORT& _vp)
{
	pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // 描画先を設定
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView_);            // 描画先を設定
	pContext_->RSSetViewports(1, &_vp);

	if (pContext_ == nullptr)return false;
	return true;
}

bool Direct3D::InitShader()
{
	if (CompileVertexShader() == false)return false;

	if (CompilePixelShader() == false)return false;

	if (CreateRasterizer() == false)return false;

	//シェーダーをセット
	SetShader();

	return true;
}

bool Direct3D::CompileVertexShader()
{
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Assets/Shader/Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	if (FAILED(pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader_))) {
#ifdef _DEBUG
		MessageBox(NULL, "頂点シェーダーの作成に失敗しました", "エラー", MB_OK);
#endif 
		SAFE_RELEASE(pCompileVS);
		return false;
	}

	//頂点インプットレイアウト
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(pDevice_->CreateInputLayout(layout.data(), layout.size(), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout_))) {
#ifdef _DEBUG
		MessageBox(NULL, "頂点インプットレイアウトの作成に失敗しました", "エラー", MB_OK);
#endif 
		SAFE_RELEASE(pCompileVS);
		return false;
	}

	SAFE_RELEASE(pCompileVS);
	return true;
}

bool Direct3D::CompilePixelShader()
{
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Assets/Shader/Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	if (FAILED(pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader_))) {
		SAFE_RELEASE(pCompilePS);
#ifdef _DEBUG
		MessageBox(NULL, "ピクセルシェーダの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}
	SAFE_RELEASE(pCompilePS);
	return true;
}

bool Direct3D::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	if (FAILED(pDevice_->CreateRasterizerState(&rdc, &pRasterizerState_))) {
#ifdef _DEBUG
		MessageBox(NULL, "ラスタライザの作成に失敗しました", "エラー", MB_OK);
#endif 
		return false;
	}
	return true;
}

void Direct3D::SetShader()
{
	//それぞれをデバイスコンテキストにセット
	pContext_->VSSetShader(pVertexShader_, NULL, 0);	//頂点シェーダー
	pContext_->PSSetShader(pPixelShader_, NULL, 0);	//ピクセルシェーダー
	pContext_->IASetInputLayout(pVertexLayout_);	//頂点インプットレイアウト
	pContext_->RSSetState(pRasterizerState_);		//ラスタライザー
}
