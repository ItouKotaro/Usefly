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

	// トランスフォーム情報を更新する
	m_oldTransform = *transform;

	// 物理リストに追加する
	Manager::GetInstance()->GetPhysics()->AddCollision(this);
}

//=============================================================
// 終了
//=============================================================
void Collision::Uninit()
{
	// 物理リストから削除する
	Manager::GetInstance()->GetPhysics()->RemoveCollision(this);

	// 形状を破棄する
	if (m_shape != nullptr)
	{
		delete m_shape;
		m_shape = nullptr;
	}

	// コリジョンを破棄する
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}

	// 副次的なコンポーネントを削除する
	if (gameObject != nullptr)
	{
		auto rigidBody = gameObject->GetComponent<RigidBody>();
		if (rigidBody != nullptr)
		{
			Destroy(rigidBody);
		}
	}
}

//=============================================================
// 更新
//=============================================================
void Collision::Update()
{
	
}

//=============================================================
// ビルドする
//=============================================================
void Collision::Build()
{
	// リジッドボディを取得する
	auto rigidbody = gameObject->GetComponent<RigidBody>();

	// コリジョンを破棄する
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}

	// コライダーシェイプを生成する
	GenerateColliderShape();

	// 位置を設定
	btTransform startTransform;
	D3DXVECTOR3 worldPos = transform->GetWorldPosition();
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

	// 回転を設定
	D3DXQUATERNION worldRot = transform->GetWorldRotation();
	btQuaternion quaternion(worldRot.x, worldRot.y, worldRot.z, worldRot.w);
	startTransform.setRotation(quaternion);

	if (rigidbody != nullptr)
	{ // リジッドボディを作成する
		// 質量
		btScalar mass = rigidbody->GetMass();

		// 移動するオブジェクトか
		bool isDynamic = (mass != 0.0f);

		// 慣性モーメント
		btVector3 inertia(0, 0, 0);
		if (isDynamic)
		{
			m_shape->calculateLocalInertia(mass, inertia);
		}

		// 剛体操作
		rigidbody->SetMotionState(new btDefaultMotionState(startTransform));

		// 剛体作成
		btRigidBody::btRigidBodyConstructionInfo rb_info(mass, rigidbody->GetMotionState(), m_shape, inertia);
		m_collision = new btRigidBody(rb_info);

		// 摩擦設定
		m_collision->setFriction(m_friction);

		// 物理ワールドに追加する
		Manager::GetInstance()->GetPhysics()->GetWorld()->addRigidBody((btRigidBody*)m_collision);
	}
	else
	{ // ゴーストオブジェクトを作成する
		m_collision = new btGhostObject;

		// 形状を設定する
		m_collision->setCollisionShape(m_shape);

		// 摩擦設定
		m_collision->setFriction(m_friction);

		// 他のオブジェクトに干渉するか
		if (m_trigger)
		{
			m_collision->setCollisionFlags(m_collision->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}

		// トランスフォームを設定する
		m_collision->setWorldTransform(startTransform);

		// 物理ワールドに追加する
		Manager::GetInstance()->GetPhysics()->GetWorld()->addCollisionObject(m_collision);
	}

	// フラグを更新する
	m_updateFlag = false;
}

//=============================================================
// トリガーの設定
//=============================================================
void Collision::SetTrigger(const bool& enabled)
{
	if (m_trigger != enabled)
	{
		m_trigger = enabled;
		m_updateFlag = true;
	}
}

//=============================================================
// コライダーシェイプを生成する
//=============================================================
void Collision::GenerateColliderShape()
{
	// コライダーを取得する
	std::vector<Collider*> colliders = gameObject->GetComponents<Collider>(true);

	// 現在の形状を破棄する
	if (m_shape != nullptr)
	{
		// コライダーの終了処理
		for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
		{
			(*itr)->Uninit();
		}

		// 削除
		delete m_shape;
		m_shape = nullptr;
	}

	// シェイプを作成する
	m_shape = new btCompoundShape;

	// 形状を追加
	for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
	{
		(*itr)->AddShape(m_shape);
	}

	// スケールを調整する
	m_shape->setLocalScaling(btVector3(transform->GetWorldScale().x, transform->GetWorldScale().y, transform->GetWorldScale().z));
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

	// 更新対象に追加する
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// 終了
//=============================================================
void RigidBody::Uninit()
{
	// 更新対象に追加する
	if (gameObject != nullptr && gameObject->GetComponent<Collision>() != nullptr)
	{
		gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
	}

	// モーションステートを破棄する
	if (m_motionState != nullptr)
	{
		delete m_motionState;
		m_motionState = nullptr;
	}
}

//=============================================================
// リジットボディを取得する
//=============================================================
btRigidBody* RigidBody::GetRigidBody()
{
	Collision* collision = gameObject->GetComponent<Collision>();
	if (collision != nullptr)
	{
		return btRigidBody::upcast(collision->GetCollision());
	}
	return nullptr;
}

//=============================================================
// モーションステートを設定する
//=============================================================
void RigidBody::SetMotionState(btMotionState* motionState)
{
	if (m_motionState != nullptr)
	{
		delete m_motionState;
		m_motionState = nullptr;
	}

	m_motionState = motionState;
}
