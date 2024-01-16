#pragma once
#include "Shader.h"

class ShaderNormalMap : public Shader
{
public:
	ShaderNormalMap();
private:
	void InitVertexLayout() override;
	void InitRasterizerState() override;
};

