//------------------------------------------------------------
// @file		manager.h
// @brief	�}�l�[�W���[
// @detail	�V�X�e���̊Ǘ����s���܂�
//------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "resource_data.h"
#include "scene.h"

//@brief �Ǘ��N���X
class Manager final
{
public:
	//@brief ������
	void Init(HINSTANCE hInstance, HWND hWnd);
	//@brief �I��
	void Uninit();
	//@brief �X�V
	void Update();
	//@brief �`��
	void Draw();

	//@brief �����_���[���擾����
	Renderer* GetRenderer() { return m_renderer; }
	//@brief ���\�[�X�f�[�^�}�l�[�W���[���擾����
	ResourceDataManager* GetResourceDataManager() { return m_resourceDataManager; }
	//@brief �V�[���}�l�[�W���[���擾����
	SceneManager* GetSceneManager() { return m_sceneManager; }

	//@brief �f�o�C�X���擾����
	LPDIRECT3DDEVICE9 GetDevice() { return m_renderer->GetDevice(); }

	//@brief �C���X�^���X�̎擾
	static Manager* GetInstance()
	{
		static Manager instance;
		return &instance;
	}
private:
	Renderer* m_renderer;											// �����_���[
	ResourceDataManager* m_resourceDataManager;	// ���\�[�X�f�[�^�}�l�[�W���[
	SceneManager* m_sceneManager;							// �V�[���}�l�[�W���[
};

#endif // !_MANAGER_H_
