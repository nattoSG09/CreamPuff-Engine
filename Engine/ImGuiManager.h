#pragma once

//ImGui関連データのインクルード
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "Windows/Window.h"

namespace ImGuiManager 
{
	// 初期化
	void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context);

	// 描画
	void Draw();

	// フレーム開始
	void BeginFlame();

	// フレーム終了
	void EndFlame();
	
	// 解放
	void ShutDown();
}