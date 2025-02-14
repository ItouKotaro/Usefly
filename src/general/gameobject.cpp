//------------------------------------------------------------
// @file		gameobject.cpp
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#include "gameobject.h"
#include "component.h"
using namespace std;
#include <vector>

// 静的メンバ変数の初期化
std::vector<GameObject*> GameObject::m_gameObjects;

//=============================================================
// コンストラクタ
//=============================================================
GameObject::GameObject(std::string vName, std::string vTag)
{
	// 基本情報
	this->name = vName;
	this->tag = vTag;

	// トランスフォームを作成する
	transform = new Transform();

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

	// トランスフォームを削除する
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
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

//=============================================================
// すべてのオブジェクトを更新する
//=============================================================
void GameObject::AllUpdate()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->Update();
	}
}

//=============================================================
// すべてのオブジェクトを描画する
//=============================================================
void GameObject::AllDraw()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->Draw();
	}
}

//=============================================================
// すべてのオブジェクトをUI描画する
//=============================================================
void GameObject::AllDrawUI()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->DrawUI();
	}
}

//=============================================================
// コンポーネントをデタッチする
//=============================================================
void GameObject::DetachComponent(Component* component)
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if (*itr == component)
		{
			(*itr)->gameObject = nullptr;
			(*itr)->transform = nullptr;
			m_components.erase(itr);
			break;
		}
	}
}

//=============================================================
// 解放する
//=============================================================
void GameObject::Release()
{
	// 終了処理を行う
	this->Uninit();

	// 親子関係のあるオブジェクトを破棄する
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->transform->getParent();
	}

	// コンポーネントを解放する
	int idx = static_cast<int>(m_components.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		m_components[i]->Destroy();
		m_components[i]->DetachGameObject();
	}
}
