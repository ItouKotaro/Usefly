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
	Renderer* getRenderer() { return m_renderer; }
	//@brief リソースデータマネージャーを取得する
	ResourceDataManager* getResourceDataManager() { return m_resourceDataManager; }
	//@brief シーンマネージャーを取得する
	SceneManager* getSceneManager() { return m_sceneManager; }

	//@brief デバイスを取得する
	LPDIRECT3DDEVICE9 getDevice() { return m_renderer->getDevice(); }

	//@brief インスタンスの取得
	static Manager* getInstance()
	{
		static Manager instance;
		return &instance;
	}
private:
	Renderer* m_renderer;											// レンダラー
	ResourceDataManager* m_resourceDataManager;	// リソースデータマネージャー
	SceneManager* m_sceneManager;							// シーンマネージャー
};

#endif // !_MANAGER_H_
