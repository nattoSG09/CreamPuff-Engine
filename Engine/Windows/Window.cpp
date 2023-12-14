#include "Window.h"

namespace DEFAULT{
	const string WIN_NAME = "window";
	const int WIN_HEIGHT = 600;
	const int WIN_WIDTH = 800;
}

Window::Window()
	:name_(DEFAULT::WIN_NAME),height_(DEFAULT::WIN_HEIGHT),width_(DEFAULT::WIN_WIDTH),hWnd_(0)
{
}

Window::Window(const string _name, const int _height, const int _width)
	:name_(_name),height_(_height),width_(_width),hWnd_(0)
{
}

Window::~Window()
{
}

void Window::Show(int _nCmdShow)
{
	ShowWindow(hWnd_, _nCmdShow);
}
