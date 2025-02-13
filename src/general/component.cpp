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
// �������
//=============================================================
void Component::Release()
{
	// �I���������s��
	this->Uninit();

	// �R���|�[�l���g����������
	gameObject->DetachComponent(this);
}
