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
		if ((*itr)->GetActive())
		{
			(*itr)->Update();
		}
	}
}

//=============================================================
// 描画
//=============================================================
void GameObject::Draw()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Draw();
		}
	}
}

//=============================================================
// 描画UI
//=============================================================
void GameObject::DrawUI()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->DrawUI();
		}
	}
}

//=============================================================
// すべてのオブジェクトを更新する
//=============================================================
void GameObject::AllUpdate()
{
	for (UINT i = 0; i < static_cast<UINT>(m_gameObjects.size()); i++)
	{
		if (m_gameObjects[i]->GetActive())
		{
			m_gameObjects[i]->Update();
		}
	}
}

//=============================================================
// すべてのオブジェクトを描画する
//=============================================================
void GameObject::AllDraw()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Draw();
		}
	}
}

//=============================================================
// すべてのオブジェクトをUI描画する
//=============================================================
void GameObject::AllDrawUI()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->DrawUI();
		}
	}
}

//=============================================================
// 名前からゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByName(const std::string& name)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->name == name)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// タグからゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByTag(const std::string& tag)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->tag == tag)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// 名前とタグからゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByNameTag(const std::string& name, const std::string& tag)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->name == name && (*itr)->tag == tag)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// 親を設定する
//=============================================================
void GameObject::SetParent(GameObject* gameObject)
{
	if (gameObject != nullptr)
	{
		transform->SetParent(gameObject->transform);
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
	// 親子関係のあるオブジェクトを破棄する
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->transform->GetParent();
	}

	// コンポーネントを解放する
	int idx = static_cast<int>(m_components.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		Destroy(m_components[i]);
		m_components[i]->DetachGameObject();
	}
}
