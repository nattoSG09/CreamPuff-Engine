#include "EditorWindow.h"

EditorWindow::EditorWindow()
{
}

EditorWindow::EditorWindow(const string _name, const int _height, const int _width)
	:Window(_name,_height,_width)
{
}

EditorWindow::~EditorWindow()
{
}

bool EditorWindow::Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc)
{
    WNDCLASSEX wc = {};
    InitWindowClass(wc, _hInstance, _wndProc);

    int winH, winW;
    CalcWindowSize(winH, winW);

    hWnd_ = CreateWindow(
        name_.c_str(),         //�E�B���h�E�N���X��
        name_.c_str(),     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,                 //�E�B���h�E��
        winH,                 //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        _hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );

    if (hWnd_ == nullptr) return false;

    ShowWindow(hWnd_, _nCmdShow);
	return true;
}

void EditorWindow::InitWindowClass(WNDCLASSEX& _wc, HINSTANCE _hInstance,WndProcType _wndProc)
{
    _wc.cbSize = sizeof(WNDCLASSEX);
    _wc.hInstance = _hInstance;
    _wc.lpszClassName = name_.c_str();
    _wc.lpfnWndProc = _wndProc;
    _wc.style = CS_VREDRAW | CS_HREDRAW;
    _wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    _wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    _wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    _wc.lpszMenuName = NULL;
    _wc.cbClsExtra = 0;
    _wc.cbWndExtra = 0;
    _wc.hbrBackground = CreateSolidBrush(RGB(10, 10, 10));

    RegisterClassEx(&_wc);
}

void EditorWindow::CalcWindowSize(int& _height, int& _width)
{
    RECT winRect = { 0, 0, width_, height_ };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    _width = winRect.right - winRect.left;     //�E�B���h�E��
    _height = winRect.bottom - winRect.top;     //�E�B���h�E����
}
