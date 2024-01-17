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
	// �P�DCubeMap�e�N�X�`���쐬(����̂�)
	//--------------------------------------------------
	CreateCubeMap(_size, d3d);

	// Z�o�b�t�@���쐬(����̂�)
	CreateZBuffer(_size, d3d);

	// �e�N�X�`�����\�[�X���擾
	ID3D11Resource* cubeMapResource = nullptr;
	rtvCubeMap_->GetResource(&cubeMapResource);

	//--------------------------------------------------
	// �Q�D�㉺���E�O��̌v�U��`�悵�ACubeMap���쐬����
	//--------------------------------------------------
	// RenderTarget�AZBuffer�AViewport�̕ύX���邽�߁A
	// ���݂�RenderTarget��ZBuffer��Viewport���擾���Ă���
	ID3D11RenderTargetView* currentRTV[8] = {};
	ID3D11DepthStencilView* currentDSV = nullptr;
	d3d->Context()->OMGetRenderTargets(8, currentRTV, &currentDSV);

	D3D11_VIEWPORT currentVP;
	UINT numVPs = 1;
	d3d->Context()->RSGetViewports(&numVPs, &currentVP);

	// Viewport��ύX
	D3D11_VIEWPORT vp = { 0, 0, (float)_size, (float)_size, 0, 1 };
	d3d->Context()->RSSetViewports(1, &vp);

	// �L���[�u�}�b�v�̊e��(6��)��`��
	for (int i = 0; i < 6; i++)
	{
		// �L���[�u�}�b�v�̊e�摜(�㉺���E�O��)�p�̃r���[���쐬
		ID3D11RenderTargetView* rtv = nullptr;
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // Format
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.ArraySize = 1;
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		rtvDesc.Texture2DArray.MipSlice = 0;
		// �����_�[�^�[�Q�b�g�r���[�쐬
		d3d->Device()->CreateRenderTargetView(cubeMapResource, &rtvDesc, &rtv);

		// RT�AZ�N���A
		d3d->Context()->ClearRenderTargetView(rtv,0);
		d3d->Context()->ClearDepthStencilView(dsv_, D3D11_CLEAR_DEPTH, 1, 0);

		// RT��Z��ύX����
		d3d->Context()->OMSetRenderTargets(1, &rtv, dsv_);

		// �J�����ݒ�
		XMMATRIX mView;
		switch (i)
		{
			// �E��(X)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_X:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(1, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// ����(-X)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_X:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(-1, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// ���(Y)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 1, 0, 1), XMVectorSet(0, 0, -1, 1));
			break;
			// ����(-Y)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, -1, 0, 1), XMVectorSet(0, 0, 1, 1));
			break;
			// ���(Z)
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 0, 1, 1), XMVectorSet(0, 1, 0, 1));
			break;
			// �O��(-Z)
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(_position, _position + XMVectorSet(0, 0, -1, 1), XMVectorSet(0, 1, 0, 1));
			break;
		}


		//// �J�������W��萔�o�b�t�@�ɃZ�b�g
		//SHADER->m_cb7_Camera.Work().CamPos = mView.Invert().Translation();

		//// �r���[�s���萔�o�b�t�@�ɃZ�b�g
		//SHADER->m_cb7_Camera.Work().mView = mView;
		//// �ˉe�s���萔�o�b�t�@�ɃZ�b�g
		//SHADER->m_cb7_Camera.Work().mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90), 1.0f, 0.01f, 2000);
		//// ��������
		//SHADER->m_cb7_Camera.Write();

		////-----------------
		//// �`����s
		//drawProc();
		////-----------------

		// �r���[���
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

	// �e�N�X�`�����\�[�X���쐬
	D3D11_TEXTURE2D_DESC desc = {};
	InitCubeMapTextureDesc(desc, _size);

	ID3D11Texture2D* resource = nullptr;
	_d3d->Device()->CreateTexture2D(&desc, nullptr, &resource);
	resource->GetDesc(&desc);// ���m��MipLevels�擾�̂��߁A���Ď擾

	// �����_�[�^�[�Q�b�g�r���[���쐬
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	InitCubeMapRTVDesc(rtvDesc, desc);
	_d3d->Device()->CreateRenderTargetView(resource, &rtvDesc, &rtvCubeMap_);

	// �V�F�[�_�[���\�[�X�r���[���쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	InitCubeMapSRVDesc(srvDesc, desc);
	_d3d->Device()->CreateShaderResourceView(resource, &srvDesc, &srvCubeMap_);

	//�g�p�������\�[�X�͉��
	resource->Release();
}

void CubeMapGenerator::CreateZBuffer(int _size, Direct3D* _d3d)
{
	if (dsv_ == nullptr)return;

	// �e�N�X�`�����\�[�X���쐬
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
	_desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // HDR�ɑΉ������RGBA���ׂ�float�^�̒l�ɂ���
	_desc.ArraySize = 6; // �U���̉摜���������e�N�X�`���Ƃ��č쐬����
	_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE | /*�L���[�u�}�b�v*/
		D3D11_RESOURCE_MISC_GENERATE_MIPS; /*MipMap����*/
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE |
		D3D11_BIND_RENDER_TARGET;
	
	_desc.CPUAccessFlags = 0;
	_desc.MipLevels = 0; // ���S�ȃ~�b�v�}�b�v�`�F�[��
	_desc.SampleDesc.Count = 1;
	_desc.SampleDesc.Quality = 0;
}

void CubeMapGenerator::InitCubeMapRTVDesc(D3D11_RENDER_TARGET_VIEW_DESC& _desc, D3D11_TEXTURE2D_DESC& _texDesc)
{
	_desc.Format = _texDesc.Format; // Format
	_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY; // �e�N�X�`���z��
	_desc.Texture2DArray.ArraySize = _texDesc.ArraySize; // �v�f��
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
