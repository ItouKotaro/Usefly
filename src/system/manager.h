//------------------------------------------------------------
// @file		manager.h
// @brief	マネージャー
// @detail	システムの管理を行います
//------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "resource_data.h"
#include "scene.h"
#include "input.h"

#define Input Manager::GetInstance()->GetInputManager()

//@brief 管理クラス
class Manager final
{
public:
	//@brief 初期化
	void Init(HINSTANCE hInstance, HWND hWnd);
	//@brief 終了
	void Uninit();
	//@brief 更新
	void Update();
	//@brief 描画
	void Draw();

	//@brief レンダラーを取得する
	Renderer* GetRenderer() { return m_renderer; }
	//@brief リソースデータマネージャーを取得する
	ResourceDataManager* GetResourceDataManager() { return m_resourceDataManager; }
	//@brief シーンマネージャーを取得する
	SceneManager* GetSceneManager() { return m_sceneManager; }
	//@brief 入力マネージャーを取得する
	InputManager* GetInputManager() { return m_inputManager; }

	//@brief デバイスを取得する
	LPDIRECT3DDEVICE9 GetDevice() { return m_renderer->GetDevice(); }

	//@brief インスタンスの取得
	static Manager* GetInstance()
	{
		static Manager instance;
		return &instance;
	}
private:
	Renderer* m_renderer;											// レンダラー
	ResourceDataManager* m_resourceDataManager;	// リソースデータマネージャー
	SceneManager* m_sceneManager;							// シーンマネージャー
	InputManager* m_inputManager;							// 入力マネージャー
};

#endif // !_MANAGER_H_
