#include "Direct3D.h"

#include "../Global.h"
#include "../GUI/ImGuiManager.h"
#include "../Windows/Window.h"

#include "Shaders/Shader3D.h"
#include "Shaders/ShaderDebug.h"
#include "Shaders/ShaderToon.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>



using std::vector;
using DirectX::XMVECTOR;

#pragma warning(disable: 6387)
#pragma warning(disable: 4267)

Direct3D& Direct3D::GetInstance()
{
	static Direct3D instance;
	return instance;
}

bool Direct3D::Initialize(Window* _window)
{
	// �X���b�v�`�F�[���̐ݒ���s��
	DXGI_SWAP_CHAIN_DESC scDesc;
	InitScDesc(scDesc, _window);

	// �f�o�C�X���X���b�v�`�F�[�����쐬����
	if (CreateDeviceAndSwapChain(scDesc) == false)return false;

	// �����_�[�^�[�Q�b�g�r���[���쐬����
	if (CreateRenderTargetView() == false)return false;

	// �r���[�|�[�g�̐ݒ���s��
	D3D11_VIEWPORT vp;
	InitViewPort(vp, _window);

	// �f�v�X�X�e���V���r���[���쐬����
	D3D11_TEXTURE2D_DESC descDepth;
	InitDepthStencilView(descDepth, _window);

	// �O���t�B�b�N�X�̏��������s��
	if (InitGraphics(vp) == false)return false;

	// �V�F�[�_�[�̏��������s��
	if (InitShader() == false)return false;

	return true;
}

void Direct3D::BeginDraw()
{
	
	// �w�i�F
	static float clearColor[4] = { 0.1f,0.2f,0.3f,1.0f };
#ifdef _DEBUG
	ImGui::ColorPicker3("ColorPicker3", clearColor,
		ImGuiColorEditFlags_::ImGuiColorEditFlags_InputRGB);
#endif // _DEBUG


	// ��ʂ��N���A
	pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

	// �[�x�o�b�t�@�N���A
	pContext_->ClearDepthStencilView(pDepthStencilView_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::EndDraw()
{
	// �X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
	pSwapChain_->Present(0, 0);
}

void Direct3D::Release()
{
	for (auto const& pair : shaders_) {
		delete pair.second;
	}
	shaders_.clear();

	SAFE_RELEASE(pRenderTargetView_);
	SAFE_RELEASE(pSwapChain_);
	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);
	SAFE_RELEASE(pDepthStencil_);
	SAFE_RELEASE(pDepthStencilView_);
}

Direct3D::Direct3D()
	:pDevice_(nullptr), pContext_(nullptr), pSwapChain_(nullptr), pRenderTargetView_(nullptr)
	, pDepthStencil_(nullptr), pDepthStencilView_(nullptr)
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
	// DirectX11�f�o�C�X�ƃX���b�v�`�F�[�����쐬����
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
		MessageBox(NULL, "�f�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
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
		MessageBox(NULL, "�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
#endif 
		return false;
	}

	if (FAILED(pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_))) {
#ifdef _DEBUG
		MessageBox(NULL, "�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
#endif 
		return false;
	}

	pBackBuffer->Release();

	return true;
}

void Direct3D::InitViewPort(D3D11_VIEWPORT& _vp, Window* _window)
{
	float scale = 1.0f;/*Release��*/
#ifdef _DEBUG
	scale = 0.7f;/*Debug��*/
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
	pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // �`����ݒ�
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView_);            // �`����ݒ�
	pContext_->RSSetViewports(1, &_vp);

	if (pContext_ == nullptr)return false;
	return true;
}

bool Direct3D::InitShader()
{
	//�V�F�[�_�[��p��
	shaders_[SIMPLE_3D] = new Shader3D;
	shaders_[DEBUG_3D] = new ShaderDebug;
	shaders_[TOON_3D] = new ShaderToon;

	//�V�F�[�_�[��������
	for (auto it = shaders_.begin(); it != shaders_.end(); ++it) {
		if ((*it).second->Initialize() == false)return false;
	}

	//�V�F�[�_�[���Z�b�g
	SetShader(SIMPLE_3D);

	return true;
}

void Direct3D::SetShader(SHADER_HANDLE _handle)
{
	//���ꂼ����f�o�C�X�R���e�L�X�g�ɃZ�b�g
	pContext_->VSSetShader(shaders_[_handle]->VertexShader(), NULL, 0);	//���_�V�F�[�_�[
	pContext_->PSSetShader(shaders_[_handle]->PixelShader(), NULL, 0);	//�s�N�Z���V�F�[�_�[
	pContext_->IASetInputLayout(shaders_[_handle]->InputLayout());	//���_�C���v�b�g���C�A�E�g
	pContext_->RSSetState(shaders_[_handle]->RasterizerState());		//���X�^���C�U�[
}

void Direct3D::SetDepthBafferWriteEnable(bool _isWrite)
{
	//ON
	if (_isWrite)
	{
		//Z�o�b�t�@�i�f�v�X�X�e���V�����w�肷��j
		pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView_);
	}

	//OFF
	else
	{
		pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);
	}
}
