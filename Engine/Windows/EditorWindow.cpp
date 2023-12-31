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
    // ウィンドウのクラスを設定・初期化
    WNDCLASSEX wc = {};
    InitWindowClass(wc, _hInstance, _wndProc);
    RegisterClassEx(&wc);

    // ウィンドウサイズを計算し取得
    int winH, winW;
    CalcWindowSize(winH, winW);

    // ウィンドウを作成
    hWnd_ = CreateWindow(
        name_.c_str(),          /*ウィンドウクラス名*/
        name_.c_str(),          /*タイトルバーに表示する内容*/
        WS_OVERLAPPEDWINDOW,    /*スタイル（普通のウィンドウ）*/
        CW_USEDEFAULT,          /*表示位置左（おまかせ）*/
        CW_USEDEFAULT,          /*表示位置上（おまかせ）*/
        winW,                   /*ウィンドウ幅*/
        winH,                   /*ウィンドウ高さ*/
        NULL,                   /*親ウインドウ（なし）*/
        NULL,                   /*メニュー（なし）*/
        _hInstance,             /*インスタンス*/
        NULL                    /*パラメータ（なし）*/
    );

    if (hWnd_ == nullptr) return false;
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
}

void EditorWindow::CalcWindowSize(int& _height, int& _width)
{
    // タイトルバー等により実際のサイズで出力できないことを
    // 回避する為に計算を行う
    RECT winRect = { 0, 0, width_, height_ };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    _width = winRect.right - winRect.left;
    _height = winRect.bottom - winRect.top;
}
