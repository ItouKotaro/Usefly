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
}

//=============================================================
// �I��
//=============================================================
void Collision::Uninit()
{
	// �R���W������j������
	if (m_collision != nullptr)
	{
		Manager::GetInstance()->GetPhysics()->GetWorld()->removeCollisionObject(m_collision);
		delete m_collision;
		m_collision = nullptr;
	}

	// �����I�ȃR���|�[�l���g���폜����
	auto rigidBody = gameObject->GetComponent<RigidBody>();
	if (rigidBody != nullptr)
	{
		Destroy(rigidBody);
	}
}

//=============================================================
// �r���h����
//=============================================================
void Collision::Build()
{
	// ���W�b�h�{�f�B���擾����
	auto rigidbody = gameObject->GetComponent<RigidBody>();

	if (rigidbody != nullptr)
	{ // ���W�b�h�{�f�B�̂Ƃ�

	}
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
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}
