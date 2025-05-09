//------------------------------------------------------------
// @file			collision.cpp
// @brief		�R���W����
// @detail	�����蔻��
//------------------------------------------------------------
#include "collision.h"

//=============================================================
// ������
//=============================================================
void Collision::Init()
{
	// ���łɃR���W�����R���|�[�l���g���܂܂�Ă���Ƃ�
	if (static_cast<int>(gameObject->GetComponents<Collision>().size()) > 1)
	{
		Destroy(this);
		return;
	}

	// �g�����X�t�H�[�������X�V����
	m_oldTransform = *transform;

	// �������X�g�ɒǉ�����
	Manager::GetInstance()->GetPhysics()->AddCollision(this);
}

//=============================================================
// �I��
//=============================================================
void Collision::Uninit()
{
	// �������X�g����폜����
	Manager::GetInstance()->GetPhysics()->RemoveCollision(this);

	// �`���j������
	if (m_shape != nullptr)
	{
		delete m_shape;
		m_shape = nullptr;
	}

	// �R���W������j������
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}

	// �����I�ȃR���|�[�l���g���폜����
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
// �X�V
//=============================================================
void Collision::Update()
{
	
}

//=============================================================
// �r���h����
//=============================================================
void Collision::Build()
{
	// ���W�b�h�{�f�B���擾����
	auto rigidbody = gameObject->GetComponent<RigidBody>();

	// �R���W������j������
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}

	// �R���C�_�[�V�F�C�v�𐶐�����
	GenerateColliderShape();

	// �ʒu��ݒ�
	btTransform startTransform;
	D3DXVECTOR3 worldPos = transform->GetWorldPosition();
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

	// ��]��ݒ�
	D3DXQUATERNION worldRot = transform->GetWorldRotation();
	btQuaternion quaternion(worldRot.x, worldRot.y, worldRot.z, worldRot.w);
	startTransform.setRotation(quaternion);

	if (rigidbody != nullptr)
	{ // ���W�b�h�{�f�B���쐬����
		// ����
		btScalar mass = rigidbody->GetMass();

		// �ړ�����I�u�W�F�N�g��
		bool isDynamic = (mass != 0.0f);

		// �������[�����g
		btVector3 inertia(0, 0, 0);
		if (isDynamic)
		{
			m_shape->calculateLocalInertia(mass, inertia);
		}

		// ���̑���
		rigidbody->SetMotionState(new btDefaultMotionState(startTransform));

		// ���̍쐬
		btRigidBody::btRigidBodyConstructionInfo rb_info(mass, rigidbody->GetMotionState(), m_shape, inertia);
		m_collision = new btRigidBody(rb_info);

		// ���C�ݒ�
		m_collision->setFriction(m_friction);

		// �������[���h�ɒǉ�����
		Manager::GetInstance()->GetPhysics()->GetWorld()->addRigidBody((btRigidBody*)m_collision);
	}
	else
	{ // �S�[�X�g�I�u�W�F�N�g���쐬����
		m_collision = new btGhostObject;

		// �`���ݒ肷��
		m_collision->setCollisionShape(m_shape);

		// ���C�ݒ�
		m_collision->setFriction(m_friction);

		// ���̃I�u�W�F�N�g�Ɋ����邩
		if (m_trigger)
		{
			m_collision->setCollisionFlags(m_collision->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}

		// �g�����X�t�H�[����ݒ肷��
		m_collision->setWorldTransform(startTransform);

		// �������[���h�ɒǉ�����
		Manager::GetInstance()->GetPhysics()->GetWorld()->addCollisionObject(m_collision);
	}

	// �t���O���X�V����
	m_updateFlag = false;
}

//=============================================================
// �g���K�[�̐ݒ�
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
// �R���C�_�[�V�F�C�v�𐶐�����
//=============================================================
void Collision::GenerateColliderShape()
{
	// �R���C�_�[���擾����
	std::vector<Collider*> colliders = gameObject->GetComponents<Collider>(true);

	// ���݂̌`���j������
	if (m_shape != nullptr)
	{
		// �R���C�_�[�̏I������
		for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
		{
			(*itr)->Uninit();
		}

		// �폜
		delete m_shape;
		m_shape = nullptr;
	}

	// �V�F�C�v���쐬����
	m_shape = new btCompoundShape;

	// �`���ǉ�
	for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
	{
		(*itr)->AddShape(m_shape);
	}

	// �X�P�[���𒲐�����
	m_shape->setLocalScaling(btVector3(transform->GetWorldScale().x, transform->GetWorldScale().y, transform->GetWorldScale().z));
}

//=============================================================
// ������
//=============================================================
void RigidBody::Init()
{
	// ���łɃ��W�b�h�{�f�B�R���|�[�l���g���܂܂�Ă���Ƃ�
	if (static_cast<int>(gameObject->GetComponents<RigidBody>().size()) > 1)
	{
		Destroy(this);
		return;
	}

	// �R���W�����R���|�[�l���g���܂܂�Ă��Ȃ��Ƃ�
	if (gameObject->GetComponents<Collision>().empty())
	{
		Destroy(this);
		return;
	}

	// �X�V�Ώۂɒǉ�����
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �I��
//=============================================================
void RigidBody::Uninit()
{
	// �X�V�Ώۂɒǉ�����
	if (gameObject != nullptr && gameObject->GetComponent<Collision>() != nullptr)
	{
		gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
	}

	// ���[�V�����X�e�[�g��j������
	if (m_motionState != nullptr)
	{
		delete m_motionState;
		m_motionState = nullptr;
	}
}

//=============================================================
// ���W�b�g�{�f�B���擾����
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
// ���[�V�����X�e�[�g��ݒ肷��
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
