//------------------------------------------------------------
// @file		gameobject.cpp
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#include "gameobject.h"
#include "component.h"

// 静的メンバ変数の初期化
std::vector<GameObject*> GameObject::m_gameObjects;

//=============================================================
// コンストラクタ
//=============================================================
GameObject::GameObject()
{
	// リストに追加する
	m_gameObjects.push_back(this);
}

//=============================================================
// デストラクタ
//=============================================================
GameObject::~GameObject()
{
	// リストから削除する
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == this)
		{
			m_gameObjects.erase(itr);
			break;
		}
	}
}

//=============================================================
// 初期化
//=============================================================
void GameObject::Init()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Init();
	}
}

//=============================================================
// 終了
//=============================================================
void GameObject::Uninit()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Uninit();
	}
}

//=============================================================
// 更新
//=============================================================
void GameObject::Update()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Update();
	}
}

//=============================================================
// 描画
//=============================================================
void GameObject::Draw()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Draw();
	}
}

//=============================================================
// 描画UI
//=============================================================
void GameObject::DrawUI()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->DrawUI();
	}
}