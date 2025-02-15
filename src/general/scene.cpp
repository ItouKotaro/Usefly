//------------------------------------------------------------
// @file		scene.cpp
// @brief	�V�[��
// @detail	�V�[���̊Ǘ����s���܂�
//------------------------------------------------------------
#include "scene.h"
#include "scenes/start.h"

//=============================================================
// ������
//=============================================================
void SceneManager::Init()
{
	// �ŏ��̃V�[����o�^����
	this->registerScene<StartScene>();

	// �ŏ��̃V�[���ɑJ�ڂ���
	this->setScene<StartScene>();
}

//=============================================================
// �X�V
//=============================================================
void SceneManager::Update()
{
	// ���̃V�[��������Ƃ��ɃV�[����ύX����
	changeScene();
}

//=============================================================
// ���ׂĉ������
//=============================================================
void SceneManager::AllRelease()
{
	// ���݂̃V�[�����I������
	if (m_currentScene != nullptr)
	{
		// �I������
		m_currentScene->Uninit();
		m_currentScene = nullptr;
	}

	// �o�^����Ă���V�[�������ׂĉ������
	for (auto itr = m_scenes.begin(); itr != m_scenes.end(); itr++)
	{
		delete* itr;
		*itr = nullptr;
	}
	m_scenes.clear();
}

//=============================================================
// �Q�[���I�u�W�F�N�g��j������
//=============================================================
void SceneManager::releaseGameObjects()
{
	// �Q�[���I�u�W�F�N�g���擾����
	auto gameObjectList = GameObject::getAllGameObjects();

	for (auto itr = gameObjectList.begin(); itr != gameObjectList.end(); itr++)
	{
		if ((*itr)->tag != TAG_NODESTROY)
		{
			Object::Destroy(*itr);
		}
	}
}

//=============================================================
// �V�[����ύX����
//=============================================================
void SceneManager::changeScene()
{
	// ���̃V�[�����ݒ肳��Ă��Ȃ��Ƃ��̓X�L�b�v����
	if (m_nextScene == nullptr)
	{
		return;
	}

	// ���܂ł̃V�[�����I������
	if (m_currentScene != nullptr)
	{
		// �I������
		m_currentScene->Uninit();

		// ���O�𑗐M����
		Log::sendLog("�V�[�� \"" + static_cast<std::string>(typeid(*m_currentScene).name()) + "\" ���I�����܂���");

		// ���݂̃V�[������ɂ���
		m_currentScene = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	if (m_isReleaseObjects)
	{
		releaseGameObjects();
	}

	// �V�����V�[�������݂̃V�[���ɂ���
	m_currentScene = m_nextScene;
	m_nextScene = nullptr;
	if (m_currentScene != nullptr)
	{
		// ���O�𑗐M����
		Log::sendLog("�V�[�� \"" + static_cast<std::string>(typeid(*m_currentScene).name()) + "\" �ɑJ�ڂ��܂���");

		// ����������
		m_currentScene->Init();

		return;
	}

	// ���s�����Ƃ�
	Log::sendLog("�V�[���̑J�ڂɎ��s���܂���", Log::TYPE_ERROR);
}
