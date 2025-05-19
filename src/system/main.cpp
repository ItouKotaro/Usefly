//------------------------------------------------------------
// @file		main.cpp
// @brief	���C������
// @detail	�E�B���h�E�̍쐬�⃁�C�����[�v�������s���܂�
//------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"

 // �������[���[�N���o
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define FIND_MEM_LEAKS
#endif
#ifdef FIND_MEM_LEAKS
#define _NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define _NEW new
#endif

// �O���[�o���ϐ��̏�����
bool g_isActiveWindow = true;		// �E�B���h�E���A�N�e�B�u��Ԃ�
bool g_isEnded = false;					// �I����Ԃ�
bool g_showCursor = true;				// �J�[�\���̕\�����
bool g_beforeShowCursor = true;	// �O��̃J�[�\���\�����
HWND g_hwnd = nullptr;				// �E�B���h�E�n���h���i���ʎq�j

 //=============================================================
 // ���C���֐�
 //=============================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	// �������[���[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1767);
#endif

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						// �������T�C�Y
		CS_CLASSDC,									// �E�B���h�E�̃X�^�C��
		WindowProc,										// �E�B���h�E�̃v���V�[�W��
		0,
		0,
		hInstance,											// �C���X�^���X�n���h��
		LoadIcon(nullptr, IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(nullptr,IDC_ARROW),			// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		nullptr,												// ���j���[�o�[
		CLASS_NAME,									// �E�B���h�E�N���X�̖��O
		LoadIcon(nullptr, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	MSG msg;			// ���b�Z�[�W���i�[����ϐ�

	// �E�B���h�E�̍��W���i�[
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	g_hwnd = CreateWindowEx(
		0,															// �g���E�B���h�E�X�^�C��
		CLASS_NAME,										// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,								// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,								// �E�B���h�E�̍����X���W
		CW_USEDEFAULT,								// �E�B���h�E�̍����Y���W
		(rect.right - rect.left),							// �E�B���h�E�̕�
		(rect.bottom - rect.top),						// �E�B���h�E�̍���
		nullptr,													// �e�E�B���h�E�̃n���h��
		nullptr,													// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,											// �C���X�^���X�o���h��
		nullptr													// �E�B���h�E�쐬�f�[�^
	);

	// �E�B���h�E�̕\��
	ShowWindow(g_hwnd, nCmdShow);		// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(g_hwnd);						// �N���C�A���g�̈���X�V

	// �}�l�[�W���[�̏�����
	Manager::GetInstance()->Init(hInstance, g_hwnd);

	// Main�̎擾
	Main& mainApp = Main::GetInstance();

	// �X���b�h�J�n
	mainApp.ThreadStart();

	// ���b�Z�[�W���[�v
	while (!g_isEnded)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{ // Windows�̏���
			if (msg.message == WM_QUIT)
			{ // WM_QUIT���b�Z�[�W
				g_isEnded = true;
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		// �A�N�e�B�u���̍X�V
		g_isActiveWindow = GetActiveWindow() != NULL;

		// �J�[�\���̕\���ݒ�̍X�V
		if (g_showCursor != g_beforeShowCursor)
		{
			ShowCursor(g_showCursor ? TRUE : FALSE);
			g_beforeShowCursor = g_showCursor;
		}
	}

	// ���C�����[�v�̃X���b�h���I���܂ő҂�
	mainApp.ThreadJoin();

	// �}�l�[�W���[�̏I��
	Manager::GetInstance()->Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================
// �E�B���h�E�v���V�[�W��
//=============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto hdc = GetDC(hWnd);

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //����̏�����Ԃ�
}


//=============================================================
// �R���X�g���N�^
//=============================================================
Main::Main()
{
	// ����\��ݒ�
	timeBeginPeriod(1);
	m_currentTime = 0;
	m_execLastTime = timeGetTime();
	m_deltaTime = 0.0f;

	// FPS�v���̏�����
	m_frameCount = 0;
	m_fpsLastTime = timeGetTime();
	m_fps = 0;
}

//=============================================================
// �f�X�g���N�^
//=============================================================
Main::~Main()
{
	// ����\��߂�
	timeEndPeriod(1);

	// �X���b�h��j������
	if (m_thread != nullptr)
	{
		delete m_thread;
		m_thread = nullptr;
	}
}

//=============================================================
// �X���b�h�̊J�n
//=============================================================
void Main::ThreadStart()
{
	// �X���b�h���쐬����
	m_thread = new std::thread(&Main::MainLoop, this);
	Log::SendLog("���C�����[�v�̃X���b�h���J�n���܂���");
}

//=============================================================
// �X���b�h���I������܂ő҂�
//=============================================================
void Main::ThreadJoin()
{
	if (m_thread != nullptr)
	{
		m_thread->join();
	}

	Log::SendLog("���C�����[�v�̃X���b�h���I�����܂���");
}

//=============================================================
// ���C�����[�v
//=============================================================
void Main::MainLoop()
{
	while (!g_isEnded)
	{
		// ���ݎ������擾
		m_currentTime = timeGetTime();

		// FPS�l�̌v�Z
		if ((m_currentTime - m_fpsLastTime) >= 500)
		{ // 0.5�b�o�ߖ�
			m_fps = (m_frameCount * 1000) / (m_currentTime - m_fpsLastTime);
			m_fpsLastTime = m_currentTime;							// �v�������������L�^
			m_frameCount = 0;												// �t���[���J�E���g���N���A
		}

		// �X�V
		if ((m_currentTime - m_execLastTime) >= (1000 / 60))
		{
			// �f���^�^�C����ݒ肷��
			m_deltaTime = (m_currentTime - m_execLastTime) * 0.001f;

			//�����J�n����
			m_execLastTime = m_currentTime;

			// �X�V����
			Manager::GetInstance()->Update();

			// �`�揈��
			Manager::GetInstance()->Draw();

			// �t���[���J�E���g�����Z
			m_frameCount++;
		}
	}
}

//=============================================================
// �A�N�e�B�u�E�B���h�E��
//=============================================================
bool Main::IsActiveWindow()
{
	return g_isActiveWindow;
}

//=============================================================
// �A�v���P�[�V�����I������
//=============================================================
void Main::ExitApplication()
{
	g_isEnded = true;
}

//=============================================================
// �J�[�\���̕\��
//=============================================================
void Main::SetShowCursor(const bool& show)
{
	g_showCursor = show;
}

//=============================================================
// �N���C�A���g���̃J�[�\���̈ʒu���擾����
//=============================================================
Main::CursorPos Main::GetCursorClientPos()
{
	POINT points;
	GetCursorPos(&points);

	// �X�N���[����Ō�������̍��W���擾����
	POINT startPos;
	startPos.x = 0;
	startPos.y = 0;
	ClientToScreen(Manager::GetInstance()->GetRenderer()->GetHWND(), &startPos);

	CursorPos pos;
	pos.x = points.x - startPos.x;
	pos.y = points.y - startPos.y;

	// ��ʃT�C�Y���l�����ĕϊ�����
	D3DXVECTOR2 rect = GetWindowSize();
	pos.x = static_cast<long>(pos.x * static_cast<float>(SCREEN_WIDTH / (float)rect.x));
	pos.y = static_cast<long>(pos.y * static_cast<float>(SCREEN_HEIGHT / (float)rect.y));
	return pos;
}

//=============================================================
// �N���C�A���g���̃J�[�\���̈ʒu��ݒ肷��
//=============================================================
void Main::SetCursorClientPos(long x, long y)
{
	CursorPos pos;
	pos.x = x;
	pos.y = y;

	// �X�N���[����Ō�������̍��W���擾����
	POINT startPos;
	startPos.x = 0;
	startPos.y = 0;
	ClientToScreen(Manager::GetInstance()->GetRenderer()->GetHWND(), &startPos);

	D3DXVECTOR2 rect = GetWindowSize();
	pos.x = static_cast<long>(pos.x	 * (rect.x / (float)SCREEN_WIDTH));
	pos.y = static_cast<long>(pos.y * (rect.y / (float)SCREEN_HEIGHT));

	pos.x += startPos.x;
	pos.y += startPos.y;

	SetCursorPos(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

//=============================================================
// �E�B���h�E�T�C�Y�̎擾
//=============================================================
D3DXVECTOR2 Main::GetWindowSize()
{
	RECT rect;
	GetWindowRect(g_hwnd, &rect);
	return D3DXVECTOR2(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
}

//=============================================================
// �E�B���h�E�n���h���̎擾
//=============================================================
HWND Main::GetHWND()
{
	return g_hwnd;
}
