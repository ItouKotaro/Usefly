//------------------------------------------------------------
// @file		main.h
// @brief	���C������
// @detail	�E�B���h�E�̍쐬�⃁�C�����[�v�������s���܂�
//------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

 // �}�N����`
#define CLASS_NAME			"WindowClass"		// �N���X��
#define WINDOW_NAME	"Karate Exorcist"	// �E�B���h�E��

// �C���N���[�h
#include <thread>

//@brief �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//@brief ���C���N���X
class Main final
{
public:
	~Main();

	//@brief �C���X�^���X���擾����
	static Main& GetInstance()
	{
		static Main instance;
		return instance;
	}

	//@brief �X���b�h�̊J�n
	void ThreadStart();
	//@brief �X���b�h�̏I����҂�
	void ThreadJoin();

	//@brief �f���^�^�C�����擾����
	float GetDeltaTime() { return m_deltaTime; }
	//@brief FPS�l���擾����
	int GetFPS() { return m_fps; }
	//@brief �E�B���h�E�̃A�N�e�B�u��Ԃ��擾����
	bool IsActiveWindow();
	//@brief �A�v���P�[�V�������I������
	void ExitApplication();
	//@brief �J�[�\���̕\����Ԃ�ύX����
	void SetShowCursor(const bool& show);

	//@brief �J�[�\���ʒu
	struct CursorPos
	{
		long x;
		long y;
	};

	//@brief �N���C�A���g���̃J�[�\���ʒu���擾����
	CursorPos GetCursorClientPos();
	//@brief �N���C�A���g���̃J�[�\���ʒu��ݒ肷��
	void SetCursorClientPos(long x, long y);

	//@brief �E�B���h�E�T�C�Y���擾����
	D3DXVECTOR2 GetWindowSize();
	//@brief �E�B���h�E�n���h�����擾����
	HWND GetHWND();
private:
	//@brief �R���X�g���N�^
	Main();

	//@brief ���C�����[�v
	void MainLoop();

	std::thread* m_thread;		// �X���b�h
	DWORD m_currentTime;		// ���ݎ���
	DWORD m_execLastTime;	// �O��̍X�V����
	DWORD m_fpsLastTime;		// �O���FPS�X�V����
	int m_frameCount;				// �t���[���̃J�E���g

	float m_deltaTime;				// �f���^�^�C��
	int m_fps;							// FPS�l
};

#endif // !_MAIN_H_