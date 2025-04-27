//------------------------------------------------------------
// @file			collider.cpp
// @brief		�R���C�_�[
// @detail	�����蔻��̌`��
//------------------------------------------------------------
#include "collider.h"
#include "collision.h"

//=============================================================
// �R���X�g���N�^
//=============================================================
Collider::Collider() :
	m_offset(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotation(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),
	m_shape(nullptr)
{
}

//=============================================================
// ������
//=============================================================
void Collider::Init()
{
	// �R���W�����R���|�[�l���g�������ǉ�����
	if (gameObject->GetComponents<Collision>().empty())
	{
		gameObject->AddComponent<Collision>();
	}
}

//=============================================================
// �I��
//=============================================================
void Collider::Uninit()
{
	// �V�F�C�v��j������
	if (m_shape != nullptr)
	{
		if (gameObject != nullptr)
		{
			btCompoundShape* shape = gameObject->GetComponent<Collision>()->GetShape();
			if (shape != nullptr)
			{
				shape->removeChildShape(m_shape);
			}
		}

		// �폜
		delete m_shape;
		m_shape = nullptr;
	}
}

//=============================================================
// ���[�J���p�������g�����X�t�H�[���Ƃ��Ď擾���܂�
//=============================================================
btTransform Collider::GetLocalTransform()
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(m_offset.x, m_offset.y, m_offset.z));

	// ��]
	btQuaternion quaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w);
	localTrans.setRotation(quaternion);

	return localTrans;
}


//=============================================================
// �{�b�N�X�R���C�_�[
//=============================================================
void BoxCollider::AddShape(btCompoundShape* shapes)
{
	Collider::Uninit();

	// �V�F�C�v��ǉ�����
	m_shape = new btBoxShape(btVector3(m_size.x, m_size.y, m_size.z));
	shapes->addChildShape(GetLocalTransform(), m_shape);
}

//=============================================================
// �{�b�N�X�R���C�_�[ : �T�C�Y�ύX
//=============================================================
void BoxCollider::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �X�t�B�A�R���C�_�[
//=============================================================
void SphereCollider::AddShape(btCompoundShape* shapes)
{
	Collider::Uninit();

	// �V�F�C�v��ǉ�����
	m_shape = new btSphereShape(m_radius);
	shapes->addChildShape(GetLocalTransform(), m_shape);
}

//=============================================================
// �X�t�B�A�R���C�_�[ : ���a�ύX
//=============================================================
void SphereCollider::SetRadius(const float& radius)
{
	m_radius = radius;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �J�v�Z���R���C�_�[
//=============================================================
void CapsuleCollider::AddShape(btCompoundShape* shapes)
{
	Collider::Uninit();

	// �V�F�C�v��ǉ�����
	m_shape = new btCapsuleShape(m_radius, m_height);
	shapes->addChildShape(GetLocalTransform(), m_shape);
}

//=============================================================
// �J�v�Z���R���C�_�[ : ���a�ύX
//=============================================================
void CapsuleCollider::SetRadius(const float& radius)
{
	m_radius = radius;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �J�v�Z���R���C�_�[ : �����ύX
//=============================================================
void CapsuleCollider::SetHeight(const float& height)
{
	m_height = height;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �~���R���C�_�[
//=============================================================
void CylinderCollider::AddShape(btCompoundShape* shapes)
{
	Collider::Uninit();

	// �V�F�C�v��ǉ�����
	m_shape = new btCylinderShape(btVector3(m_radius, m_height, m_radius));
	shapes->addChildShape(GetLocalTransform(), m_shape);
}

//=============================================================
// �~���R���C�_�[ : ���a�ύX
//=============================================================
void CylinderCollider::SetRadius(const float& radius)
{
	m_radius = radius;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �~���R���C�_�[ : �����ύX
//=============================================================
void CylinderCollider::SetHeight(const float& height)
{
	m_height = height;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �~���R���C�_�[
//=============================================================
void ConeCollider::AddShape(btCompoundShape* shapes)
{
	Collider::Uninit();

	// �V�F�C�v��ǉ�����
	m_shape = new btConeShape(m_radius, m_height);
	shapes->addChildShape(GetLocalTransform(), m_shape);
}

//=============================================================
// �~���R���C�_�[ : ���a�ύX
//=============================================================
void ConeCollider::SetRadius(const float& radius)
{
	m_radius = radius;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}

//=============================================================
// �~���R���C�_�[ : �����ύX
//=============================================================
void ConeCollider::SetHeight(const float& height)
{
	m_height = height;
	gameObject->GetComponent<Collision>()->GetUpdateFlag() = true;
}
