#pragma once
#include "Shader.h"

class Shader3D : public Shader
{
public:
	Shader3D();

private:
	void InitVertexLayout() override;
	void InitRasterizerState() override;
};

