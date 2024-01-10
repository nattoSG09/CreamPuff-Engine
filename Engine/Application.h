#pragma once
#include "Windows/WindowManager.h"
#include "RootObject.h"

/// <summary>
/// �A�v���P�[�V�������Ǘ�����N���X
/// </summary>
class Application
{
	RootObject* pRootObject;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Application();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Application();

	/// <summary>
	/// �A�v���P�[�V�����̏������������s��
	/// </summary>
	/// <param name="_hInstance">�C���X�^���X�n���h��</param>
	/// <param name="_nCmdShow">�E�B���h�E�̕\�����</param>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);

	/// <summary>
	/// �A�v���P�[�V�����̍X�V�������s��
	/// </summary>
	void Update();

	/// <summary>
	/// �A�v���P�[�V�����̊J���������s��
	/// </summary>
	void Release();

	/// <summary>
	/// �E�B���h�E�v���V�[�W���\
	/// </summary>
	/// <param name="_hWnd">�E�B���h�E�̃n���h��</param>
	/// <param name="_msg">�E�B���h�E�v���V�[�W���\�ɑ����郁�b�Z�[�W</param>
	/// <param name="_wParam">���b�Z�[�W�Ɋ֘A����ǉ����</param>
	/// <param name="_lParam">���b�Z�[�W�Ɋ֘A����ǉ����</param>
	/// <returns>LRESULT�^�̒l</returns>
	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);


private:
	int fps_;
	bool ShouldUpdate();
	void DisplayFPS(DWORD& _nowTime, DWORD& _startTime);
};
