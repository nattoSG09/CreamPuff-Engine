#pragma once
#include <string>
using std::string;

class Shader
{
public:
	Shader(string _filePath);
	~Shader();
	bool Initialize();

private:
	bool CompileVertexShader();
	bool CompilePixelShader();
	bool CreateRasterizerState();
};

