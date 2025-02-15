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

	// �V�[���}�l�[�W���[�𐶐�����
	m_sceneManager = new SceneManager();
	m_sceneManager->Init();

	// ���\�[�X�f�[�^�}�l�[�W���[�𐶐�����
	m_resourceDataManager = new ResourceDataManager();
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

	// �V�[���}�l�[�W���[���I������
	if (m_sceneManager != nullptr)
	{
		m_sceneManager->AllRelease();
		delete m_sceneManager;
		m_sceneManager = nullptr;
	}

	// ���\�[�X�f�[�^�����ׂĔj������
	if (m_resourceDataManager != nullptr)
	{
		m_resourceDataManager->AllRelease();
		delete m_resourceDataManager;
		m_resourceDataManager = nullptr;
	}

#if OUTPUT_LOG_FILE
	// ���O�������o��
	Log::OutputLog();
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

	// �V�[�����X�V����
	m_sceneManager->Update();

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
