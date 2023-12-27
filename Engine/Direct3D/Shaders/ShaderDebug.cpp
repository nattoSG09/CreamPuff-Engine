#include "ShaderDebug.h"

ShaderDebug::ShaderDebug()
	:Shader("Assets/Shader/Debug3D.hlsl")
{
}

void ShaderDebug::InitVertexLayout()
{
	vertexLayout_ = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
}

void ShaderDebug::InitRasterizerState()
{
	rasterizerStateDesc_.CullMode = D3D11_CULL_NONE;
	rasterizerStateDesc_.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerStateDesc_.FrontCounterClockwise = TRUE;
}
