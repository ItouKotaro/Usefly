//------------------------------------------------------------
// @file		start.cpp
// @brief	最初のシーン
// @detail	起動直後に呼ばれるシーンの処理です
//------------------------------------------------------------
#include "start.h"
#include "sysyem/manager.h"

// シーンのインクルード
#include "title.h"

//=============================================================
// 初期化
//=============================================================
void StartScene::Init()
{
	// シーンマネージャーを取得する
	auto sceneManager = Manager::getInstance()->getSceneManager();

	// シーンの登録
	sceneManager->registerScene<TitleScene>();

	// 遷移
	sceneManager->setScene<TitleScene>();
}
