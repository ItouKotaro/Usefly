//------------------------------------------------------------
// @file			collision.cpp
// @brief		コリジョン
// @detail	当たり判定
//------------------------------------------------------------
#include "collision.h"

//=============================================================
// 初期化
//=============================================================
void Collision::Init()
{
	// すでにコリジョンコンポーネントが含まれているとき
	if (static_cast<int>(gameObject->GetComponents<Collision>().size()) > 1)
	{
		Destroy(this);
		return;
	}

	// 構築する
	Build();
}

//=============================================================
// 終了
//=============================================================
void Collision::Uninit()
{
	// コリジョンを破棄する
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}
}

//=============================================================
// ビルドする
//=============================================================
void Collision::Build()
{
	// リジッドボディを取得する
	auto rigidbody = gameObject->GetComponent<RigidBody>();

	if (rigidbody != nullptr)
	{ // リジッドボディのとき

	}
}

//=============================================================
// 初期化
//=============================================================
void RigidBody::Init()
{
	// すでにリジッドボディコンポーネントが含まれているとき
	if (static_cast<int>(gameObject->GetComponents<RigidBody>().size()) > 1)
	{
		Destroy(this);
		return;
	}

	// コリジョンコンポーネントが含まれていないとき
	if (gameObject->GetComponents<Collision>().empty())
	{
		Destroy(this);
		return;
	}

	// リジッドボディを
}

//=============================================================
// 終了
//=============================================================
void RigidBody::Uninit()
{
}
