//------------------------------------------------------------
// @file		transform.h
// @brief	�g�����X�t�H�[��
// @detail	�ʒu���]�Ȃǂ̏������N���X
//------------------------------------------------------------
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "d3dx9.h"

//@brief �g�����X�t�H�[���N���X
class Transform
{
public:
	Transform() 
	{
		position = {0.0f, 0.0f, 0.0f};
		D3DXQuaternionIdentity(&rotation);
		scale = scale;
		size = { 1.0f, 1.0f };
		m_parent = nullptr;
	}

	//@brief �e��ݒ肷��
	void SetParent(Transform* parent) { m_parent = parent; }
	//@brief �e���擾����
	Transform* GetParent() { return m_parent; }

	//@brief �I�C���[�p�ŉ�]���擾����
	D3DXVECTOR3 GetEulerAngle();
	//@brief �I�C���[�p�ŉ�]��ݒ肷��
	void SetEulerAngle(float x, float y, float z);
	void SetEulerAngle(D3DXVECTOR3 rotation) { SetEulerAngle(rotation.x, rotation.y, rotation.z); }
	void SetEulerAngle(float fAngle) { SetEulerAngle(GetEulerAngle().x, GetEulerAngle().y, fAngle); }

	//@brief ���[���h��̈ʒu���擾����
	D3DXVECTOR3 GetWorldPosition();
	//@brief ���[���h��̉�]���擾����
	D3DXQUATERNION GetWorldRotation();
	//@brief ���[���h��̃I�C���[�p���擾����
	D3DXVECTOR3 GetWorldEulerAngle();
	//@brief ���[���h��̃X�P�[�����擾����
	D3DXVECTOR3 GetWorldScale();

	//@brief �}�g���b�N�X���擾����
	D3DXMATRIX& GetMatrix();
	//@brief �ʒu���}�g���b�N�X���擾����
	D3DXMATRIX GetTranslationMatrix();
	//@brief ��]���}�g���b�N�X���擾����
	D3DXMATRIX GetRotationMatrix();

	D3DXVECTOR3 position;			// �ʒu
	D3DXQUATERNION rotation;	// ��]
	D3DXVECTOR3 scale;				// �X�P�[��
	D3DXVECTOR2 size;				// �T�C�Y

	//@brief ���Z�q ==
	bool operator==(Transform value);

	//@brief ���Z�q !=
	bool operator!=(Transform value);

	//@brief ���Z�q =
	Transform& operator=(Transform value);

private:
	//@brief �N�H�[�^�j�I�����I�C���[�p�ɕϊ�����
	D3DXVECTOR3 QuaternionToEulerAngle(D3DXQUATERNION q);

	D3DXMATRIX m_matrix;			// �}�g���b�N�X
	Transform* m_parent;			// �e
};

#endif // !_TRANSFORM_H_
