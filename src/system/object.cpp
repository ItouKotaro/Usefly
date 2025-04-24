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
}

//=============================================================
// �f�X�t���O�̃I�u�W�F�N�g��j������
//=============================================================
void Object::ReleaseDeathFlag()
{
	int deathCounter = 0;	// �j�������f�X�t���O�̃J�E���g
	do
	{
		// �f�X�J�E���^�[�����Z�b�g����
		deathCounter = 0;

		auto itr = m_objects.begin();
		while (itr != m_objects.end())
		{
			Object* obj = *itr;
			if (obj->m_deathFlag)
			{
				obj->Release();
				delete obj;
				itr = m_objects.erase(itr);

				deathCounter++;
			}
			else
			{
				itr++;
			}
		}
	} while (deathCounter > 0);
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
