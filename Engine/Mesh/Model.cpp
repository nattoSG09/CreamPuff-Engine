#include "Model.h"
#include "AssimpLoader.h" 
#include "../Direct3D/CameraManager.h"

bool Model::Load(string _filePath, bool _inverseU, bool _inverseV)
{
	AssimpLoader al{};
	al.Load(_filePath, meshes_, _inverseU, _inverseV);

	for (const Mesh& mesh : meshes_) {
        // 頂点バッファを生成
        if (InitVertex(mesh) == false)return false;

        // インデックスバッファを生成
        if (InitIndex(mesh) == false)return false;

        // コンスタントバッファを生成
        if (InitConstantBuffer() == false)return false;
	}
	return true;
}

bool Model::Load(string _filePath)
{
    return Load(_filePath,false,false);
}

void Model::Draw(Transform _transform)
{
    Direct3D& d3d = Direct3D::GetInstance();
    for (int i = 0; i < meshes_.size(); ++i) {

        // 各メッシュごとに異なるビュー行列や射影行列などの情報を設定する
        /*XMVECTOR position = { 0, 140, 100, 0 };
        XMVECTOR target = { 0, 120, 0, 0 };*/
        XMVECTOR position = { 0, 3, 7, 0 };
        XMVECTOR target = { 0, 0, 0, 0 };

        CameraManager& cm = CameraManager::GetInstance();
        XMMATRIX view = cm.GetCurrentCamera()->GetViewMatrix();
        XMMATRIX proj = cm.GetCurrentCamera()->GetProjectionMatrix();

        Constant_Buffer cb = {};
        cb.matW = XMMatrixTranspose(_transform.WoaldMatrix());
        cb.matWVP = XMMatrixTranspose(_transform.WoaldMatrix() * view * proj);
        cb.matNormal = XMMatrixTranspose(_transform.NormalMatrix());
        cb.diffuseColor = meshes_[i].material.diffuse;
        cb.ambientColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.f);
        cb.hasTexture = meshes_[i].material.hasTexture;


        D3D11_MAPPED_SUBRESOURCE pdata;
        d3d.Context()->Map(meshConstantBuffers_[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata); // GPUからのデータアクセスを止める
        memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb)); // データを値を送る
        d3d.Context()->Unmap(meshConstantBuffers_[i], 0); // 再開

        // 各メッシュの描画を行う
        UINT stride = sizeof(Vertex);
        UINT offset = 0;

        //頂点バッファをセット
        d3d.Context()->IASetVertexBuffers(0, 1, &meshVertexBuffers_[i], &stride, &offset);

        //インデックスバッファをセット
        d3d.Context()->IASetIndexBuffer(meshIndexBuffers_[i], DXGI_FORMAT_R32_UINT, 0);

        // メッシュごとのコンスタントバッファをセット
        d3d.Context()->VSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // 頂点シェーダー用    
        d3d.Context()->PSSetConstantBuffers(0, 1, &meshConstantBuffers_[i]); // ピクセルシェーダー用

        if (meshes_[i].material.hasTexture) {
            for (auto diffuseTexture : meshes_[i].material.diffuseTextures) {
                //サンプラーをセット
                ID3D11SamplerState* pSampler = diffuseTexture->GetSampler();
                d3d.Context()->PSSetSamplers(0, 1, &pSampler);

                //シェーダーリソースビューをセット
                ID3D11ShaderResourceView* pSRV = diffuseTexture->GetSRV();
                d3d.Context()->PSSetShaderResources(0, 1, &pSRV);
            }
        }
        
        d3d.Context()->DrawIndexed(meshes_[i].indices.size(), 0, 0); // メッシュごとの描画
    }
}

bool Model::InitVertex(const Mesh& _mesh)
{
    Direct3D& d3d = Direct3D::GetInstance();

    // 頂点バッファを生成する
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
        MessageBox(NULL,"頂点バッファの生成に失敗しました","エラー",MB_OK);
#endif // _DEBUG
       return false;
    }

    // 頂点バッファを配列に追加
    meshVertexBuffers_.push_back(meshVertexBuffer);
    return true;
}

bool Model::InitIndex(const Mesh& _mesh)
{
    Direct3D& d3d = Direct3D::GetInstance();

    // インデックスバッファを生成する
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
        MessageBox(NULL, "インデックスバッファの生成に失敗しました", "エラー", MB_OK);
#endif // _DEBUG
        return false;
    }

    // インデックスバッファを配列に追加
    meshIndexBuffers_.push_back(meshIndexBuffer);
    return true;
}

bool Model::InitConstantBuffer()
{
    Direct3D& d3d = Direct3D::GetInstance();

    // コンスタントバッファの作成
    ID3D11Buffer* meshConstantBuffer;
    D3D11_BUFFER_DESC cb = {};
    cb.ByteWidth = sizeof(Constant_Buffer);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    if (FAILED(d3d.Device()->CreateBuffer(&cb, nullptr, &meshConstantBuffer))) {
#ifdef _DEBUG
        MessageBox(NULL, "コンスタントバッファの生成に失敗しました", "エラー", MB_OK);
#endif // _DEBUG
        return false;
    }

    // 作成したコンスタントバッファを配列に追加
    meshConstantBuffers_.push_back(meshConstantBuffer);
    return true;
}
