//------------------------------------------------------------
// @file		gameobject.cpp
// @brief	�Q�[���I�u�W�F�N�g
// @detail	�R���|�[�l���g�̏����������I�u�W�F�N�g�ł�
//------------------------------------------------------------
#include "gameobject.h"
#include "component.h"

// �ÓI�����o�ϐ��̏�����
std::vector<GameObject*> GameObject::m_gameObjects;

//=============================================================
// �R���X�g���N�^
//=============================================================
GameObject::GameObject()
{
	// ���X�g�ɒǉ�����
	m_gameObjects.push_back(this);
}

//=============================================================
// �f�X�g���N�^
//=============================================================
GameObject::~GameObject()
{
	// ���X�g����폜����
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == this)
		{
			m_gameObjects.erase(itr);
			break;
		}
	}
}

//=============================================================
// ������
//=============================================================
void GameObject::Init()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Init();
	}
}

//=============================================================
// �I��
//=============================================================
void GameObject::Uninit()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Uninit();
	}
}

//=============================================================
// �X�V
//=============================================================
void GameObject::Update()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Update();
	}
}

//=============================================================
// �`��
//=============================================================
void GameObject::Draw()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Draw();
	}
}

//=============================================================
// �`��UI
//=============================================================
void GameObject::DrawUI()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->DrawUI();
	}
}