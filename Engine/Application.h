#pragma once
#include "Windows/WindowManager.h"

class Quad;

class Application
{
	Quad* pQuad_;
public:
	Application();
	~Application();

	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);
	void Excute();
	void Release();
};

