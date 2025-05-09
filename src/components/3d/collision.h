//------------------------------------------------------------
// @file			collision.h
// @brief		�R���W����
// @detail	�����蔻��
//------------------------------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <component.h>
#include "collider.h"

/**
 * @brief �R���W�����R���|�[�l���g
 * @details �����蔻��̕W���R���|�[�l���g�ł��i�`��R���C�_�[��ǉ�����ƁA�����Œǉ�����܂��j
*/
class Collision : public Component
{
public:
	Collision() : m_updateFlag(true), m_collision(nullptr), m_shape(nullptr), m_trigger(false), m_friction(1.0f) {}
	void Init() override;
	void Uninit() override;
	void Update() override;
	void UpdateOldTransform() { m_oldTransform = *transform; }

	//@brief �R���W�����I�u�W�F�N�g���擾����
	btCollisionObject* GetCollision() { return m_collision; }

	//@brief �R���C�_�[���擾����
	btCompoundShape* GetShape() { return m_shape; }

	//@brief �r���h����
	virtual void Build();

	//@brief �g���K�[��ݒ肷��
	void SetTrigger(const bool& enabled);
	//@brief �g���K�[���擾����
	bool GetTrigger() { return m_trigger; }
	//@brief ���C���擾����
	float& GetFriction() { return m_friction; }
	//@brief �X�V�t���O���擾����
	bool& GetUpdateFlag() { return m_updateFlag; }
	//@brief �O��̃g�����X�t�H�[�������擾����
	Transform GetOldTransform() { return m_oldTransform; }
	//@brief �d�Ȃ��Ă���R���W�������擾����
	std::vector<Collision*>& GetOverlappingCollisions() { return m_overlapping; }

protected:
	bool m_updateFlag;					// �X�V�t���O
	btCollisionObject* m_collision;		// �R���W����
	btCompoundShape* m_shape;	// �`��

private:
	//@brief ���킹���R���C�_�[�𐶐�����
	void GenerateColliderShape();

	float m_friction;											// ���C
	bool m_trigger;											// �g���K�[
	Transform m_oldTransform;							// �O��̃g�����X�t�H�[�����
	std::vector<Collision*> m_overlapping;		// �d�Ȃ��Ă���R���W����
};

/**
 * @brief ���W�b�h�{�f�B�R���|�[�l���g�i�R���C�_�[���ɃA�^�b�`���Ă��������j
 * @details ������������悤�ɂȂ�܂�
*/
class RigidBody : public Component
{
public:
	RigidBody() : m_mass(1.0f), m_motionState(nullptr){}
	void Init() override;
	void Uninit() override;

	//@brief ���W�b�h�{�f�B���擾����
	btRigidBody* GetRigidBody();

	//@brief ���ʂ��擾����
	float& GetMass() { return m_mass; }

	//@brief ���[�V�����X�e�[�g���擾����
	void SetMotionState(btMotionState* motionState);

	//@brief ���[�V�����X�e�[�g���擾����
	btMotionState* GetMotionState() { return m_motionState; }

private:
	float m_mass;							// ����
	btMotionState* m_motionState;	// ���[�V�����X�e�[�g
};

