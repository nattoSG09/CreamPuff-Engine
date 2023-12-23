#include "Model.h"
#include "AssimpLoader.h" 

bool Model::Load(string _filePath)
{
	AssimpLoader al{};
	al.Load(_filePath, meshes_);

	for (const Mesh& mesh : meshes_) {
        // ���_�o�b�t�@�𐶐�
        if (InitVertex(mesh) == false)return false;

        // �C���f�b�N�X�o�b�t�@�𐶐�
        if (InitIndex(mesh) == false)return false;

        // �R���X�^���g�o�b�t�@�𐶐�
        if (InitConstantBuffer() == false)return false;

	}
	return true;
}

void Model::Draw(Transform _transform)
{
    Direct3D& d3d = Direct3D::GetInstance();
    for (int i = 0; i < meshes_.size(); ++i) {

        // �e���b�V�����ƂɈقȂ�r���[�s���ˉe�s��Ȃǂ̏���ݒ肷��
        XMVECTOR position = { 0, 3, 7, 0 };
        XMVECTOR target = { 0, 2, 0, 0 };
        XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0)); // ���b�V�����Ƃ̃r���[�s��
        XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1280.0f / 720.0f, 0.1f, 1000.0f); // ���b�V�����Ƃ̎ˉe�s��

        CONSTANT_BUFFER cb = {};
        cb.matWVP = XMMatrixTranspose(_transform.WoaldMatrix() * view * proj);
        cb.matNormal = XMMatrixTranspose(_transform.NormalMatrix());
        cb.diffuseColor = meshes_[i].material.diffuse;

        D3D11_MAPPED_SUBRESOURCE pdata;
        d3d.Context()->Map(meshConstantBuffers_[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); // GPU����̃f�[�^�A�N�Z�X���~�߂�
        memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb)); // �f�[�^��l�𑗂�
        d3d.Context()->Unmap(meshConstantBuffers_[i], 0); // �ĊJ

        // �e���b�V���̕`����s��
        UINT stride = sizeof(Vertex);
        UINT offset = 0;

        //���_�o�b�t�@���Z�b�g
        d3d.Context()->IASetVertexBuffers(0, 1, &meshVertexBuffers_[i], &stride, &offset);

        //�C���f�b�N�X�o�b�t�@���Z�b�g
        d3d.Context()->IASetIndexBuffer(meshIndexBuffers_[i], DXGI_FORMAT_R32_UINT, 0);

        // ���b�V�����Ƃ̃R���X�^���g�o�b�t�@���Z�b�g
        d3d.Context()->VSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // ���_�V�F�[�_�[�p    
        d3d.Context()->PSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // �s�N�Z���V�F�[�_�[�p

        d3d.Context()->DrawIndexed(meshes_[i].indices.size(), 0, 0); // ���b�V�����Ƃ̕`��
    }
}

bool Model::InitVertex(const Mesh& _mesh)
{
    Direct3D& d3d = Direct3D::GetInstance();

    // ���_�o�b�t�@�𐶐�����
    ID3D11Buffer* meshVertexBuffer;
    D3D11_BUFFER_DESC bd_vertex = {};
    bd_vertex.ByteWidth = sizeof(Vertex) * _mesh.vertices.size();
    bd_vertex.Usage = D3D11_USAGE_DEFAULT;
    bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd_vertex.CPUAccessFlags = 0;
    bd_vertex.MiscFlags = 0;
    bd_vertex.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA data_vertex = {};
    data_vertex.pSysMem = _mesh.vertices.data();
    if (FAILED(d3d.Device()->CreateBuffer(&bd_vertex, &data_vertex, &meshVertexBuffer))) {
#ifdef _DEBUG
        MessageBox(NULL,"���_�o�b�t�@�̐����Ɏ��s���܂���","�G���[",MB_OK);
#endif // _DEBUG
       return false;
    }

    // ���_�o�b�t�@��z��ɒǉ�
    meshVertexBuffers_.push_back(meshVertexBuffer);
    return true;
}

bool Model::InitIndex(const Mesh& _mesh)
{
    Direct3D& d3d = Direct3D::GetInstance();

    // �C���f�b�N�X�o�b�t�@�𐶐�����
    ID3D11Buffer* meshIndexBuffer;
    D3D11_BUFFER_DESC bd_index = {};
    bd_index.Usage = D3D11_USAGE_DEFAULT;
    bd_index.ByteWidth = sizeof(uint32_t) * _mesh.indices.size();
    bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd_index.CPUAccessFlags = 0;
    bd_index.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = _mesh.indices.data();
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;
    if (FAILED(d3d.Device()->CreateBuffer(&bd_index, &InitData, &meshIndexBuffer))) {
#ifdef _DEBUG
        MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐����Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
        return false;
    }

    // �C���f�b�N�X�o�b�t�@��z��ɒǉ�
    meshIndexBuffers_.push_back(meshIndexBuffer);
    return true;
}

bool Model::InitConstantBuffer()
{
    Direct3D& d3d = Direct3D::GetInstance();

    // �R���X�^���g�o�b�t�@�̍쐬
    ID3D11Buffer* meshConstantBuffer;
    D3D11_BUFFER_DESC cb = {};
    cb.ByteWidth = sizeof(CONSTANT_BUFFER);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    if (FAILED(d3d.Device()->CreateBuffer(&cb, nullptr, &meshConstantBuffer))) {
#ifdef _DEBUG
        MessageBox(NULL, "�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
        return false;
    }

    // �쐬�����R���X�^���g�o�b�t�@��z��ɒǉ�
    meshConstantBuffers_.push_back(meshConstantBuffer);
    return true;
}
