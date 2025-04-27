//------------------------------------------------------------
// @file			physics.cpp
// @brief		����
// @detail	�������Z�̏���
//------------------------------------------------------------
#include "physics.h"
#include "components/3d/collision.h"

// �萔
constexpr bool DEBUG_LINE_VISIBLE = true;	// ���C����\�����邩
constexpr int DEBUG_LINE_LIFE = 30;				// ���C���̎���

//=============================================================
// ������
//=============================================================
void Physics::Init()
{
	// �R���W�����̐ݒ�
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	// �u���[�h�t�F�[�Y�@�̐ݒ�
	m_overlappingPairCache = new btDbvtBroadphase();

	// �S���̃\���o�ݒ�
	m_solver = new btSequentialImpulseConstraintSolver;

	// Bullet���[���h���쐬
	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

	// �S�[�X�g�̌Ăяo���ݒ�
	m_ghostPairCollback = new btGhostPairCallback();
	m_world->getPairCache()->setInternalGhostPairCallback(m_ghostPairCollback);

	// �f�o�b�O�̐ݒ�
	m_debugDrawer = new DebugPhysics();
	m_debugDrawer->setDebugMode(DEBUG_LINE_VISIBLE ? btIDebugDraw::DBG_DrawWireframe : btIDebugDraw::DBG_NoDebug);
	m_world->setDebugDrawer(m_debugDrawer);

	// �A�N�V�����C���^�[�t�F�C�X�̐ݒ�
	m_actionInterface = new ActionInterface();
	m_world->addAction(m_actionInterface);

	// �d�͂�ݒ�
	m_world->setGravity(btVector3(0, -90, 0));
}

//=============================================================
// �I��
//=============================================================
void Physics::Uninit()
{
	// �S�����폜����
	for (int i = 0; i < m_world->getNumConstraints(); i++)
	{
		btTypedConstraint* pConstraint = m_world->getConstraint(i);
		m_world->removeConstraint(pConstraint);
		delete pConstraint;
	}

	// �������[���h�̔j��
	if (m_world != nullptr)
	{
		delete m_world;
		m_world = nullptr;
	}

	// �A�N�V�����C���^�[�t�F�C�X�̔j��
	if (m_actionInterface != nullptr)
	{
		delete m_actionInterface;
		m_actionInterface = nullptr;
	}

	// �f�o�b�O�`��̔j��
	if (m_debugDrawer != nullptr)
	{
		m_debugDrawer->Uninit();
		delete m_debugDrawer;
		m_debugDrawer = nullptr;
	}

	// �S�[�X�g�R�[���o�b�N�̔j��
	if (m_ghostPairCollback != nullptr)
	{
		delete m_ghostPairCollback;
		m_ghostPairCollback = nullptr;
	}

	// �\���o�̔j��
	if (m_solver != nullptr)
	{
		delete m_solver;
		m_solver = nullptr;
	}

	// �I�[�o�[���b�s���O�y�A�L���b�V���̔j��
	if (m_overlappingPairCache != nullptr)
	{
		delete m_overlappingPairCache;
		m_overlappingPairCache = nullptr;
	}

	// �f�B�X�p�b�`���[�̔j��
	if (m_dispatcher != nullptr)
	{
		delete m_dispatcher;
		m_dispatcher = nullptr;
	}

	// �R���W�����ݒ�̔j��
	if (m_collisionConfiguration != nullptr)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = nullptr;
	}
}

