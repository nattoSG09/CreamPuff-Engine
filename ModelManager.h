#pragma once
#include "Engine/Mesh/Model.h"
#include "Engine/Components/Transform.h"

#include <string>
using std::string;

namespace ModelManager
{
	// モデル情報-構造体
	struct ModelData {
		Model*		pModel;		// アドレス
		string		filePath;	// ファイルパス
		Transform	transform;	// 変換行列

		// 構造体コンストラクタ
		ModelData(string _filePath):pModel(nullptr),filePath(_filePath),transform() {}
	};

	int Load(string _filePath);
	int Load(string _filePath,bool _inverseU,bool _inverseV);

	void SetTransform(int _hModel,Transform _transform);
	void Draw(int _hModel);
	void Release(int _hModel);
	void AllRelease();
};

