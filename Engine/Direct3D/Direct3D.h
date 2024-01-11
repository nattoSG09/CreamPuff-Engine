#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <map>

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using std::map;

//前方宣言
class Window;
class Shader;

enum SHADER_HANDLE {
	SIMPLE_3D,
	DEBUG_3D,

};

/// <summary>
/// Direct3Dを管理するクラス
/// </summary>
class Direct3D
{
private:
	ID3D11Device* pDevice_;						/*Direct3D11デバイス*/
	ID3D11DeviceContext* pContext_;				/*Direct3D11コンテキスト*/
	IDXGISwapChain* pSwapChain_;				/*スワップチェーン*/
	ID3D11RenderTargetView* pRenderTargetView_;	/*レンダーターゲットビュー*/
	ID3D11Texture2D* pDepthStencil_;			/*デプスステンシル*/
	ID3D11DepthStencilView* pDepthStencilView_;	/*デプスステンシルビュー*/
	
	//test
	
	map<SHADER_HANDLE, Shader*> shaders_;

public:
	/// <summary>
	/// Direct3Dのインスタンスを取得する
	/// </summary>
	/// <returns>Direct3Dのインスタンス</returns>
	static Direct3D& GetInstance();

	/// <summary>
	/// Direct3Dの初期化を行う
	/// </summary>
	/// <param name="_window">ウィンドウ情報</param>
	/// <returns>正常に初期化が完了したら true を返す</returns>
	bool Initialize(Window* _window);

	/// <summary>
	/// 描画を開始する
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// 描画を終了する
	/// </summary>
	void EndDraw();

	/// <summary>
	/// Direct3Dリソースを開放する
	/// </summary>
	void Release();

	/// <summary>
	/// シェーダーを設定する
	/// </summary>
	void SetShader(SHADER_HANDLE _handle);

	void SetDepthBafferWriteEnable(bool isWrite);

// ゲッター・セッター　//
	ID3D11Device* Device() { return pDevice_; }									
	ID3D11DeviceContext* Context() { return pContext_; }
	IDXGISwapChain* SwapChain() { return pSwapChain_; }
	ID3D11RenderTargetView* RenderTargetView() { return pRenderTargetView_; }
	ID3D11Texture2D* DepthStencil() { return pDepthStencil_; }
	ID3D11DepthStencilView* DepthStencilView() { return pDepthStencilView_; }

private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Direct3D();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Direct3D();


private:
	/// <summary>
	/// スワップチェーンの設定を初期化する
	/// </summary>
	/// <param name="_scDesc">スワップチェーンの設定</param>
	/// <param name="_window">ウィンドウ情報</param>
	void InitScDesc(DXGI_SWAP_CHAIN_DESC& _scDesc, Window* _window);

	/// <summary>
	/// デバイスとスワップチェーンを作成する
	/// </summary>
	/// <param name="_scDesc">スワップチェーンの設定</param>
	/// <returns>正常に作成が完了したら true を返す</returns>
	bool CreateDeviceAndSwapChain(DXGI_SWAP_CHAIN_DESC _scDesc);

	/// <summary>
	/// レンダーターゲットビューを作成する
	/// </summary>
	/// <returns>正常に作成が完了したら true を返す</returns>
	bool CreateRenderTargetView();

	/// <summary>
	/// ビューポートを初期化する
	/// </summary>
	/// <param name="_vp">ビューポートの設定</param>
	/// <param name="_window">ウィンドウ情報</param>
	void InitViewPort(D3D11_VIEWPORT& _vp, Window* _window);

	/// <summary>
	/// デプスステンシルビューを初期化する
	/// </summary>
	/// <param name="_descDepth">デプスステンシルの設定</param>
	/// <param name="_window">ウィンドウの情報</param>
	void InitDepthStencilView(D3D11_TEXTURE2D_DESC& _descDepth, Window* _window);

	/// <summary>
	/// グラフィックスの初期化を行う
	/// </summary>
	/// <param name="_vp">ビューポート設定</param>
	/// <returns>正常に初期化が完了したら true を返す</returns>
	bool InitGraphics(D3D11_VIEWPORT& _vp);

	/// <summary>
	/// シェーダーの初期化を行う
	/// </summary>
	/// <returns>正常に初期化が完了したら true を返す</returns>
	bool InitShader();

};
