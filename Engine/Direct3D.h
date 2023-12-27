#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//�O���錾
class Window;

/// <summary>
/// Direct3D���Ǘ�����N���X
/// </summary>
class Direct3D
{
private:
	ID3D11Device* pDevice_;						/*Direct3D11�f�o�C�X*/
	ID3D11DeviceContext* pContext_;				/*Direct3D11�R���e�L�X�g*/
	IDXGISwapChain* pSwapChain_;				/*�X���b�v�`�F�[��*/
	ID3D11RenderTargetView* pRenderTargetView_;	/*�����_�[�^�[�Q�b�g�r���[*/
	ID3D11Texture2D* pDepthStencil_;			/*�f�v�X�X�e���V��*/
	ID3D11DepthStencilView* pDepthStencilView_;	/*�f�v�X�X�e���V���r���[*/

	ID3D11VertexShader* pVertexShader_;			/*���_�V�F�[�_�[*/
	ID3D11PixelShader* pPixelShader_;			/*�s�N�Z���V�F�[�_�[*/
	ID3D11InputLayout* pVertexLayout_;			/*���_���̓��C�A�E�g*/
	ID3D11RasterizerState* pRasterizerState_;	/*���X�^���C�U���*/

public:
	/// <summary>
	/// Direct3D�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>Direct3D�̃C���X�^���X</returns>
	static Direct3D& GetInstance();

	/// <summary>
	/// Direct3D�̏��������s��
	/// </summary>
	/// <param name="_window">�E�B���h�E���</param>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	bool Initialize(Window* _window);

	/// <summary>
	/// �`����J�n����
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// �`����I������
	/// </summary>
	void EndDraw();

	/// <summary>
	/// Direct3D���\�[�X���J������
	/// </summary>
	void Release();

// �Q�b�^�[�E�Z�b�^�[�@//
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
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Direct3D();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Direct3D();

private:
	/// <summary>
	/// �X���b�v�`�F�[���̐ݒ������������
	/// </summary>
	/// <param name="_scDesc">�X���b�v�`�F�[���̐ݒ�</param>
	/// <param name="_window">�E�B���h�E���</param>
	void InitScDesc(DXGI_SWAP_CHAIN_DESC& _scDesc, Window* _window);

	/// <summary>
	/// �f�o�C�X�ƃX���b�v�`�F�[�����쐬����
	/// </summary>
	/// <param name="_scDesc">�X���b�v�`�F�[���̐ݒ�</param>
	/// <returns>����ɍ쐬������������ true ��Ԃ�</returns>
	bool CreateDeviceAndSwapChain(DXGI_SWAP_CHAIN_DESC _scDesc);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[���쐬����
	/// </summary>
	/// <returns>����ɍ쐬������������ true ��Ԃ�</returns>
	bool CreateRenderTargetView();

	/// <summary>
	/// �r���[�|�[�g������������
	/// </summary>
	/// <param name="_vp">�r���[�|�[�g�̐ݒ�</param>
	/// <param name="_window">�E�B���h�E���</param>
	void InitViewPort(D3D11_VIEWPORT& _vp, Window* _window);

	/// <summary>
	/// �f�v�X�X�e���V���r���[������������
	/// </summary>
	/// <param name="_descDepth">�f�v�X�X�e���V���̐ݒ�</param>
	/// <param name="_window">�E�B���h�E�̏��</param>
	void InitDepthStencilView(D3D11_TEXTURE2D_DESC& _descDepth, Window* _window);

	/// <summary>
	/// �O���t�B�b�N�X�̏��������s��
	/// </summary>
	/// <param name="_vp">�r���[�|�[�g�ݒ�</param>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	bool InitGraphics(D3D11_VIEWPORT& _vp);

	/// <summary>
	/// �V�F�[�_�[�̏��������s��
	/// </summary>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	bool InitShader();

	/// <summary>
	/// ���_�V�F�[�_�[�̃R���p�C�����s��
	/// </summary>
	/// <returns>�R���p�C���ɐ��������� true ��Ԃ�</returns>
	bool CompileVertexShader();

	/// <summary>
	/// �s�N�Z���V�F�[�_�[�̃R���p�C�����s��
	/// </summary>
	/// <returns>�R���p�C���ɐ��������� true ��Ԃ�</returns>
	bool CompilePixelShader();

	/// <summary>
	/// ���X�^���C�U���쐬����
	/// </summary>
	/// <returns>�쐬�ɐ��������� true ��Ԃ�</returns>
	bool CreateRasterizer();

	/// <summary>
	/// �V�F�[�_�[��ݒ肷��
	/// </summary>
	void SetShader();
};
