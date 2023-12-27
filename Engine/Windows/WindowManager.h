#pragma once
#include "Window.h"

#include <map>
using std::map;

/// <summary>
/// �E�B���h�E�Ǘ��N���X
/// </summary>
class WindowManager
{
private:
	map<string, Window*> windows_;/*�E�B���h�E���i�[����}�b�v*/

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WindowManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WindowManager();

public:
	/// <summary>
	/// WindowsManager�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>WindowsManager�̃C���X�^���X</returns>
	static WindowManager& GetInstance();

	/// <summary>
	/// �w�肳�ꂽ�L�[�ɑΉ�����E�B���h�E���擾����
	/// </summary>
	/// <param name="_key">�E�B���h�E�̃L�[</param>
	/// <returns>�w�肳�ꂽ�L�[�ɑΉ�����E�B���h�E</returns>
	Window* GetWindow(const string& _key);
	
	/// <summary>
	/// �ǉ����ꂽ���ׂẴE�B���h�E�̏��������s��
	/// </summary>
	/// <param name="_hInstance">�C���X�^���X�n���h��</param>
	/// <param name="_nCmdShow">�E�B���h�E�̕\�����</param>
	/// <param name="_wndProc">�E�B���h�E�v���V�[�W���\</param>
	/// <returns>����ɏ����������������� true ��Ԃ�</returns>
	bool InitWindows(HINSTANCE _hInstance, int _nCmdShow, WndProcType _wndProc);
	
	/// <summary>
	/// ���ׂẴE�B���h�E�̊J�����s��
	/// </summary>
	void ReleaseWindows();

	/// <summary>
	/// �E�B���h�E��ǉ�����
	/// </summary>
	/// <param name="_key">�E�B���h�E�̃L�[</param>
	/// <param name="_window">�ǉ�����E�B���h�E</param>
	void AddWindow(const string& _key, Window* _window);

	/// <summary>
	/// �o�^���ꂽ���ׂẴE�B���h�E���擾����
	/// </summary>
	/// <returns>�E�B���h�E���i�[����map</returns>
	map<string, Window*>& GetWindows() { return windows_; }

};

