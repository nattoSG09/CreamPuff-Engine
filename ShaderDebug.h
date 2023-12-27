#pragma once
#include "Shader.h"
class ShaderDebug : public Shader
{
public:
	ShaderDebug();

private:
	void InitVertexLayout() override;
	void InitRasterizerState() override;
};

