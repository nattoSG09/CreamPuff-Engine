#include "AssimpLoader.h"

// assimp�֘A�f�[�^�̃C���N���[�h
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Windows.h>

namespace {
    string Directory(string _path) {
        //���݂̃J�����g�f�B���N�g�����擾
        char defaultCurrentDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

        //������fileName����f�B���N�g���������擾
        char dir[MAX_PATH];
        _splitpath_s(_path.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
        return dir;
    }
}

AssimpLoader::AssimpLoader()
{
}

AssimpLoader::~AssimpLoader()
{
}

bool AssimpLoader::Load(string _filePath, vector<Mesh>& _meshes)
{
    // �����ŏo����΁AUV�̔��]�̉ۂ����߂���...

    return Load(_filePath, _meshes,false,false);
}

bool AssimpLoader::Load(string _filePath, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV)
{
    // �t���O��������
    int flags = 0;
    InitFlags(flags);

    // �t�@�C�������[�h
    Assimp::Importer importer{};
    const aiScene* scene = importer.ReadFile(_filePath, flags);

    if (scene == nullptr) {
#ifdef _DEBUG
        MessageBox(NULL, importer.GetErrorString(), "�G���[", MB_OK);
#endif // _DEBUG
        return false;
    }

    _meshes.clear();
    _meshes.resize(scene->mNumMeshes);

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        // ���b�V���������...
        if (scene->HasMeshes()) {
            // ���b�V�������[�h����
            if (LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV) == false)return false;
        }
        // �}�e���A���������...
        if (scene->HasMaterials()) {
            // �}�e���A�������[�h����
            if (LoadMaterial(_filePath, _meshes[i].material, scene->mMaterials[i]) == false)return false;
        }
    }

    return false;
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

bool AssimpLoader::LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV)
{
    if (_src == nullptr)return false;

    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

    _dst.vertices.clear();
    _dst.vertices.resize(_src->mNumVertices);

    // ���_�����̈ʒu�E�@���EUV�E�ڋ�ԁE���_�F�E�C���f�b�N�X�����擾
    for (int i = 0; i < _src->mNumVertices; ++i) {
        aiVector3D* pos = &(_src->mVertices[i]);
        aiVector3D* nor = &(_src->mNormals[i]);
        aiVector3D* uv = (_src->HasTextureCoords(0)) ? &(_src->mTextureCoords[0][i]) : &zero3D;
        aiVector3D* tan = (_src->HasTangentsAndBitangents()) ? &(_src->mTangents[i]) : &zero3D;
        aiColor4D* col = (_src->HasVertexColors(0)) ? &(_src->mColors[0][i]) : &zeroColor;

        // ���]�I�v�V��������������UV�𔽓]������
        if (_inverseU)uv->x = 1 - uv->x;
        if (_inverseV)uv->y = 1 - uv->y;

        // ���_�����i�[
        Vertex vertex{};
        vertex.position = DirectX::XMFLOAT3(-pos->x, pos->y, pos->z);
        vertex.normal = DirectX::XMFLOAT3(nor->x, nor->y, nor->z);
        vertex.uv = DirectX::XMFLOAT2(uv->x, uv->y);
        vertex.tangent = DirectX::XMFLOAT3(tan->x, tan->y, tan->z);
        vertex.color = DirectX::XMFLOAT4(col->r, col->g, col->b, col->a);
        _dst.vertices[i] = vertex;

        // �C���f�b�N�X�����擾
        _dst.indices.resize(_src->mNumFaces * 3);
        for (auto i = 0u; i < _src->mNumFaces; ++i) {
            const auto& face = _src->mFaces[i];
            _dst.indices[i * 3 + 0] = face.mIndices[0];
            _dst.indices[i * 3 + 1] = face.mIndices[1];
            _dst.indices[i * 3 + 2] = face.mIndices[2];
        }
    }

    if (_dst.vertices.empty())return false;
    if (_dst.indices.empty())return false;
    return true;
}

bool AssimpLoader::LoadMaterial(string _filePath, Material& _dst, const aiMaterial* _src)
{
    if (_src == nullptr)return false;

    // �f�B�q���[�Y�J���[���擾
    aiColor3D diffuseColor(0.f, 0.f, 0.f);
    if (AI_SUCCESS == _src->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
        _dst.diffuse = XMFLOAT4(diffuseColor.r, diffuseColor.g, diffuseColor.b, 0.f);
    }

    //�e�N�X�`�������擾
    if (LoadTexture(_filePath,_dst, _src)) _dst.hasTexture = true;
    else _dst.hasTexture = false;

    return true;
}

bool AssimpLoader::LoadTexture(string _filePath,Material& _dst, const aiMaterial* _src)
{
    bool ret = false;

    // �f�B�q���[�Y�e�N�X�`�����擾�����[�h
    _dst.diffuseTextures.resize(_src->GetTextureCount(aiTextureType_DIFFUSE));
    for (int i = 0; i < _src->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
        aiString path;
        if (_src->GetTexture(aiTextureType_DIFFUSE, i, &path) == AI_SUCCESS) {
            
            _dst.diffuseTextures[i] = new Texture;
            _dst.diffuseTextures[i]->Load(Directory(_filePath) + path.C_Str());
            ret = true;
        }
    }

    return ret;
}