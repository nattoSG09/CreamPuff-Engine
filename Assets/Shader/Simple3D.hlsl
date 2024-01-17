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
	float4x4	matW;
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
    float4x4	matNormal;		// 法線行列
								// ※頂点の法線ベクトルを変換するために使用され、光の反射や陰影などの正しい描画を行うため
	float4		diffuseColor;	// ディヒューズカラー
	float4		ambientColor;	// アンビエントカラー
	float4		specularColor;	// スペキュラーカラー
	float		shininess;		// 輝度
    bool		hasTexture;		// テクスチャの有無
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,
										float3 tangent : TANGENT,float4 color :COLOR)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
    outData.color = color;
    outData.uv = uv;
	
	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    //float lv = 1000;
    //inData.uv = floor(inData.uv * lv) / lv;
    return hasTexture ? g_texture.Sample(g_sampler, inData.uv) : diffuseColor;
}