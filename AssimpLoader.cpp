#include "AssimpLoader.h"
#include <Windows.h>

// assimp�֘A�f�[�^�̃C���N���[�h
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

AssimpLoader::AssimpLoader()
{
}

AssimpLoader::~AssimpLoader()
{
}

bool AssimpLoader::Load(string _fileName, vector<Mesh>& _meshes, bool _inverseU, bool _inverseV)
{
    // �t���O�̐ݒ�
    int flags = 0;
    InitFlags(flags);

    // �t�@�C�������[�h
    Assimp::Importer importer{};
    const aiScene* scene = importer.ReadFile(_fileName, flags);

    if (scene == nullptr) {
#ifdef _DEBUG
        MessageBox(NULL, importer.GetErrorString(), "�G���[", MB_OK);
#endif // _DEBUG
        return false;
    }

    //�z��T�C�Y�����Z�b�g���A���b�V���̐��Ɠ����T�C�Y�ɕύX
    _meshes.clear();
    _meshes.resize(scene->mNumMeshes);
    
    // ���b�V�����̃��b�V�����E�}�e���A�������擾
    for (int i = 0; i < scene->mNumMeshes; ++i) {
        // ���b�V�����̎擾
        if (scene->HasMeshes()) {
            if (LoadMesh(_meshes[i], scene->mMeshes[i], _inverseU, _inverseV) == false) {
#ifdef _DEBUG
                MessageBox(NULL, "���b�V���̃��[�h�Ɏ��s���܂���", "�G���[", MB_OK);
#endif // _DEBUG
                return false;
            }
        }

        // �}�e���A�����̎擾
//        if (scene->HasMaterials()) {
//            if (LoadMaterial(_fileName, _meshes[i].material, scene->mMaterials[i]) == false) {
//#ifdef _DEBUG
//                MessageBox(NULL, "�}�e���A���̃��[�h�Ɏ��s���܂���", "�G���[", MB_OK);
//#endif // _DEBUG
//                return false;
//            }
//        }
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

bool AssimpLoader::LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV)
{
    if (!_src) return false;

    // �O�ŏ��������邽�߂̕ϐ���p��
    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);
    
// ���_�����擾 //
    // �z��T�C�Y�����Z�b�g���A���_���Ɠ����T�C�Y�ɕύX
    _dst.vertices.clear();
    _dst.vertices.resize(_src->mNumVertices);

    // ���_�����̈ʒu�E�@���EUV�E�ڋ�ԁE���_�F�E�C���f�b�N�X�����擾
    for (unsigned int i = 0; i < _src->mNumVertices; ++i) {
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

// �C���f�b�N�X�����擾 //
        // �z��T�C�Y�����Z�b�g���A�C���f�b�N�X���Ɠ����T�C�Y�ɕύX
        _dst.indices.resize(_src->mNumFaces * 3);

        // �C���f�b�N�X�����i�[
        for (auto i = 0u; i < _src->mNumFaces; ++i){
            const auto& face = _src->mFaces[i];
            _dst.indices[i * 3 + 0] = face.mIndices[0];
            _dst.indices[i * 3 + 1] = face.mIndices[1];
            _dst.indices[i * 3 + 2] = face.mIndices[2];
        }
    }

    //�z���񂪋󂾂�����
    if (_dst.vertices.empty())return false;
    if (_dst.indices.empty())return false;
    return true;
}

bool AssimpLoader::LoadMaterial(string _fileName, Material& _dst, const aiMaterial* _src)
{
    if (!_src) return false;

    //�e�N�X�`�����擾
    if(LoadTexture(_dst, _src) == false)return false;
    
    //�f�B�q���[�Y�J���[���擾
    aiColor3D diffuseColor(0.f, 0.f, 0.f);
    if (AI_SUCCESS == _src->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
        // �f�B�t���[�Y�i�A���x�h�j�J���[���擾���A_dst �̑Ή����郁���o�ɃZ�b�g����
        _dst.diffuse = XMFLOAT4(diffuseColor.r, diffuseColor.g, diffuseColor.b,0.f);
    }

    return true;
}

bool AssimpLoader::LoadTexture(Material& _dst, const aiMaterial* _src)
{
    if (!_src) return false;

    //���݂̃J�����g�f�B���N�g�����擾
    char defaultCurrentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

    // �f�B�t���[�Y�e�N�X�`�����擾
    _dst.diffuseTextures.clear();
    _dst.diffuseTextures.resize(_src->GetTextureCount(aiTextureType_DIFFUSE));
    for (int i = 0; i < _src->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
        aiString texturePath;
        if (_src->GetTexture(aiTextureType_DIFFUSE, i, &texturePath) == AI_SUCCESS) {

            //������fileName����f�B���N�g���������擾
            char dir[MAX_PATH];
            _splitpath_s(texturePath.C_Str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);

            Texture* texture = new Texture;
            if (texture->Load(dir + string(texturePath.C_Str())) == false)return false;
            _dst.diffuseTextures[i] = texture;
        }
    }

    return true;
}
