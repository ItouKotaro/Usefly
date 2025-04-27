//------------------------------------------------------------
// @file			physics.cpp
// @brief		物理
// @detail	物理演算の処理
//------------------------------------------------------------
#include "physics.h"
#include "components/3d/collision.h"

// 定数
constexpr bool DEBUG_LINE_VISIBLE = true;	// ラインを表示するか
constexpr int DEBUG_LINE_LIFE = 30;				// ラインの寿命

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

	// デバッグの設定
	m_debugDrawer = new DebugPhysics();
	m_debugDrawer->setDebugMode(DEBUG_LINE_VISIBLE ? btIDebugDraw::DBG_DrawWireframe : btIDebugDraw::DBG_NoDebug);
	m_world->setDebugDrawer(m_debugDrawer);

	// アクションインターフェイスの設定
	m_actionInterface = new ActionInterface();
	m_world->addAction(m_actionInterface);

	// 重力を設定
	m_world->setGravity(btVector3(0, -90, 0));
}

//=============================================================
// 終了
//=============================================================
void Physics::Uninit()
{
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

	// アクションインターフェイスの破棄
	if (m_actionInterface != nullptr)
	{
		delete m_actionInterface;
		m_actionInterface = nullptr;
	}

	// デバッグ描画の破棄
	if (m_debugDrawer != nullptr)
	{
		m_debugDrawer->Uninit();
		delete m_debugDrawer;
		m_debugDrawer = nullptr;
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
	m_world->debugDrawWorld();

	// 新しく追加されたコリジョンを登録する
	for (auto itr = m_collisions.begin(); itr != m_collisions.end(); itr++)
	{
		Collision* collision = *itr;
		RigidBody* rigidbody = collision->gameObject->GetComponent<RigidBody>();

		// トランスフォームが変更されていた場合
		if (*collision->gameObject->transform != collision->GetOldTransform() && collision->GetCollision() != nullptr)
		{
			// 位置を設定
			btTransform changedTransform;
			D3DXVECTOR3 worldPos = collision->gameObject->transform->GetWorldPosition();
			changedTransform.setIdentity();
			changedTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

			// 回転を設定
			D3DXQUATERNION worldRot = collision->gameObject->transform->GetWorldRotation();
			btQuaternion quaternion(worldRot.x, worldRot.y, worldRot.z, worldRot.w);
			changedTransform.setRotation(quaternion);

			// スケールが変更されているか
			if (collision->gameObject->transform->GetWorldScale() != collision->GetOldTransform().GetWorldScale())
			{
				collision->GetUpdateFlag() = true;
			}

			// 変更を適用する
			collision->GetCollision()->setWorldTransform(changedTransform);
		}

		// リジッドボディのトランスフォームを更新する
		if (rigidbody != nullptr && collision->GetCollision() != nullptr)
		{
			// 結果を取得する
			btTransform result;
			rigidbody->GetRigidBody()->getMotionState()->getWorldTransform(result);

			// 更新する
			collision->transform->position = { result.getOrigin().getX(), result.getOrigin().getY(), result.getOrigin().getZ() };
			collision->transform->rotation = { result.getRotation().getX(), result.getRotation().getY(), result.getRotation().getZ(), result.getRotation().getW() };
		}

		// 更新フラグが立っているとき
		if (collision->GetUpdateFlag())
		{
			// 構成する
			collision->Build();
		}
	}
}

//=============================================================
// 描画
//=============================================================
void Physics::Draw()
{
	// デバッグの描画
	m_debugDrawer->Draw();
}

//=============================================================
// コリジョンを追加する
//=============================================================
void Physics::AddCollision(Collision* collision)
{
	// 重複していないときのみ追加する
	if (std::find(m_collisions.begin(), m_collisions.end(), collision) == m_collisions.end())
	{
		m_collisions.emplace_back(collision);
	}
}

//=============================================================
// コリジョンを削除する
//=============================================================
void Physics::RemoveCollision(Collision* collision)
{
	auto target = std::find(m_collisions.begin(), m_collisions.end(), collision);
	if (target != m_collisions.end())
	{
		m_collisions.erase(target);
	}
}

//=============================================================
// btCollisionObjectからCollisionを探す
//=============================================================
Collision* Physics::FindCollision(btCollisionObject* collisionObject)
{
	for (auto itr = m_collisions.begin(); itr != m_collisions.end(); itr++)
	{
		if ((*itr)->GetCollision() == collisionObject)
		{
			return *itr;
		}
	}
	return nullptr;
}


//=============================================================
// デバッグ : 線の描画
//=============================================================
void Physics::DebugPhysics::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	LineData* target = nullptr;

	// 余っているラインがあるか
	for (auto itr = m_lineData.begin(); itr != m_lineData.end(); itr++)
	{
		if (!(*itr)->use)
		{ // 使われていないとき
			(*itr)->from = { from.getX(), from.getY(), from.getZ() };
			(*itr)->to = { to.getX(), to.getY(), to.getZ() };
			(*itr)->color = { color.getX(), color.getY(), color.getZ(), 1.0f };
			(*itr)->life = DEBUG_LINE_LIFE;
			(*itr)->use = true;

			target = *itr;
			break;
		}
	}

	// 余っていなかった場合、ラインを新規作成する
	if (target == nullptr)
	{
		LineData* data = new LineData();
		data->from = D3DXVECTOR3(from.getX(), from.getY(), from.getZ());
		data->to = D3DXVECTOR3(to.getX(), to.getY(), to.getZ());
		data->color = D3DXCOLOR(color.getX(), color.getY(), color.getZ(), 1.0f);
		data->life = DEBUG_LINE_LIFE;
		data->use = true;

		// バッファを確保する
		auto device = Manager::GetInstance()->GetRenderer()->GetDevice();
		device->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &data->vtxBuff, nullptr);

		// 追加する
		m_lineData.emplace_back(data);
		target = data;
	}


	// ラインの設定を行う
	if (target != nullptr)
	{
		VERTEX_3D* pVtx;
		target->vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = target->from;
		pVtx[1].pos = target->to;

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラー
		pVtx[0].col = target->color;
		pVtx[1].col = target->color;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

		// 頂点バッファをアンロックする
		target->vtxBuff->Unlock();
	}
}

