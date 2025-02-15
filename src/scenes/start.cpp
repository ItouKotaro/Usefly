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
	auto sceneManager = Manager::GetInstance()->GetSceneManager();

	// �V�[���̓o�^
	sceneManager->RegisterScene<TitleScene>();

	// �J��
	sceneManager->SetScene<TitleScene>();
}
