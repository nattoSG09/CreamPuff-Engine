#pragma once
#include <DirectXTex.h>
#include "Engine/Direct3D/Direct3D.h"
using namespace DirectX;

class CubeMapGenerator
{
private:
	// �L���[�u�}�b�v(�ǂݎ��p)
	ID3D11ShaderResourceView* srvCubeMap_;

	// �L���[�u�}�b�v(�������ݗp)
	ID3D11RenderTargetView* rtvCubeMap_;

	// �`�掞�Ɏg�p����Z�o�b�t�@
	ID3D11DepthStencilView* dsv_;
public:
	CubeMapGenerator();
	~CubeMapGenerator();

	// �������ꂽ�L���[�u�}�b�v���擾
	ID3D11ShaderResourceView* const* GetCubeMap() const { return &srvCubeMap_; }

	// �w��T�C�Y�̃L���[�u�}�b�v�𐶐����A���i��`�悷��B
	// size �F�L���[�u�}�b�v�e�N�X�`���̃T�C�Y�B
	// position �F�B�e�̒��S�ƂȂ郏�[���h���W�B
	// drawProc �F�e�����Ŏ��s�������`�揈����n���B
	void Generate(int _size, const XMVECTOR _position, std::function<void()> drawProc);

	// ���
	void Release();

	// �L���[�u�}�b�v��DDS�t�@�C���֕ۑ�����
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

