#pragma once

//ImGui関連データのインクルード
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "../Windows/Window.h"

/// <summary>
/// ImGuiを管理するクラス
/// </summary>
namespace ImGuiManager 
{
	/// <summary>
	/// 初期化を行う
	/// </summary>
	/// <param name="windowHandle">ウィンドウハンドル</param>
	/// <param name="device">Direct3D11デバイスへのポインタ</param>
	/// <param name="context">Direct3Dコンテキストへのポインタ</param>
	void Initialize(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context);

	/// <summary>
	/// 描画を行う(現在つかっていないかも)
	/// </summary>
	void Draw();

	/// <summary>
	/// フレームを開始する
	/// </summary>
	void BeginFlame();

	/// <summary>
	/// フレームを終了する
	/// </summary>
	void EndFlame();
	
	/// <summary>
	/// ImGuiリソースを開放する
	/// </summary>
	void ShutDown();

}