//// �S�[�X�g�I�u�W�F�N�g
//class CGhostObject : public Component
//{
//public:
//	void Init() override;							// ������
//	btGhostObject* GetGhostObject();		// �S�[�X�g�I�u�W�F�N�g�̎擾
//	Collision* GetCollision();					// �R���W�����̎擾
//};
//
//// �_������
//class CPoint2PointConstraint : public Component
//{
//public:
//	CPoint2PointConstraint();
//	void Uninit() override;
//	void SetConstraint(btRigidBody* rb1, btRigidBody* rb2, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& pivotInB);
//private:
//	btPoint2PointConstraint* m_p2p;
//};
//
//// �q���W����
//class CHingeConstraint : public Component
//{
//public:
//	CHingeConstraint();
//	void Uninit() override;
//	void SetConstraint(btRigidBody* rb, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& axisInA);
//	void SetConstraint(btRigidBody* rb1, btRigidBody* rb2, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& pivotInB, const D3DXVECTOR3& axisInA, const D3DXVECTOR3& axisInB);
//	btHingeConstraint* GetHinge() { return m_hinge; }
//private:
//	btHingeConstraint* m_hinge;
//};
//
//// 2���q���W����
//class CHinge2Constraint : public Component
//{
//public:
//	CHinge2Constraint();
//	void Uninit() override;
//	void SetConstraint(btRigidBody* rb1, btRigidBody* rb2, D3DXVECTOR3 anchor, D3DXVECTOR3 parentAxis, D3DXVECTOR3 childAxis);
//	btHinge2Constraint* GetHinge2() { return m_hinge2; }
//private:
//	btHinge2Constraint* m_hinge2;
//};
//
//// �R���C�_�[���N���X
//class CCollider : public Component
//{
//public:
//	virtual void AddShapes(btCompoundShape* pShapes) = 0;						// �`��ǉ�
//	void SetOffset(const D3DXVECTOR3& offset) { m_offset = offset; }			// �I�t�Z�b�g�ݒ�
//	D3DXVECTOR3 GetOffset() { return m_offset; }										// �I�t�Z�b�g�擾
//	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }							// ��]�ݒ�
//	D3DXVECTOR3 GetRot() { return m_rot; }												// ��]�擾
//private:
//	D3DXVECTOR3 m_offset;		// ���S
//	D3DXVECTOR3 m_rot;			// ��]
//};
//
//
//// �{�b�N�X�R���C�_�[
//class CBoxCollider : public CCollider
//{
//public:
//	CBoxCollider(D3DXVECTOR3 size = { 1.0f, 1.0f, 1.0f }, D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f }, D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f });		// �R���X�g���N�^
//	void Init() override;																						// ������
//	void AddShapes(btCompoundShape* pShapes) override;									// �`��ǉ�
//
//	void SetSize(const D3DXVECTOR3& size) { m_size = size; }								// �T�C�Y�ݒ�
//	D3DXVECTOR3 GetSize() { return m_size; }														// �T�C�Y�擾
//private:
//	D3DXVECTOR3 m_size;		// �T�C�Y
//};
//
//// ���R���C�_�[
//class CSphereCollider : public CCollider
//{
//public:
//	CSphereCollider(float fRadius = 1.0f, D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f }, D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f });	// �R���X�g���N�^
//	void Init() override;																					// ������
//	void AddShapes(btCompoundShape* pShapes) override;								// �`��ǉ�
//
//	void SetRadius(const float& fRadius) { m_fRadius = fRadius; }						// ���a�ݒ�
//	float GetRadius() { return m_fRadius; }														// ���a�擾
//private:
//	float m_fRadius;		// ���a
//};
//
//// �J�v�Z���R���C�_�[
//class CCapsuleCollider : public CCollider
//{
//public:
//	CCapsuleCollider(float fRadius = 1.0f, float fHeight = 2.0f, D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f }, D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f });	// �R���X�g���N�^
//	void Init() override;																					// ������
//	void AddShapes(btCompoundShape* pShapes) override;								// �`��ǉ�
//
//	void SetRadius(const float& fRadius) { m_fRadius = fRadius; }						// ���a�ݒ�
//	float GetRadius() { return m_fRadius; }														// ���a�擾
//	void SetHeight(const float& fHeight) { m_fHeight = fHeight; }						// �����ݒ�
//	float GetHeight() { return m_fHeight; }														// �����擾
//private:
//	float m_fRadius;		// ���a
//	float m_fHeight;		// ����
//};
//
//// �V�����_�[(�~��) �R���C�_�[
//class CCylinderCollider : public CCollider
//{
//public:
//	CCylinderCollider(float fRadius = 1.0f, float fHeight = 2.0f, D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f }, D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f });	// �R���X�g���N�^
//	void Init() override;																					// ������
//	void AddShapes(btCompoundShape* pShapes) override;								// �`��ǉ�
//
//	void SetRadius(const float& fRadius) { m_fRadius = fRadius; }						// ���a�ݒ�
//	float GetRadius() { return m_fRadius; }														// ���a�擾
//	void SetHeight(const float& fHeight) { m_fHeight = fHeight; }						// �����ݒ�
//	float GetHeight() { return m_fHeight; }														// �����擾
//private:
//	float m_fRadius;		// ���a
//	float m_fHeight;		// ����
//};
//
//// �R�[��(�~��) �R���C�_�[
//class CConeCollider : public CCollider
//{
//public:
//	CConeCollider(float fRadius = 1.0f, float fHeight = 2.0f, D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f }, D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f });	// �R���X�g���N�^
//	void Init() override;																					// ������
//	void AddShapes(btCompoundShape* pShapes) override;								// �`��ǉ�
//
//	void SetRadius(const float& fRadius) { m_fRadius = fRadius; }						// ���a�ݒ�
//	float GetRadius() { return m_fRadius; }														// ���a�擾
//	void SetHeight(const float& fHeight) { m_fHeight = fHeight; }						// �����ݒ�
//	float GetHeight() { return m_fHeight; }														// �����擾
//private:
//	float m_fRadius;		// ���a
//	float m_fHeight;		// ����
//};

#endif // !_COLLISION_H_
