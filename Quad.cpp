#include "Quad.h"
#include "Engine/Global.h"

Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::Initialize()
{
    Direct3D& d3d = Direct3D::GetInstance();

    // ���f�������[�h
    AssimpLoader al;
    al.Load("Assets/Alicia/FBX/Alicia_solid_MMD.FBX", meshes_, true, false);

    for (const auto& mesh : meshes_) {
        // ���_�o�b�t�@��p��
        vertices_ = mesh.Vertices;

        // ���_�o�b�t�@�𐶐�����
        ID3D11Buffer* meshVertexBuffer;
        D3D11_BUFFER_DESC bd_vertex = {};
        bd_vertex.ByteWidth = sizeof(Vertex) * vertices_.size();
        bd_vertex.Usage = D3D11_USAGE_DEFAULT;
        bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd_vertex.CPUAccessFlags = 0;
        bd_vertex.MiscFlags = 0;
        bd_vertex.StructureByteStride = 0;
        D3D11_SUBRESOURCE_DATA data_vertex = {};
        data_vertex.pSysMem = vertices_.data();
        d3d.Device()->CreateBuffer(&bd_vertex, &data_vertex, &meshVertexBuffer);

        // ���_�o�b�t�@��z��ɒǉ�
        meshVertexBuffers_.push_back(meshVertexBuffer);

        // �C���f�b�N�X�o�b�t�@��p��
        indices_ = mesh.Indices;

        // �C���f�b�N�X�o�b�t�@�𐶐�����
        ID3D11Buffer* meshIndexBuffer;
        D3D11_BUFFER_DESC bd_index = {};
        bd_index.Usage = D3D11_USAGE_DEFAULT;
        bd_index.ByteWidth = sizeof(uint32_t) * indices_.size();
        bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd_index.CPUAccessFlags = 0;
        bd_index.MiscFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData = {};
        InitData.pSysMem = indices_.data();
        InitData.SysMemPitch = 0;
        InitData.SysMemSlicePitch = 0;
        d3d.Device()->CreateBuffer(&bd_index, &InitData, &meshIndexBuffer);

        // �C���f�b�N�X�o�b�t�@��z��ɒǉ�
        meshIndexBuffers_.push_back(meshIndexBuffer);

        // �R���X�^���g�o�b�t�@�̍쐬
        ID3D11Buffer* meshConstantBuffer;
        D3D11_BUFFER_DESC cb = {};
        cb.ByteWidth = sizeof(CONSTANT_BUFFER);
        cb.Usage = D3D11_USAGE_DYNAMIC;
        cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        cb.MiscFlags = 0;
        cb.StructureByteStride = 0;
        d3d.Device()->CreateBuffer(&cb, nullptr, &meshConstantBuffer);

        // �쐬�����R���X�^���g�o�b�t�@��z��ɒǉ�
        meshConstantBuffers_.push_back(meshConstantBuffer);
    }
}

void Quad::Draw()
{
    Direct3D& d3d = Direct3D::GetInstance();

    for (int i = 0; i < meshes_.size(); ++i) {
        // ���b�V�����Ƃ̃R���X�^���g�o�b�t�@���Z�b�g
        d3d.Context()->VSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // ���_�V�F�[�_�[�p    
        d3d.Context()->PSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // �s�N�Z���V�F�[�_�[�p

        // �e���b�V�����ƂɈقȂ�r���[�s���ˉe�s��Ȃǂ̏���ݒ肷��
        XMVECTOR position = { 0, 120, 75, 0 };
        XMVECTOR target = { 0, 120, 0, 0 };
        XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0)); // ���b�V�����Ƃ̃r���[�s��
        XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1280.0f / 720.0f, 0.1f, 100.0f); // ���b�V�����Ƃ̎ˉe�s��

        CONSTANT_BUFFER cb = {};
        cb.matWVP = XMMatrixTranspose(view * proj);

        D3D11_MAPPED_SUBRESOURCE pdata;
        d3d.Context()->Map(meshConstantBuffers_[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); // GPU����̃f�[�^�A�N�Z�X���~�߂�
        memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb)); // �f�[�^��l�𑗂�
        d3d.Context()->Unmap(meshConstantBuffers_[i], 0); // �ĊJ

        // �e���b�V���̕`����s��
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        d3d.Context()->IASetVertexBuffers(0, 1, &meshVertexBuffers_[i], &stride, &offset); // ���b�V�����Ƃ̒��_�o�b�t�@
        d3d.Context()->IASetIndexBuffer(meshIndexBuffers_[i], DXGI_FORMAT_R32_UINT, 0); // ���b�V�����Ƃ̃C���f�b�N�X�o�b�t�@

        d3d.Context()->DrawIndexed(meshes_[i].Indices.size(), 0, 0); // ���b�V�����Ƃ̕`��
    }
}
void Quad::Release()
{
    for (auto& buffer : meshVertexBuffers_) {
        SAFE_RELEASE(buffer);
    }
    meshVertexBuffers_.clear();

    for (auto& buffer : meshIndexBuffers_) {
        SAFE_RELEASE(buffer);
    }
    meshIndexBuffers_.clear();

    for (auto& buffer : meshConstantBuffers_) {
        SAFE_RELEASE(buffer);
    }
    meshConstantBuffers_.clear();
}