//=============================================================
// �X�V
//=============================================================
void Physics::Update()
{
	// �������[���h���X�V����
	m_world->stepSimulation(static_cast<btScalar>(Main::GetInstance().GetDeltaTime()), 1);
	m_world->debugDrawWorld();

	// �V�����ǉ����ꂽ�R���W������o�^����
	for (auto itr = m_collisions.begin(); itr != m_collisions.end(); itr++)
	{
		Collision* collision = *itr;
		RigidBody* rigidbody = collision->gameObject->GetComponent<RigidBody>();

		// �g�����X�t�H�[�����ύX����Ă����ꍇ
		if (*collision->gameObject->transform != collision->GetOldTransform() && collision->GetCollision() != nullptr)
		{
			// �ʒu��ݒ�
			btTransform changedTransform;
			D3DXVECTOR3 worldPos = collision->gameObject->transform->GetWorldPosition();
			changedTransform.setIdentity();
			changedTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

			// ��]��ݒ�
			D3DXQUATERNION worldRot = collision->gameObject->transform->GetWorldRotation();
			btQuaternion quaternion(worldRot.x, worldRot.y, worldRot.z, worldRot.w);
			changedTransform.setRotation(quaternion);

			// �X�P�[�����ύX����Ă��邩
			if (collision->gameObject->transform->GetWorldScale() != collision->GetOldTransform().GetWorldScale())
			{
				collision->GetUpdateFlag() = true;
			}

			// �ύX��K�p����
			collision->GetCollision()->setWorldTransform(changedTransform);
		}

		// ���W�b�h�{�f�B�̃g�����X�t�H�[�����X�V����
		if (rigidbody != nullptr && collision->GetCollision() != nullptr)
		{
			// ���ʂ��擾����
			btTransform result;
			rigidbody->GetRigidBody()->getMotionState()->getWorldTransform(result);

			// �X�V����
			collision->transform->position = { result.getOrigin().getX(), result.getOrigin().getY(), result.getOrigin().getZ() };
			collision->transform->rotation = { result.getRotation().getX(), result.getRotation().getY(), result.getRotation().getZ(), result.getRotation().getW() };
		}

		// �X�V�t���O�������Ă���Ƃ�
		if (collision->GetUpdateFlag())
		{
			// �\������
			collision->Build();
		}
	}
}

//=============================================================
// �`��
//=============================================================
void Physics::Draw()
{
	// �f�o�b�O�̕`��
	m_debugDrawer->Draw();
}

//=============================================================
// �R���W������ǉ�����
//=============================================================
void Physics::AddCollision(Collision* collision)
{
	// �d�����Ă��Ȃ��Ƃ��̂ݒǉ�����
	if (std::find(m_collisions.begin(), m_collisions.end(), collision) == m_collisions.end())
	{
		m_collisions.emplace_back(collision);
	}
}

//=============================================================
// �R���W�������폜����
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
// btCollisionObject����Collision��T��
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
// �f�o�b�O : ���̕`��
//=============================================================
void Physics::DebugPhysics::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	LineData* target = nullptr;

	// �]���Ă��郉�C�������邩
	for (auto itr = m_lineData.begin(); itr != m_lineData.end(); itr++)
	{
		if (!(*itr)->use)
		{ // �g���Ă��Ȃ��Ƃ�
			(*itr)->from = { from.getX(), from.getY(), from.getZ() };
			(*itr)->to = { to.getX(), to.getY(), to.getZ() };
			(*itr)->color = { color.getX(), color.getY(), color.getZ(), 1.0f };
			(*itr)->life = DEBUG_LINE_LIFE;
			(*itr)->use = true;

			target = *itr;
			break;
		}
	}

	// �]���Ă��Ȃ������ꍇ�A���C����V�K�쐬����
	if (target == nullptr)
	{
		LineData* data = new LineData();
		data->from = D3DXVECTOR3(from.getX(), from.getY(), from.getZ());
		data->to = D3DXVECTOR3(to.getX(), to.getY(), to.getZ());
		data->color = D3DXCOLOR(color.getX(), color.getY(), color.getZ(), 1.0f);
		data->life = DEBUG_LINE_LIFE;
		data->use = true;

		// �o�b�t�@���m�ۂ���
		auto device = Manager::GetInstance()->GetRenderer()->GetDevice();
		device->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &data->vtxBuff, nullptr);

		// �ǉ�����
		m_lineData.emplace_back(data);
		target = data;
	}


	// ���C���̐ݒ���s��
	if (target != nullptr)
	{
		VERTEX_3D* pVtx;
		target->vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = target->from;
		pVtx[1].pos = target->to;

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[
		pVtx[0].col = target->color;
		pVtx[1].col = target->color;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		target->vtxBuff->Unlock();
	}
}

