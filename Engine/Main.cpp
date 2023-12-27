#include "Application.h"
#include "Global.h"

// �G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE _hInstance,HINSTANCE _hPrevInst,LPSTR _lpCmdLine,int _nCmdShow)
{
	Application* application = new Application;

	if (application->Initialize(_hInstance, _nCmdShow))
	{
		application->Update();
	}
	application->Release();
	SAFE_DELETE(application);

	return 0;
}
