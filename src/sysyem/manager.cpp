//------------------------------------------------------------
// @file		manager.cpp
// @brief	マネージャー
// @detail	システムの管理を行います
//------------------------------------------------------------
#include "manager.h"
#include "components/2d/sprite.h"

//=============================================================
// 初期化
//=============================================================
void Manager::Init(HINSTANCE hInstance, HWND hWnd)
{
	// レンダラーを生成する
	m_renderer = new Renderer();
	m_renderer->Init(hInstance, hWnd);

	// シーンマネージャーを生成する
	m_sceneManager = new SceneManager();
	m_sceneManager->Init();

	// リソースデータマネージャーを生成する
	m_resourceDataManager = new ResourceDataManager();
}

//=============================================================
// 終了
//=============================================================
void Manager::Uninit()
{
	// すべてのオブジェクトを破棄する
	Object::AllDestroy();
	
	// レンダラーを終了する
	if (m_renderer != nullptr)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = nullptr;
	}

	// シーンマネージャーを終了する
	if (m_sceneManager != nullptr)
	{
		m_sceneManager->AllRelease();
		delete m_sceneManager;
		m_sceneManager = nullptr;
	}

	// リソースデータをすべて破棄する
	if (m_resourceDataManager != nullptr)
	{
		m_resourceDataManager->AllRelease();
		delete m_resourceDataManager;
		m_resourceDataManager = nullptr;
	}

#if OUTPUT_LOG_FILE
	// ログを書き出す
	Log::OutputLog();
#endif
}

//=============================================================
// 更新
//=============================================================
void Manager::Update()
{
	// ゲームオブジェクトを更新する
	GameObject::AllUpdate();

	// レンダラーを更新する
	m_renderer->Update();

	// シーンを更新する
	m_sceneManager->Update();

	// デスフラグがついているオブジェクトを破棄する
	Object::ReleaseDeathFlag();
}

//=============================================================
// 描画
//=============================================================
void Manager::Draw()
{
	// レンダラーを描画する
	m_renderer->Draw();
}
