#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
using namespace DirectX;
using std::vector;
using std::string;

struct aiScene;
struct aiMesh;
struct aiMaterial;

// ���_���-�\����
struct Vertex{
    XMFLOAT3 Position; // �ʒu���W
    XMFLOAT3 Normal; // �@��
    XMFLOAT2 UV; // uv���W
    XMFLOAT3 Tangent; // �ڋ��
    XMFLOAT4 Color; // ���_�F
};

// ���b�V�����-�\����
struct Mesh{
    vector<Vertex> Vertices; // ���_�f�[�^�̔z��
    vector<uint32_t> Indices; // �C���f�b�N�X�̔z��
    vector<string> DiffuseMaps; // �e�N�X�`���̃t�@�C���p�X
};

/// <summary>
/// assimp�ɂ�郂�f���Ɋ֘A����f�[�^�����[�h����
/// </summary>
class AssimpLoader
{
public:
    bool Load(string _fileName,vector<Mesh>& _meshs,bool _inverseU,bool _inverseV);
private:
    void InitFlags(int& _flags);
    void LoadMesh(Mesh& _dst, const aiMesh* _src, bool _inverseU, bool _inverseV);
    void LoadTexture(const string _filename, Mesh& _dst, const aiMaterial* _src);
};

