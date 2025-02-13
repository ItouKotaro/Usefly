//------------------------------------------------------------
// @file		manager.h
// @brief	�}�l�[�W���[
// @detail	�V�X�e���̊Ǘ����s���܂�
//------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "resource_data.h"

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
	Renderer* getRenderer() { return m_renderer; }
	//@brief ���\�[�X�f�[�^���擾����
	ResourceDataManager* getResourceData() { return m_resourceData; }

	//@brief �f�o�C�X���擾����
	LPDIRECT3DDEVICE9 getDevice() { return m_renderer->getDevice(); }

	//@brief �C���X�^���X�̎擾
	static Manager* getInstance()
	{
		static Manager instance;
		return &instance;
	}
private:
	Renderer* m_renderer;								// �����_���[
	ResourceDataManager* m_resourceData;	// ���\�[�X�f�[�^
};

#endif // !_MANAGER_H_
