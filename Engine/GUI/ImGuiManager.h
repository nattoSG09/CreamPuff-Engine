#pragma once

//ImGui�֘A�f�[�^�̃C���N���[�h
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "../Windows/Window.h"

/// <summary>
/// ImGui���Ǘ�����N���X
/// </summary>
namespace ImGuiManager 
{
	/// <summary>
	/// ���������s��
	/// </summary>
	/// <param name="windowHandle">�E�B���h�E�n���h��</param>
	/// <param name="device">Direct3D11�f�o�C�X�ւ̃|�C���^</param>
	/// <param name="context">Direct3D�R���e�L�X�g�ւ̃|�C���^</param>
	void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context);

	/// <summary>
	/// �`����s��(���݂����Ă��Ȃ�����)
	/// </summary>
	void Draw();

	/// <summary>
	/// �t���[�����J�n����
	/// </summary>
	void BeginFlame();

	/// <summary>
	/// �t���[�����I������
	/// </summary>
	void EndFlame();
	
	/// <summary>
	/// ImGui���\�[�X���J������
	/// </summary>
	void ShutDown();

}