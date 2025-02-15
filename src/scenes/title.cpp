//------------------------------------------------------------
// @file		title.cpp
// @brief	タイトルシーン
//------------------------------------------------------------
#include "title.h"

#include "components/3d/model.h"

//=============================================================
// 初期化
//=============================================================
void TitleScene::Init()
{
	// モデルを作成する
	GameObject* model = new GameObject("TestModel");
	model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");


}
