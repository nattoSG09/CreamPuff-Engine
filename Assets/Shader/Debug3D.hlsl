// 定数バッファ(CPU側からの値受け取り場)
cbuffer global
{
	float4x4	matW;		// ワールド行列
	float4x4	matWVP;		// ワールド・ビュー・プロジェクション行列
};

// 頂点シェーダ
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	return mul(pos, matWVP);
}

// ピクセルシェーダ
float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return float4(0.6, 0.6, 0.6, 0.3);
}