#include "AssimpLoader.h"
#include <Windows.h>
#include <filesystem>

// assimp�֘A�f�[�^�̃C���N���[�h
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool AssimpLoader::Load(string _fileName, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV)
{
// �t�@�C����ǂݍ��� //
    Assimp::Importer importer;
    int flags = 0;
    InitFlags(flags);
    const aiScene* scene = importer.ReadFile(_fileName, flags);

#ifdef _DEBUG
    if (scene == nullptr) {
        MessageBox(NULL, importer.GetErrorString(), "���s", MB_OK); return false;
    }
#endif // _DEBUG

// ���f����ǂݍ��� //
    _meshes.clear();
    _meshes.resize(scene->mNumMeshes);

    for (int i = 0; i < scene->mNumMeshes; ++i){
        LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV);
        LoadTexture(_fileName, _meshes[i], scene->mMaterials[i]);
    }
    scene = nullptr;
    return true;
}

void AssimpLoader::InitFlags(int& _flags)
{
    _flags |= aiProcess_Triangulate;             // �|���S�������ׂĎO�p�`�ɕϊ�
    _flags |= aiProcess_PreTransformVertices;    // ���f���̒��_�����[���h��Ԃɕϊ�
    _flags |= aiProcess_CalcTangentSpace;        // �ڋ�Ԃ��v�Z
    _flags |= aiProcess_GenSmoothNormals;        // �X���[�Y�Ȗ@�����v�Z
    _flags |= aiProcess_GenUVCoords;             // UV���W�𐶐�
    _flags |= aiProcess_RemoveRedundantMaterials;// �s�v�ȃ}�e���A�����폜
    _flags |= aiProcess_OptimizeMeshes;          // ���b�V�����œK��
}

void AssimpLoader::LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV)
{
    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);
    _dst.Vertices.resize(_src->mNumVertices);

    for (unsigned int i = 0; i < _src->mNumVertices; ++i) {
        
// ���_�����i�[ //
        auto pos = &(_src->mVertices[i]);
        auto nor = &(_src->mNormals[i]);
        auto uv = (_src->HasTextureCoords(0)) ? &(_src->mTextureCoords[0][i]) : &zero3D;
        auto tan = (_src->HasTangentsAndBitangents()) ? &(_src->mTangents[i]) : &zero3D;
        auto col = (_src->HasVertexColors(0)) ? &(_src->mColors[0][i]) : &zeroColor;

        // ���]�I�v�V��������������UV�𔽓]������
        if (_inverseU)uv->x = 1 - uv->x;
        if (_inverseV)uv->y = 1 - uv->y;

        Vertex vertex = {};
        vertex.Position = DirectX::XMFLOAT3(-pos->x, pos->y, pos->z);
        vertex.Normal = DirectX::XMFLOAT3(nor->x, nor->y, nor->z);
        vertex.UV = DirectX::XMFLOAT2(uv->x, uv->y);
        vertex.Tangent = DirectX::XMFLOAT3(tan->x, tan->y, tan->z);
        vertex.Color = DirectX::XMFLOAT4(col->r, col->g, col->b, col->a);
        _dst.Vertices[i] = vertex;

// �C���f�b�N�X�����i�[ //
        _dst.Indices.resize(_src->mNumFaces * 3);
        for (auto i = 0u; i < _src->mNumFaces; ++i)
        {
            const auto& face = _src->mFaces[i];

            _dst.Indices[i * 3 + 0] = face.mIndices[0];
            _dst.Indices[i * 3 + 1] = face.mIndices[1];
            _dst.Indices[i * 3 + 2] = face.mIndices[2];
        }
    }
}

void AssimpLoader::LoadTexture(const string _fileName, Mesh& _dst, const aiMaterial* _src)
{
    aiVector3D temp = {};
    aiString path;
    _src->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    auto x = _src->GetTextureCount(aiTextureType_DIFFUSE);
    
    if (_src->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS){

        //���݂̃J�����g�f�B���N�g�����擾
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //������fileName����f�B���N�g���������擾
        char dir[MAX_PATH];
        _splitpath_s(_fileName.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);

        _dst.DiffuseMap = dir + string(path.C_Str());
    }
    else _dst.DiffuseMap.clear();
}
