#pragma once

//ImGui�֘A�f�[�^�̃C���N���[�h
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "Windows/Window.h"

namespace ImGuiManager 
{
	// ������
	void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context);

	// �`��
	void Draw();

	// �t���[���J�n
	void BeginFlame();

	// �t���[���I��
	void EndFlame();
	
	// ���
	void ShutDown();
}