//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D g_texture : register(t0); //�e�N�X�`���[
SamplerState g_sampler : register(s0); //�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matW;
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
    float4x4	matNormal;		// �@���s��
								// �����_�̖@���x�N�g����ϊ����邽�߂Ɏg�p����A���̔��˂�A�e�Ȃǂ̐������`����s������
	float4		diffuseColor;	// �f�B�q���[�Y�J���[
	float4		ambientColor;	// �A���r�G���g�J���[
	float4		specularColor;	// �X�y�L�����[�J���[
	float		shininess;		// �P�x
    bool		hasTexture;		// �e�N�X�`���̗L��
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,
										float3 tangent : TANGENT,float4 color :COLOR)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
    outData.color = color;
    outData.uv = uv;
	
	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
    //float lv = 1000;
    //inData.uv = floor(inData.uv * lv) / lv;
    return hasTexture ? g_texture.Sample(g_sampler, inData.uv) : diffuseColor;
}