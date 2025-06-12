//------------------------------------------------------------
// @file			camera_options.cpp
// @brief		カメラのオプション
//------------------------------------------------------------
#include "camera_options.h"

//=============================================================
// オブジェクトを追加する
//=============================================================
void LimitObjects::AddObject(GameObject* object)
{
	if (std::find(m_objects.begin(), m_objects.end(), object) == m_objects.end())
	{
		m_objects.push_back(object);
	}

	auto& gameObjects = GameObject::GetAllGameObjects();
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		if ((*itr)->transform->GetParent() == object->transform)
		{
			AddObject((*itr));
		}
	}
}

//=============================================================
// オブジェクトを削除する
//=============================================================
void LimitObjects::RemoveObject(GameObject* object)
{
	auto itr = std::find(m_objects.begin(), m_objects.end(), object);
	if (itr != m_objects.end())
	{
		m_objects.erase(itr);
	}
}

//=============================================================
// オブジェクトをリセットする
//=============================================================
void LimitObjects::ResetObject()
{
	m_objects.clear();
}

//=============================================================
// 描画する
//=============================================================
void LimitObjects::LimitDraw()
{
	auto& gameObjects = GameObject::GetAllGameObjects();
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		// 非アクティブ時はスルー
		if (!(*itr)->GetActive() && !m_ignoreActive)
		{
			continue;
		}

		bool isExist = std::find(m_objects.begin(), m_objects.end(), *itr) != m_objects.end();
		if (m_type == WHITE && isExist)
		{
			(*itr)->Draw();
		}
		else if (m_type == BLACK && !isExist)
		{
			(*itr)->Draw();
		}
	}
}
