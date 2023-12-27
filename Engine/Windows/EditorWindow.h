#pragma once
#include "Window.h"

/// <summary>
/// �u�G�f�B�^�[�E�B���h�E�v�𑀍삷��N���X
/// </summary>
class EditorWindow : public Window
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EditorWindow();

	/// <summary>
	/// �����t���R���X�g���N�^
	/// </summary>
	/// <param name="_name">�E�B���h�E�̖��O</param>
	/// <param name="_height">�E�B���h�E�̍���</param>
	/// <param name="_width">�E�B���h�E�̕�</param>
	EditorWindow(const string _name, const int _height, const int _width);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EditorWindow();

	/// <summary>
	/// ���������s��
	/// </summary>
	/// <param name="_hInstance">�C���X�^���X�n���h��</param>
	/// <param name="_nCmdShow">�E�B���h�E�̕\�����</param>
	/// <param name="_wndProc">�E�B���h�E�v���V�[�W���\</param>
	/// <returns>����ɏ����������������� ture ��Ԃ�</returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc) override;

private:
	/// <summary>
	/// �E�B���h�E���̐ݒ�E���������s��
	/// </summary>
	/// <param name="_wc">�E�B���h�E�N���X�\���̂ւ̎Q��</param>
	/// <param name="_hInstance">�C���X�^���X�n���h��</param>
	/// <param name="_wndProc">�E�B���h�E�v���V�[�W��</param>
	void InitWindowClass(WNDCLASSEX& _wc, HINSTANCE _hInstance, WndProcType _wndProc);

	/// <summary>
	/// �E�B���h�E�T�C�Y�̌v�Z���s��
	/// </summary>
	/// <param name="_height">�E�B���h�E�̍���</param>
	/// <param name="_width">�E�B���h�E�̕�</param>
	void CalcWindowSize(int& _height, int& _width);
};