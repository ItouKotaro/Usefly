//------------------------------------------------------------
// @file		transform.cpp
// @brief	�g�����X�t�H�[��
// @detail	�ʒu���]�Ȃǂ̏������N���X
//------------------------------------------------------------
#include "transform.h"

//=============================================================
// �I�C���[�p�ŉ�]���擾����
//=============================================================
D3DXVECTOR3 Transform::GetEulerAngle()
{
	return QuaternionToEulerAngle(rotation);
}

//=============================================================
// �I�C���[�p�ŉ�]��ݒ肷��
//=============================================================
void Transform::SetEulerAngle(float x, float y, float z)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationYawPitchRoll(&q, y, x, z);
	rotation = q;
}

//=============================================================
// ���[���h��̈ʒu���擾����
//=============================================================
D3DXVECTOR3 Transform::GetWorldPosition()
{
	D3DXMATRIX mtx = GetMatrix();
	return D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
}

//=============================================================
// ���[���h��̉�]���擾����
//=============================================================
D3DXQUATERNION Transform::GetWorldRotation()
{
	D3DXQUATERNION worldQuaternion;
	D3DXQuaternionIdentity(&worldQuaternion);

	Transform* worldTransform = this;
	do
	{
		D3DXQUATERNION q = worldTransform->rotation;
		D3DXQuaternionMultiply(&worldQuaternion, &worldQuaternion, &q);

		// ���̐e�ɐi��
		worldTransform = worldTransform->GetParent();
	} while (worldTransform != nullptr);

	// ���K��
	D3DXQuaternionNormalize(&worldQuaternion, &worldQuaternion);

	return worldQuaternion;
}

//=============================================================
// ���[���h��̃I�C���[�p���擾����
//=============================================================
D3DXVECTOR3 Transform::GetWorldEulerAngle()
{
	return QuaternionToEulerAngle(GetWorldRotation());
}

//=============================================================
// ���[���h��̃X�P�[�����擾����
//=============================================================
D3DXVECTOR3 Transform::GetWorldScale()
{
	// �e�̃��[���h���W�����[�J�����W�Ɋ|����
	D3DXVECTOR3 worldScale = { 1.0f, 1.0f, 1.0f };
	Transform* worldTransform = this;
	do
	{
		// ���W���|����
		worldScale.x *= worldTransform->scale.x;
		worldScale.y *= worldTransform->scale.y;
		worldScale.z *= worldTransform->scale.z;

		// ���̐e�ɐi��
		worldTransform = worldTransform->GetParent();
	} while (worldTransform != nullptr);

	return worldScale;
}

//=============================================================
// �}�g���b�N�X���擾����
//=============================================================
D3DXMATRIX& Transform::GetMatrix()
{
	// �ϐ�
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_matrix);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&m_matrix, &m_matrix, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationQuaternion(&mtxRot, &rotation);
	D3DXMatrixMultiply(&m_matrix, &m_matrix, &mtxRot);
	//31 32 33�őO���������擾�ł���

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, position.x, position.y, position.z);
	D3DXMatrixMultiply(&m_matrix, &m_matrix, &mtxTrans);

	if (m_parent != nullptr)
	{
		D3DXMATRIX mtxParent;
		mtxParent = m_parent->GetMatrix();
		D3DXMatrixMultiply(&m_matrix, &m_matrix, &mtxParent);
	}

	return m_matrix;
}

//=============================================================
// �ʒu���}�g���b�N�X���擾����
//=============================================================
D3DXMATRIX Transform::GetTranslationMatrix()
{
	D3DXMATRIX mtx;
	D3DXVECTOR3 wPos = GetWorldPosition();
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixTranslation(&mtx, wPos.x, wPos.y, wPos.z);
	return mtx;
}

//=============================================================
// ��]���}�g���b�N�X���擾����
//=============================================================
D3DXMATRIX Transform::GetRotationMatrix()
{
	D3DXMATRIX mtx;
	D3DXQUATERNION wQuaternion = GetWorldRotation();
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationQuaternion(&mtx, &wQuaternion);
	return mtx;
}

//=============================================================
// ���Z�q ==
//=============================================================
bool Transform::operator==(Transform value)
{
	return (position == value.position &&
		rotation == value.rotation &&
		scale == value.scale &&
		size == value.size &&
		m_parent == value.m_parent);
}

//=============================================================
// ���Z�q !=
//=============================================================
bool Transform::operator!=(Transform value)
{
	return !(position == value.position &&
		rotation == value.rotation &&
		scale == value.scale &&
		size == value.size &&
		m_parent == value.m_parent);
}

//=============================================================
// ���Z�q =
//=============================================================
Transform& Transform::operator=(Transform value)
{
	position = value.position;
	rotation = value.rotation;
	scale = value.scale;
	size = value.size;
	m_parent = value.m_parent;
	return *this;
}

//=============================================================
// �N�H�[�^�j�I�����I�C���[�p�ɕϊ�����
//=============================================================
D3DXVECTOR3 Transform::QuaternionToEulerAngle(D3DXQUATERNION q)
{
	auto sx = -(2 * q.y * q.z - 2 * q.x * q.w);
	auto unlocked = std::abs(sx) < 0.99999f;
	return D3DXVECTOR3(
		std::asin(sx),
		unlocked ? std::atan2(2 * q.x * q.z + 2 * q.y * q.w, 2 * q.w * q.w + 2 * q.z * q.z - 1)
		: std::atan2(-(2 * q.x * q.z - 2 * q.y * q.w), 2 * q.w * q.w + 2 * q.x * q.x - 1),
		unlocked ? std::atan2(2 * q.x * q.y + 2 * q.z * q.w, 2 * q.w * q.w + 2 * q.y * q.y - 1) : 0
	);
}
