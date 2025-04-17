//------------------------------------------------------------
// @file			physics.cpp
// @brief		物理
// @detail	物理演算の処理
//------------------------------------------------------------
#include "physics.h"

//=============================================================
// 初期化
//=============================================================
void Physics::Init()
{
	// コリジョンの設定
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	// ブロードフェーズ法の設定
	m_overlappingPairCache = new btDbvtBroadphase();

	// 拘束のソルバ設定
	m_solver = new btSequentialImpulseConstraintSolver;

	// Bulletワールドを作成
	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

	// ゴーストの呼び出し設定
	m_ghostPairCollback = new btGhostPairCallback();
	m_world->getPairCache()->setInternalGhostPairCallback(m_ghostPairCollback);

	// 重力を設定
	m_world->setGravity(btVector3(0, -90, 0));
}

//=============================================================
// 終了
//=============================================================
void Physics::Uninit()
{
	// コリジョンリストを削除する
	for (auto itr = m_collisionShapes.begin(); itr != m_collisionShapes.end(); itr++)
	{
		delete* itr;
		*itr = nullptr;
	}
	m_collisionShapes.clear();

	// 拘束を削除する
	for (int i = 0; i < m_world->getNumConstraints(); i++)
	{
		btTypedConstraint* pConstraint = m_world->getConstraint(i);
		m_world->removeConstraint(pConstraint);
		delete pConstraint;
	}

	// 物理ワールドの破棄
	if (m_world != nullptr)
	{
		delete m_world;
		m_world = nullptr;
	}

	// ゴーストコールバックの破棄
	if (m_ghostPairCollback != nullptr)
	{
		delete m_ghostPairCollback;
		m_ghostPairCollback = nullptr;
	}

	// ソルバの破棄
	if (m_solver != nullptr)
	{
		delete m_solver;
		m_solver = nullptr;
	}

	// オーバーラッピングペアキャッシュの破棄
	if (m_overlappingPairCache != nullptr)
	{
		delete m_overlappingPairCache;
		m_overlappingPairCache = nullptr;
	}

	// ディスパッチャーの破棄
	if (m_dispatcher != nullptr)
	{
		delete m_dispatcher;
		m_dispatcher = nullptr;
	}

	// コリジョン設定の破棄
	if (m_collisionConfiguration != nullptr)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = nullptr;
	}
}

//=============================================================
// 更新
//=============================================================
void Physics::Update()
{
	// 物理ワールドを更新する
	m_world->stepSimulation(static_cast<btScalar>(Main::GetInstance().GetDeltaTime()), 1);

	// オブジェクトのトランスフォーム情報を上書きする
	//for (auto itr = )
}
