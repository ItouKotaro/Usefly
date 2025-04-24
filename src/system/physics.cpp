//------------------------------------------------------------
// @file			physics.cpp
// @brief		����
// @detail	�������Z�̏���
//------------------------------------------------------------
#include "physics.h"
#include "components/3d/collision.h"

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

	// �d�͂�ݒ�
	m_world->setGravity(btVector3(0, -90, 0));
}

//=============================================================
// �I��
//=============================================================
void Physics::Uninit()
{
	// �R���W�������X�g���폜����
	for (auto itr = m_collisionShapes.begin(); itr != m_collisionShapes.end(); itr++)
	{
		delete* itr;
		*itr = nullptr;
	}
	m_collisionShapes.clear();

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

	// �I�u�W�F�N�g�̃g�����X�t�H�[�������㏑������
	//for (auto itr = )

	// �V�����ǉ����ꂽ�R���W������o�^����
	auto& gameObjects = GameObject::GetAllGameObjects();
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
	{
		Collision* collision = (*itr)->GetComponent<Collision>(true);
		if (collision != nullptr && collision->GetUpdateFlag())
		{ // �X�V�t���O�������Ă���Ƃ�
			// �\������
			collision->Build();
		}
	}
}

////=============================================================
//// �R���W�����I�u�W�F�N�g��ǉ�����
////=============================================================
//void Physics::AddCollisionObject(Collision* collision)
//{
//	// �R���W���������[���h�ɒǉ�����
//	m_world->addCollisionObject(collision->GetCollision());
//}
//
////=============================================================
//// �R���W�����I�u�W�F�N�g���폜����
////=============================================================
//void Physics::RemoveCollisionObject(Collision* collision)
//{
//	// �R���W���������X�g����폜
//}
