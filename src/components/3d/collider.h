//------------------------------------------------------------
// @file			collider.h
// @brief		�R���C�_�[
// @detail	�����蔻��̌`��
//------------------------------------------------------------
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "component.h"

/**
 * @brief �R���C�_�[�e���v���[�g
*/
class Collider : public Component
{
public:
	Collider();
	void Init() override;
	void Uninit() override;

	//@brief �V�F�C�v�ɒǉ�����
	virtual void AddShape(btCompoundShape* shapes) = 0;

	//@brief �I�t�Z�b�g��ݒ肷��
	void SetOffset(const D3DXVECTOR3& offset) { m_offset = offset; }
	//@brief ��]��ݒ肷��
	void SetRotation(const D3DXQUATERNION& rotation) { m_rotation = rotation; }
protected:
	//@brief ���[�J���p�������g�����X�t�H�[���Ƃ��Ď擾���܂�
	btTransform GetLocalTransform();

	D3DXVECTOR3 m_offset;			// ���S
	D3DXQUATERNION m_rotation;	// ��]
	btCollisionShape* m_shape;		// �`��
};

/**
 * @brief �{�b�N�X�R���C�_�[
 * @details �����`�̃R���C�_�[�ł�
*/
class BoxCollider : public Collider
{
public:
	BoxCollider() : m_size(D3DXVECTOR3(1.0f, 1.0f, 1.0f)){}
	void AddShape(btCompoundShape* shapes) override;
	void SetSize(const D3DXVECTOR3& size);
private:
	D3DXVECTOR3 m_size;	// �T�C�Y
};

/**
 * @brief �X�t�B�A�R���C�_�[
 * @details ���̃R���C�_�[�ł�
*/
class SphereCollider : public Collider
{
public:
	SphereCollider() : m_radius(1.0f){}
	void AddShape(btCompoundShape* shapes) override;
	void SetRadius(const float& radius);
private:
	float m_radius;	// ���a
};

/**
 * @brief �J�v�Z���R���C�_�[
 * @details �J�v�Z���̃R���C�_�[�ł�
*/
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider() : m_radius(1.0f), m_height(2.0f) {}
	void AddShape(btCompoundShape* shapes) override;
	void SetRadius(const float& radius);
	void SetHeight(const float& height);
private:
	float m_radius;	// ���a
	float m_height;	// ����
};

/**
 * @brief �~���R���C�_�[
 * @details �~���̃R���C�_�[�ł�
*/
class CylinderCollider : public Collider
{
public:
	CylinderCollider() : m_radius(1.0f), m_height(2.0f) {}
	void AddShape(btCompoundShape* shapes) override;
	void SetRadius(const float& radius);
	void SetHeight(const float& height);
private:
	float m_radius;	// ���a
	float m_height;	// ����
};

/**
 * @brief �~���R���C�_�[
 * @details �~���̃R���C�_�[�ł�
*/
class ConeCollider : public Collider
{
public:
	ConeCollider() : m_radius(1.0f), m_height(2.0f) {}
	void AddShape(btCompoundShape* shapes) override;
	void SetRadius(const float& radius);
	void SetHeight(const float& height);
private:
	float m_radius;	// ���a
	float m_height;	// ����
};


#endif // !_COLLIDER_H_
