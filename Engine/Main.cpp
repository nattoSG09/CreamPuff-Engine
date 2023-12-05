#include "Application.h"


int APIENTRY WinMain(HINSTANCE _hInstance,HINSTANCE _hPrevInst,LPSTR _lpCmdLine,int _nCmdShow)
{
	Application* application = new Application;
	if (application->Initialize(_hInstance, _nCmdShow))
	{
		application->Excute();
	}
	application->Release();

	delete application;
	return 0;
}
