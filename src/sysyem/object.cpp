//------------------------------------------------------------
// @file		object.cpp
// @brief	�I�u�W�F�N�g
// @detail	�I�u�W�F�N�g�ނ̊��N���X
//------------------------------------------------------------
#include "object.h"

// �ÓI�����o�ϐ��̏�����
std::vector<Object*> Object::m_objects;

//=============================================================
// �R���X�g���N�^
//=============================================================
Object::Object() : m_deathFlag(false), m_active(true)
{
	// �f�[�^��ǉ�����
	m_objects.push_back(this);
}

//=============================================================
// �f�X�g���N�^
//=============================================================
Object::~Object()
{
	// �f�[�^���폜����
	for (auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		if (*itr == this)
		{
			m_objects.erase(itr);
			break;
		}
	}
}

//=============================================================
// �f�X�t���O�̃I�u�W�F�N�g��j������
//=============================================================
void Object::ReleaseDeathFlag()
{
	int idx = static_cast<int>(m_objects.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		if (m_objects[i]->m_deathFlag)
		{ // ���S�t���O�����Ă���Ƃ�
			m_objects[i]->Release();
			delete m_objects[i];
		}
	}
}

//=============================================================
// ���ׂẴI�u�W�F�N�g��j������
//=============================================================
void Object::AllDestroy()
{
	for (auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		Destroy(*itr);
	}
	
	// �f�X�t���O�̃I�u�W�F�N�g��j������
	ReleaseDeathFlag();
}
