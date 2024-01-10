#pragma once
#include "Component.h"


#include <DirectXMath.h>
using namespace DirectX;

class GameObject;

/// <summary>
/// Transform(変換行列)コンポーネント
/// </summary>
class Transform : public Component
{
public:
	XMFLOAT3 position_;		/*位置*/
	XMFLOAT4 rotate_;		/*方向*/
	XMFLOAT3 scale_;		/*拡大率*/

	Transform* pParent_;	/*親オブジェクトの変換行列*/

private:
	XMMATRIX matTranslate_;	/*移動行列*/
	XMMATRIX matRotate_;	/*回転行列*/
	XMMATRIX matScale_;		/*拡大行列*/

	XMVECTOR rotationAxis_;	/*任意の回転に必要な軸*/

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Transform(GameObject* _parent);

	Transform();

	/// <summary>
	/// 生成した変換行列を計算
	/// </summary>
	void Calclation();

// アクセス関数 //
	XMFLOAT3 GetPosition() { return position_; }
	void SetPosition(const XMFLOAT3 _position) { position_ = _position; }
	void SetPosition(float _x, float _y, float _z) { SetPosition(XMFLOAT3(_x, _y, _z)); }

	XMFLOAT4 GetRotate() { return rotate_; }
	void SetRotate(const XMFLOAT4 _rotate) { rotate_ = _rotate; }
	void SetRotate(float _x, float _y, float _z) { SetRotate(XMFLOAT4(_x, _y, _z,0.0f)); }
	void SetRotateAxis(XMVECTOR _rotationAxis) { rotationAxis_ = _rotationAxis; }
	

	XMFLOAT3 GetScale() { return scale_; }
	void SetScale(const XMFLOAT3 _scale) { scale_ = _scale; }
	void SetScale(float _x, float _y, float _z) { SetScale(XMFLOAT3(_x, _y, _z)); }

	/// <summary>
	/// ワールド行列を生成・取得を行う
	/// </summary>
	/// <returns>ワールド行列</returns>
	XMMATRIX WoaldMatrix();

	/// <summary>
	/// 法線行列を生成・取得を行う
	/// </summary>
	/// <returns>法線行列</returns>
	XMMATRIX NormalMatrix();
};

