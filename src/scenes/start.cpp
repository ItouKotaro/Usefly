//------------------------------------------------------------
// @file		start.cpp
// @brief	�ŏ��̃V�[��
// @detail	�N������ɌĂ΂��V�[���̏����ł�
//------------------------------------------------------------
#include "start.h"
#include "sysyem/manager.h"

// �V�[���̃C���N���[�h
#include "title.h"

//=============================================================
// ������
//=============================================================
void StartScene::Init()
{
	// �V�[���}�l�[�W���[���擾����
	auto sceneManager = Manager::getInstance()->getSceneManager();

	// �V�[���̓o�^
	sceneManager->registerScene<TitleScene>();

	// �J��
	sceneManager->setScene<TitleScene>();
}
