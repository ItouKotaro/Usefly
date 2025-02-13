//------------------------------------------------------------
// @file		component.cpp
// @brief	�R���|�[�l���g
//------------------------------------------------------------
#include "component.h"

//=============================================================
// �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
//=============================================================
void Component::AttachGameObject(GameObject* attachObj)
{
	if (gameObject == nullptr)
	{ // �A�^�b�`����Ă��Ȃ��Ƃ�
		gameObject = attachObj;
		transform = gameObject->transform;
	}
}

//=============================================================
// �Q�[���I�u�W�F�N�g���f�^�b�`����
//=============================================================
void Component::DetachGameObject()
{
	if (gameObject != nullptr)
	{ // �A�^�b�`����Ă���Ƃ�
		GameObject* gameObjectData = gameObject;
		gameObject = nullptr;
		transform = nullptr;
		gameObjectData->DetachComponent(this);
	}
}

//=============================================================
// �������
//=============================================================
void Component::Release()
{
	// �I���������s��
	this->Uninit();

	// �R���|�[�l���g����������
	if (gameObject != nullptr)
	{
		gameObject->DetachComponent(this);
	}
}
