//------------------------------------------------------------
// @file		start.cpp
// @brief	最初のシーン
// @detail	起動直後に呼ばれるシーンの処理です
//------------------------------------------------------------
#include "start.h"
#include "system/manager.h"

// シーンのインクルード
#include "title.h"

//=============================================================
// 初期化
//=============================================================
void StartScene::Init()
{
	// シーンマネージャーを取得する
	auto sceneManager = Manager::GetInstance()->GetSceneManager();

	// シーンの登録
	sceneManager->RegisterScene<TitleScene>();

	// 遷移
	sceneManager->SetScene<TitleScene>();
}
