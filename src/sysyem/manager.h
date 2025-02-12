//------------------------------------------------------------
// @file		manager.h
// @brief	�}�l�[�W���[
// @detail	�V�X�e���̊Ǘ����s���܂�
//------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"

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

	//@brief �C���X�^���X�̎擾
	static Manager* getInstance()
	{
		static Manager instance;
		return &instance;
	}
private:
	Renderer* m_renderer;		// �����_���[
};

#endif // !_MANAGER_H_
