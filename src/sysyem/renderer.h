//------------------------------------------------------------
// @file		renderer.h
// @brief	�����_���[
// @detail	�`����s���V�X�e���ł�
//------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

//-----------------------------------------------------------
// �ݒ荀��

// �E�B���h�E�T�C�Y�i���j
#define DEFAULT_SCREEN_WIDTH					(1920)

// �E�B���h�E�T�C�Y�i�����j
#define DEFAULT_SCREEN_HEIGHT				(1080)

// �E�B���h�E��
#define RENDERER_WINDOWED		(TRUE)

//-----------------------------------------------------------


//@brief �����_���[�N���X
class Renderer final
{
public:
	Renderer() : m_d3d(nullptr), m_d3dDevice(nullptr), m_hwnd(nullptr) {}
	~Renderer() {}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();
private:
	LPDIRECT3D9 m_d3d;								// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_d3dDevice;			// Direct3D�f�o�C�X�ւ̃|�C���^
	HWND m_hwnd;										// �n���h��
};

#endif // !_RENDERER_H_
