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
	float4x4	matWVP;		
	float4x4	matNormal;	
	float4		diffuseColor;	
	bool		hasTexture;		
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	
	float4 color : COLOR;
	float2 uv : TEXCOORD;

	//float4 eyev : POSITION;
	//float4 normal : NORMAL;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,
	float3 tangent : TANGENT, float4 color : COLOR)
{
	VS_OUT outData;

	outData.pos = mul(pos, matWVP);
	outData.color = color;
	outData.uv = uv;

	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	//float d = abs(dot(normalize(inData.eyev),inData.normal));

	return hasTexture ? g_texture.Sample(g_sampler, inData.uv) : diffuseColor;
}

