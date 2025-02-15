//------------------------------------------------------------
// @file		scene.cpp
// @brief	シーン
// @detail	シーンの管理を行います
//------------------------------------------------------------
#include "scene.h"
#include "scenes/start.h"

//=============================================================
// 初期化
//=============================================================
void SceneManager::Init()
{
	// 最初のシーンを登録する
	this->registerScene<StartScene>();

	// 最初のシーンに遷移する
	this->setScene<StartScene>();
}

//=============================================================
// 更新
//=============================================================
void SceneManager::Update()
{
	// 次のシーンがあるときにシーンを変更する
	changeScene();
}

//=============================================================
// すべて解放する
//=============================================================
void SceneManager::AllRelease()
{
	// 現在のシーンを終了する
	if (m_currentScene != nullptr)
	{
		// 終了処理
		m_currentScene->Uninit();
		m_currentScene = nullptr;
	}

	// 登録されているシーンをすべて解放する
	for (auto itr = m_scenes.begin(); itr != m_scenes.end(); itr++)
	{
		delete* itr;
		*itr = nullptr;
	}
	m_scenes.clear();
}

//=============================================================
// ゲームオブジェクトを破棄する
//=============================================================
void SceneManager::releaseGameObjects()
{
	// ゲームオブジェクトを取得する
	auto gameObjectList = GameObject::getAllGameObjects();

	for (auto itr = gameObjectList.begin(); itr != gameObjectList.end(); itr++)
	{
		if ((*itr)->tag != TAG_NODESTROY)
		{
			Object::Destroy(*itr);
		}
	}
}

//=============================================================
// シーンを変更する
//=============================================================
void SceneManager::changeScene()
{
	// 次のシーンが設定されていないときはスキップする
	if (m_nextScene == nullptr)
	{
		return;
	}

	// 今までのシーンを終了する
	if (m_currentScene != nullptr)
	{
		// 終了処理
		m_currentScene->Uninit();

		// ログを送信する
		Log::sendLog("シーン \"" + static_cast<std::string>(typeid(*m_currentScene).name()) + "\" を終了しました");

		// 現在のシーンを空にする
		m_currentScene = nullptr;
	}

	// オブジェクトの破棄
	if (m_isReleaseObjects)
	{
		releaseGameObjects();
	}

	// 新しいシーンを現在のシーンにする
	m_currentScene = m_nextScene;
	m_nextScene = nullptr;
	if (m_currentScene != nullptr)
	{
		// ログを送信する
		Log::sendLog("シーン \"" + static_cast<std::string>(typeid(*m_currentScene).name()) + "\" に遷移しました");

		// 初期化処理
		m_currentScene->Init();

		return;
	}

	// 失敗したとき
	Log::sendLog("シーンの遷移に失敗しました", Log::TYPE_ERROR);
}
