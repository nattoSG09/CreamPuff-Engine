#pragma once
#include <string>
#include <Windows.h>

using std::string;
typedef LRESULT(CALLBACK* WndProcType)(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// �E�B���h�E����̒��ۉ��N���X
/// </summary>
class Window
{
protected:
	HWND hWnd_;/*�E�B���h�E�n���h��*/
	int height_;/*�E�B���h�E�̍���*/
	int width_;/*�E�B���h�E�̕�*/
	string name_;/*�E�B���h�E�̖��O*/

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Window();

	/// <summary>
	/// �����t���R���X�g���N�^
	/// </summary>
	/// <param name="_name">�E�B���h�E�̖��O</param>
	/// <param name="_height">�E�B���h�E�̍���</param>
	/// <param name="_width">�E�B���h�E�̕�</param>
	Window(const string _name,const int _height,const int _width);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Window();

	/// <summary>
	/// �E�B���h�E�̏��������s��
	/// </summary>
	/// <param name="_hInstance">�C���X�^���X�n���h��</param>
	/// <param name="_nCmdShow">�E�B���h�E�̕\�����</param>
	/// <param name="_wndProc">�E�B���h�E�v���V�[�W���\</param>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	virtual bool Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc) = 0;
	
	/// <summary>
	/// �E�B���h�E��\������
	/// </summary>
	/// <param name="_nCmdShow"></param>
	void Show(int _nCmdShow);

// �Q�b�^�[�E�Z�b�^�[ //
	HWND WindowHandle() const { return hWnd_; }
	int Height() const { return height_; }
	void SetHeight(int _height) { height_ = _height; }
	int Width() const { return width_; }
	void SetWidth(int _width) { width_ = _width; }
	string Name() const{ return name_; }
	void SetName(string _name) { name_ = _name; }
};

