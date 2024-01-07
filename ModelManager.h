#pragma once
#include "Engine/Mesh/Model.h"
#include "Engine/Components/Transform.h"

#include <string>
using std::string;

namespace ModelManager
{
	// ���f�����-�\����
	struct ModelData {
		Model*		pModel;		// �A�h���X
		string		filePath;	// �t�@�C���p�X
		Transform	transform;	// �ϊ��s��

		// �\���̃R���X�g���N�^
		ModelData(string _filePath):pModel(nullptr),filePath(_filePath),transform() {}
	};

	int Load(string _filePath);
	int Load(string _filePath,bool _inverseU,bool _inverseV);

	void SetTransform(int _hModel,Transform _transform);
	void Draw(int _hModel);
	void Release(int _hModel);
	void AllRelease();
};

