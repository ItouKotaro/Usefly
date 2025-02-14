//------------------------------------------------------------
// @file		gameobject.cpp
// @brief	�Q�[���I�u�W�F�N�g
// @detail	�R���|�[�l���g�̏����������I�u�W�F�N�g�ł�
//------------------------------------------------------------
#include "gameobject.h"
#include "component.h"
using namespace std;
#include <vector>

// �ÓI�����o�ϐ��̏�����
std::vector<GameObject*> GameObject::m_gameObjects;

//=============================================================
// �R���X�g���N�^
//=============================================================
GameObject::GameObject(std::string vName, std::string vTag)
{
	// ��{���
	this->name = vName;
	this->tag = vTag;

	// �g�����X�t�H�[�����쐬����
	transform = new Transform();

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

	// �g�����X�t�H�[�����폜����
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
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

//=============================================================
// ���ׂẴI�u�W�F�N�g���X�V����
//=============================================================
void GameObject::AllUpdate()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->Update();
	}
}

//=============================================================
// ���ׂẴI�u�W�F�N�g��`�悷��
//=============================================================
void GameObject::AllDraw()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->Draw();
	}
}

//=============================================================
// ���ׂẴI�u�W�F�N�g��UI�`�悷��
//=============================================================
void GameObject::AllDrawUI()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->DrawUI();
	}
}

//=============================================================
// �R���|�[�l���g���f�^�b�`����
//=============================================================
void GameObject::DetachComponent(Component* component)
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if (*itr == component)
		{
			(*itr)->gameObject = nullptr;
			(*itr)->transform = nullptr;
			m_components.erase(itr);
			break;
		}
	}
}

//=============================================================
// �������
//=============================================================
void GameObject::Release()
{
	// �I���������s��
	this->Uninit();

	// �e�q�֌W�̂���I�u�W�F�N�g��j������
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		(*itr)->transform->getParent();
	}

	// �R���|�[�l���g���������
	int idx = static_cast<int>(m_components.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		m_components[i]->Destroy();
		m_components[i]->DetachGameObject();
	}
}
