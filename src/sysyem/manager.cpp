//------------------------------------------------------------
// @file		manager.cpp
// @brief	�}�l�[�W���[
// @detail	�V�X�e���̊Ǘ����s���܂�
//------------------------------------------------------------
#include "manager.h"
#include "components/2d/sprite.h"

//=============================================================
// ������
//=============================================================
void Manager::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �����_���[�𐶐�����
	m_renderer = new Renderer();
	m_renderer->Init(hInstance, hWnd);

	// ���\�[�X�f�[�^�𐶐�����
	m_resourceData = new ResourceDataManager();
}

//=============================================================
// �I��
//=============================================================
void Manager::Uninit()
{
	// ���ׂẴI�u�W�F�N�g��j������
	Object::AllDestroy();
	
	// �����_���[���I������
	if (m_renderer != nullptr)
	{
		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = nullptr;
	}

	// ���\�[�X�f�[�^�����ׂĔj������
	if (m_resourceData != nullptr)
	{
		m_resourceData->AllRelease();
		delete m_resourceData;
		m_resourceData = nullptr;
	}

#if OUTPUT_LOG_FILE
	// ���O�������o��
	Log::outputLog();
#endif
}

//=============================================================
// �X�V
//=============================================================
void Manager::Update()
{
	// �Q�[���I�u�W�F�N�g���X�V����
	GameObject::AllUpdate();

	// �����_���[���X�V����
	m_renderer->Update();

	// �f�X�t���O�����Ă���I�u�W�F�N�g��j������
	Object::ReleaseDeathFlag();
}

//=============================================================
// �`��
//=============================================================
void Manager::Draw()
{
	// �����_���[��`�悷��
	m_renderer->Draw();
}