//=============================================================
// �f�o�b�O : ���C�����폜����
//=============================================================
void Physics::DebugPhysics::clearLines()
{
	for (auto itr = m_lineData.begin(); itr != m_lineData.end(); itr++)
	{
		(*itr)->use = false;
	}
}

//=============================================================
// �f�o�b�O : �I��
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
// �f�o�b�O : �`��
//=============================================================
void Physics::DebugPhysics::Draw()
{
	// �f�o�C�X���擾����
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();

	for (auto itr = m_lineData.begin(); itr != m_lineData.end();)
	{
		if ((*itr)->use)
		{
			// ���[���h�}�g���b�N�X�̐ݒ�
			D3DXMATRIX mtx;
			D3DXMatrixIdentity(&mtx);
			device->SetTransform(D3DTS_WORLD, &mtx);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			device->SetStreamSource(0, (*itr)->vtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			device->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			device->SetTexture(0, nullptr);

			// �|���S���̕`��
			device->DrawPrimitive(D3DPT_LINELIST, //�v���~�e�B�u�̎��
				0, //�`�悷��ŏ��̒��_�C���f�b�N�X
				1);				//�`�悷��v���~�e�B�u��

			// �C�e���[�^�[��i�߂�
			itr++;
		}
		else
		{ // ���g�p�̏ꍇ
			(*itr)->life--;

			// �������Ȃ��Ȃ����Ƃ�
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
// �A�N�V�����C���^�[�t�F�C�X
//=============================================================
void ActionInterface::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	// �R���W�������擾����
	std::vector<Collision*>& collisions = Manager::GetInstance()->GetPhysics()->GetCollisions();
	for (auto itr = collisions.begin(); itr != collisions.end(); itr++)
	{
		if ((*itr)->GetCollision() == nullptr)
		{
			continue;
		}

		// �R���W���������擾����
		Collision* collision = *itr;																												// �R���W����
		RigidBody* rigidbody = collision->gameObject->GetComponent<RigidBody>();						// ���W�b�h�{�f�B�i�����ꍇ�� nullptr�j
		bool isTrigger = collision->GetTrigger();																						// �g���K�[��
		std::vector<Collision*>& overlappingCollisions = collision->GetOverlappingCollisions();			// �d�Ȃ��Ă���R���W����
		std::vector<Component*>& componentList = collision->gameObject->GetComponents();	// �R���|�[�l���g���X�g

		if (rigidbody == nullptr)
		{ // �S�[�X�g�I�u�W�F�N�g

			btGhostObject* ghostObj = (btGhostObject*)collision->GetCollision();

			// ���݁A�d�Ȃ��Ă���R���W���������X�g������
			int overlappingNum = ghostObj->getNumOverlappingObjects();
			std::vector<Collision*> currentOverlapping;
			for (int i = 0; i < overlappingNum; i++)
			{
				// �R���W�������擾����
				Collision* overlapObj = Manager::GetInstance()->GetPhysics()->FindCollision(ghostObj->getOverlappingObject(i));
				if (overlapObj != nullptr)
				{
					currentOverlapping.emplace_back(overlapObj);
				}
			}

			// Enter�C�x���g
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

			// Stay�C�x���g
			for (auto compItr = componentList.begin(); compItr != componentList.end(); compItr++)
			{
				for (auto overlapItr = currentOverlapping.begin(); overlapItr != currentOverlapping.end(); overlapItr++)
				{
					isTrigger ? (*compItr)->OnTriggerStay(*overlapItr) : (*compItr)->OnCollisionStay(*overlapItr);
				}
			}

			// Exit�C�x���g
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

			// �d�Ȃ��Ă���R���W�������X�V����
			overlappingCollisions.clear();
			overlappingCollisions = std::move(currentOverlapping);
		}


	}
}
