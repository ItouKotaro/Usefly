//------------------------------------------------------------
// @file		scene.h
// @brief	�V�[��
// @detail	�V�[���̊Ǘ����s���܂�
//------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//@brief �V�[���i���j
class Scene
{
public:
	//@brief ������
	virtual void Init() {}
	//@brief �I��
	virtual void Uninit() {}
	//@brief �X�V
	virtual void Update() {}
private:

};

//@brief �V�[���Ǘ��N���X
class SceneManager final
{
public:
	//@brief ������
	void Init();
	//@brief �X�V
	void Update();

	//@brief �V�[����ύX����
	template<class T> bool setScene(bool releaseObjects = true)
	{
		// ���̃V�[�����L���[�ɓ����
		m_nextScene = getScene<T>();
		m_isReleaseObjects = releaseObjects;

		// �V�[���̕ύX�悪���݂̃V�[���ƈ�v����Ƃ�
		if (m_nextScene == m_currentScene)
		{
			Log::sendLog("�V�[���̕ύX�悪���݂̃V�[���ƈ�v���Ă��܂��i" + static_cast<std::string>(typeid(T).name()) + "�j", Log::TYPE_WARNING);
			return false;
		}

		// ����
		return true;
	}

	//@brief �V�[�����擾����
	template<class T> T* getScene()
	{
		// �N���X����v����V�[����������
		for (auto itr = m_scenes.begin(); itr != m_scenes.end(); itr++)
		{
			if (typeid(T) == typeid(**itr))
			{
				return static_cast<T*>(*itr);
			}
		}

		// ������Ȃ������Ƃ�
		return nullptr;
	}

	//@brief �V�[����o�^����
	template<class T> bool registerScene()
	{
		// ���ɓo�^����Ă��Ȃ������m�F����
		for (auto itr = m_scenes.begin(); itr != m_scenes.end(); itr++)
		{
			if (typeid(T) == typeid(**itr))
			{ // �o�^�ς݂̂Ƃ�
				Log::sendLog("�o�^�ς݂̃V�[�� \"" + static_cast<std::string>(typeid(T).name()) + "\" ���ēo�^���悤�Ƃ��܂���", Log::TYPE_WARNING);
				return false;
			}
		}

		// �V�����o�^����
		Scene* addScene = new T();
		m_scenes.push_back(addScene);
		Log::sendLog("�V�[�� \"" + static_cast<std::string>(typeid(T).name()) + "\" ��o�^���܂���");

		return true;
	}

	//@brief �V�[�������ׂĉ������
	void AllRelease();
private:
	//@brief �Q�[���I�u�W�F�N�g��j������
	void releaseGameObjects();

	//@brief �L���[�ɓ����Ă���V�[���ɕύX����
	void changeScene();

	Scene* m_currentScene;				// ���݂̃V�[��
	Scene* m_nextScene;					// ���̃V�[���i�L���[�j
	bool m_isReleaseObjects;					// ���̃V�[���Ɉڍs����Ƃ�������邩
	std::vector<Scene*> m_scenes;		// �V�[��
};

#endif // !_SCENE_H_
