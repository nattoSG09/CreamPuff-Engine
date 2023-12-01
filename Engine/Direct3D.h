#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

//ÉäÉìÉJ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ëOï˚êÈåæ
class Window;

class Direct3D
{
private:
	ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;
	IDXGISwapChain* pSwapChain_;
	ID3D11RenderTargetView* pRenderTargetView_;
	ID3D11Texture2D* pDepthStencil_;
	ID3D11DepthStencilView* pDepthStencilView_;

	ID3D11VertexShader* pVertexShader_;
	ID3D11PixelShader* pPixelShader_;
	ID3D11InputLayout* pVertexLayout_;
	ID3D11RasterizerState* pRasterizerState_;

public:
	static Direct3D& GetInstance() {
		static Direct3D instance;
		return instance;
	}
	bool Initialize(Window* _window);
	void Update();
	void Draw();
	void Release();

	ID3D11Device* Device() { return pDevice_; }
	ID3D11DeviceContext* Context() { return pContext_; }
	IDXGISwapChain* SwapChain() { return pSwapChain_; }
	ID3D11RenderTargetView* RenderTargetView() { return pRenderTargetView_; }
	ID3D11Texture2D* DepthStencil() { return pDepthStencil_; }
	ID3D11DepthStencilView* DepthStencilView() { return pDepthStencilView_; }

	ID3D11VertexShader* VertexShader() { return pVertexShader_; }
	ID3D11PixelShader* PixelShader() { return pPixelShader_; }
	ID3D11InputLayout* VertexLayout() { return pVertexLayout_; }
	ID3D11RasterizerState* RasterizerState() { return pRasterizerState_; }

private:
	Direct3D();
	~Direct3D();

private:
	void InitScDesc(DXGI_SWAP_CHAIN_DESC& _scDesc, Window* _window);
	bool CreateDeviceAndSwapChain(DXGI_SWAP_CHAIN_DESC _scDesc);
	bool CreateRenderTargetView();
	void InitViewPort(D3D11_VIEWPORT& _vp, Window* _window);
	void InitDepthStencilView(D3D11_TEXTURE2D_DESC& _descDepth, Window* _window);
	bool InitGraphics(D3D11_VIEWPORT& _vp);
	bool InitShader();

	bool CompileVertexShader();
	bool CompilePixelShader();
	bool CreateRasterizer();
	void SetShader();
};