//=============================================================
// デバッグ : ラインを削除する
//=============================================================
void Physics::DebugPhysics::clearLines()
{
	for (auto itr = m_lineData.begin(); itr != m_lineData.end(); itr++)
	{
		(*itr)->use = false;
	}
}

//=============================================================
// デバッグ : 終了
//=============================================================
void Physics::DebugPhysics::Uninit()
{
	for (auto itr = m_lineData.begin(); itr != m_lineData.end(); itr++)
	{
		(*itr)->vtxBuff->Release();
		delete* itr;
		*itr = nullptr;
	}
	m_lineData.clear();
}

//=============================================================
// デバッグ : 描画
//=============================================================
void Physics::DebugPhysics::Draw()
{
	// デバイスを取得する
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();

	for (auto itr = m_lineData.begin(); itr != m_lineData.end();)
	{
		if ((*itr)->use)
		{
			// ワールドマトリックスの設定
			D3DXMATRIX mtx;
			D3DXMatrixIdentity(&mtx);
			device->SetTransform(D3DTS_WORLD, &mtx);

			// 頂点バッファをデータストリームに設定
			device->SetStreamSource(0, (*itr)->vtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			device->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			device->SetTexture(0, nullptr);

			// ポリゴンの描画
			device->DrawPrimitive(D3DPT_LINELIST, //プリミティブの種類
				0, //描画する最初の頂点インデックス
				1);				//描画するプリミティブ数

			// イテレーターを進める
			itr++;
		}
		else
		{ // 未使用の場合
			(*itr)->life--;

			// 寿命がなくなったとき
			if ((*itr)->life <= 0)
			{
				LineData* data = *itr;
				itr = m_lineData.erase(itr);

				data->vtxBuff->Release();
				delete data;
				data = nullptr;
			}
		}
	}
}


//=============================================================
// アクションインターフェイス
//=============================================================
void ActionInterface::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	// コリジョンを取得する
	std::vector<Collision*>& collisions = Manager::GetInstance()->GetPhysics()->GetCollisions();
	for (auto itr = collisions.begin(); itr != collisions.end(); itr++)
	{
		if ((*itr)->GetCollision() == nullptr)
		{
			continue;
		}

		// コリジョン情報を取得する
		Collision* collision = *itr;																												// コリジョン
		RigidBody* rigidbody = collision->gameObject->GetComponent<RigidBody>();						// リジッドボディ（無い場合は nullptr）
		bool isTrigger = collision->GetTrigger();																						// トリガーか
		std::vector<Collision*>& overlappingCollisions = collision->GetOverlappingCollisions();			// 重なっているコリジョン
		std::vector<Component*>& componentList = collision->gameObject->GetComponents();	// コンポーネントリスト

		if (rigidbody == nullptr)
		{ // ゴーストオブジェクト

			btGhostObject* ghostObj = (btGhostObject*)collision->GetCollision();

			// 現在、重なっているコリジョンをリスト化する
			int overlappingNum = ghostObj->getNumOverlappingObjects();
			std::vector<Collision*> currentOverlapping;
			for (int i = 0; i < overlappingNum; i++)
			{
				// コリジョンを取得する
				Collision* overlapObj = Manager::GetInstance()->GetPhysics()->FindCollision(ghostObj->getOverlappingObject(i));
				if (overlapObj != nullptr)
				{
					currentOverlapping.emplace_back(overlapObj);
				}
			}

			// Enterイベント
			for (auto compItr = componentList.begin(); compItr != componentList.end(); compItr++)
			{
				for (auto overlapItr = currentOverlapping.begin(); overlapItr != currentOverlapping.end(); overlapItr++)
				{
					if (std::find(overlappingCollisions.begin(), overlappingCollisions.end(), *overlapItr) == overlappingCollisions.end())
					{
						isTrigger ? (*compItr)->OnTriggerEnter(*overlapItr) : (*compItr)->OnCollisionEnter(*overlapItr);
					}
				}
			}

			// Stayイベント
			for (auto compItr = componentList.begin(); compItr != componentList.end(); compItr++)
			{
				for (auto overlapItr = currentOverlapping.begin(); overlapItr != currentOverlapping.end(); overlapItr++)
				{
					isTrigger ? (*compItr)->OnTriggerStay(*overlapItr) : (*compItr)->OnCollisionStay(*overlapItr);
				}
			}

			// Exitイベント
			for (auto compItr = componentList.begin(); compItr != componentList.end(); compItr++)
			{
				for (auto overlapItr = overlappingCollisions.begin(); overlapItr != overlappingCollisions.end(); overlapItr++)
				{
					if (std::find(currentOverlapping.begin(), currentOverlapping.end(), *overlapItr) == currentOverlapping.end())
					{
						isTrigger ? (*compItr)->OnTriggerExit(*overlapItr) : (*compItr)->OnCollisionExit(*overlapItr);
					}
				}
			}

			// 重なっているコリジョンを更新する
			overlappingCollisions.clear();
			overlappingCollisions = std::move(currentOverlapping);
		}


	}
}
