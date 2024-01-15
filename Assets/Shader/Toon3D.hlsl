//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0); //テクスチャー
SamplerState g_sampler : register(s0); //サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;		
	float4x4	matNormal;	
	float4		diffuseColor;	
	bool		hasTexture;		
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	
	float4 color : COLOR;
	float2 uv : TEXCOORD;

	//float4 eyev : POSITION;
	//float4 normal : NORMAL;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,
	float3 tangent : TANGENT, float4 color : COLOR)
{
	VS_OUT outData;

	outData.pos = mul(pos, matWVP);
	outData.color = color;
	outData.uv = uv;

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	//float d = abs(dot(normalize(inData.eyev),inData.normal));

	return hasTexture ? g_texture.Sample(g_sampler, inData.uv) : diffuseColor;
}

