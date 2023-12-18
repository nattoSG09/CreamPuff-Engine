#pragma once
#include <string>
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(string _fileName);
};

