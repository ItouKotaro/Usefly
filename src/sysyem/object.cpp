//------------------------------------------------------------
// @file		object.cpp
// @brief	オブジェクト
// @detail	オブジェクト類の基底クラス
//------------------------------------------------------------
#include "object.h"

// 静的メンバ変数の初期化
std::vector<Object*> Object::m_objects;

//=============================================================
// コンストラクタ
//=============================================================
Object::Object() : m_deathFlag(false), m_active(true)
{
	// データを追加する
	m_objects.push_back(this);
}

//=============================================================
// デストラクタ
//=============================================================
Object::~Object()
{
	// データを削除する
	for (auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		if (*itr == this)
		{
			m_objects.erase(itr);
			break;
		}
	}
}

//=============================================================
// デスフラグのオブジェクトを破棄する
//=============================================================
void Object::ReleaseDeathFlag()
{
	int idx = static_cast<int>(m_objects.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		if (m_objects[i]->m_deathFlag)
		{ // 死亡フラグがついているとき
			m_objects[i]->Release();
			delete m_objects[i];
		}
	}
}

//=============================================================
// すべてのオブジェクトを破棄する
//=============================================================
void Object::AllDestroy()
{
	for (auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		Destroy(*itr);
	}
	
	// デスフラグのオブジェクトを破棄する
	ReleaseDeathFlag();
}
