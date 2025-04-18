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

	// �\�z����
	Build();
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

	// ���W�b�h�{�f�B��
}

//=============================================================
// �I��
//=============================================================
void RigidBody::Uninit()
{
}
