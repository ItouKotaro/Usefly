//------------------------------------------------------------
// @file		main.h
// @brief	���C������
// @detail	�E�B���h�E�̍쐬�⃁�C�����[�v�������s���܂�
//------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

 // �}�N����`
#define CLASS_NAME			"WindowClass"	// �N���X��
#define WINDOW_NAME	"Usefly"			// �E�B���h�E��

// �C���N���[�h
#include <thread>

//@brief �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//@brief ���C���N���X
class Main final
{
public:
	Main();
	~Main();

	//@brief �X���b�h�̊J�n
	void ThreadStart();
	//@brief �X���b�h�̏I����҂�
	void ThreadJoin();

	//@brief �f���^�^�C�����擾����
	static float getDeltaTime() { return m_deltaTime; }
	//@brief FPS�l���擾����
	static int getFPS() { return m_fps; }
	//@brief �E�B���h�E�̃A�N�e�B�u��Ԃ��擾����
	static bool isActiveWindow();
	//@brief �A�v���P�[�V�������I������
	static void ExitApplication();
	//@brief �J�[�\���̕\����Ԃ�ύX����
	static void setShowCursor(const bool& show);
private:
	//@brief ���C�����[�v
	void MainLoop();

	std::thread* m_thread;		// �X���b�h
	DWORD m_currentTime;	// ���ݎ���
	DWORD m_execLastTime;	// �O��̍X�V����
	DWORD m_fpsLastTime;		// �O���FPS�X�V����
	int m_frameCount;				// �t���[���̃J�E���g

	static float m_deltaTime;	// �f���^�^�C��
	static int m_fps;					// FPS�l
};

#endif // !_MAIN_H_