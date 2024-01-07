#include "ModelManager.h"
#include "Engine/Global.h"

namespace ModelManager {
	vector<ModelData*> modelDatas;
}

int ModelManager::Load(string _filePath)
{
	return Load(_filePath,false,false);
}

int ModelManager::Load(string _filePath, bool _inverseU, bool _inverseV)
{
	ModelData* pData = new ModelData(_filePath);

	// 読み込み済みかどうかを確認する
	for (auto& mData : modelDatas) {
		if (mData->filePath == _filePath) {
			pData->pModel = mData->pModel; break;
		}
	}

	// 読み込んでいなければモデルを読み込む
	if (pData->pModel == nullptr) {
		pData->pModel = new Model;
		pData->pModel->Load(_filePath, _inverseU, _inverseV);
	}

	modelDatas.push_back(pData);
	return (int)modelDatas.size() - 1;
}

void ModelManager::SetTransform(int _hModel, Transform _transform)
{
	modelDatas[_hModel]->transform = _transform;
}

void ModelManager::Draw(int _hModel)
{
	modelDatas[_hModel]->pModel->Draw(modelDatas[_hModel]->transform);
}

void ModelManager::Release(int _hModel)
{
	if (_hModel < 0 || _hModel >= modelDatas.size() 
		|| modelDatas[_hModel] == nullptr)return;

	bool isReffered = false;
	for (int i = 0; i < modelDatas.size(); i++){
		//すでに開いている場合
		if (modelDatas[i] != nullptr && i != _hModel && modelDatas[i]->pModel == modelDatas[_hModel]->pModel){
			isReffered = true;break;
		}
	}

	//使ってなければモデル解放
	if (isReffered == false)SAFE_DELETE(modelDatas[_hModel]->pModel);
	SAFE_DELETE(modelDatas[_hModel]);
}

void ModelManager::AllRelease()
{
	for (int i = 0; i < modelDatas.size(); i++){
		if (modelDatas[i] != nullptr)Release(i);
	}
	modelDatas.clear();
}


