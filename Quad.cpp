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

    // モデルをロード
    AssimpLoader al;
    al.Load("Assets/Alicia/FBX/Alicia_solid_MMD.FBX", meshes_, true, false);

    for (const auto& mesh : meshes_) {
        // 頂点バッファを用意
        vertices_ = mesh.Vertices;

        // 頂点バッファを生成する
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

        // 頂点バッファを配列に追加
        meshVertexBuffers_.push_back(meshVertexBuffer);

        // インデックスバッファを用意
        indices_ = mesh.Indices;

        // インデックスバッファを生成する
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

        // インデックスバッファを配列に追加
        meshIndexBuffers_.push_back(meshIndexBuffer);

        // コンスタントバッファの作成
        ID3D11Buffer* meshConstantBuffer;
        D3D11_BUFFER_DESC cb = {};
        cb.ByteWidth = sizeof(CONSTANT_BUFFER);
        cb.Usage = D3D11_USAGE_DYNAMIC;
        cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        cb.MiscFlags = 0;
        cb.StructureByteStride = 0;
        d3d.Device()->CreateBuffer(&cb, nullptr, &meshConstantBuffer);

        // 作成したコンスタントバッファを配列に追加
        meshConstantBuffers_.push_back(meshConstantBuffer);
    }
}

void Quad::Draw()
{
    Direct3D& d3d = Direct3D::GetInstance();

    for (int i = 0; i < meshes_.size(); ++i) {
        // メッシュごとのコンスタントバッファをセット
        d3d.Context()->VSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // 頂点シェーダー用    
        d3d.Context()->PSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // ピクセルシェーダー用

        // 各メッシュごとに異なるビュー行列や射影行列などの情報を設定する
        XMVECTOR position = { 0, 120, 75, 0 };
        XMVECTOR target = { 0, 120, 0, 0 };
        XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0)); // メッシュごとのビュー行列
        XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1280.0f / 720.0f, 0.1f, 100.0f); // メッシュごとの射影行列

        CONSTANT_BUFFER cb = {};
        cb.matWVP = XMMatrixTranspose(view * proj);

        D3D11_MAPPED_SUBRESOURCE pdata;
        d3d.Context()->Map(meshConstantBuffers_[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); // GPUからのデータアクセスを止める
        memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb)); // データを値を送る
        d3d.Context()->Unmap(meshConstantBuffers_[i], 0); // 再開

        // 各メッシュの描画を行う
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        d3d.Context()->IASetVertexBuffers(0, 1, &meshVertexBuffers_[i], &stride, &offset); // メッシュごとの頂点バッファ
        d3d.Context()->IASetIndexBuffer(meshIndexBuffers_[i], DXGI_FORMAT_R32_UINT, 0); // メッシュごとのインデックスバッファ

        d3d.Context()->DrawIndexed(meshes_[i].Indices.size(), 0, 0); // メッシュごとの描画
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
