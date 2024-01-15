#pragma once
#include "Shader.h"

class ShaderToon : public Shader
{
public:
	ShaderToon();
private:
	void InitVertexLayout() override;
	void InitRasterizerState() override;
};

