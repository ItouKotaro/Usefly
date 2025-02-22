//------------------------------------------------------------
// @file		renderer.cpp
// @brief	�����_���[
// @detail	�`����s���V�X�e���ł�
//------------------------------------------------------------
#include "renderer.h"
#include "gameobject.h"
#include "components/3d/camera.h"

//=============================================================
// ������
//=============================================================
HRESULT Renderer::Init(HINSTANCE hInstance, HWND hWnd)
{
	D3DDISPLAYMODE d3ddm;					// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));														// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;												// ��ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;											// ��ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;												// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;																	// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									// �_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;													// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;									// �f�v�X�o�b�t�@
	d3dpp.Windowed = RENDERER_WINDOWED;											// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// �v���[���e�[�V�����C���^�[�o��

		// Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
	{
		// Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�Œ��_������CPU�ōs���j
		if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
		{
			// Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �n���h���̑��
	m_hwnd = hWnd;

	// �����_�[�X�e�[�g�̐ݒ�
	m_d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// ������Ԃ�
	return S_OK;
}

//=============================================================
// �I��
//=============================================================
void Renderer::Uninit()
{
	// Direct3D�f�o�C�X�̔j��
	if (m_d3dDevice != nullptr)
	{
		m_d3dDevice->Release();
		m_d3dDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_d3d != nullptr)
	{
		m_d3d->Release();
		m_d3d = nullptr;
	}
}

//=============================================================
// �X�V
//=============================================================
void Renderer::Update()
{

}

//=============================================================
// �`��
//=============================================================
void Renderer::Draw()
{
	// �J�������擾����
	auto& cameras = Camera::GetAllCameras();

	if (SUCCEEDED(m_d3dDevice->BeginScene()))
	{ // �`��J�n�����������ꍇ
		for (auto itr = cameras.begin(); itr != cameras.end(); itr++)
		{
			// ��A�N�e�B�u�̂Ƃ�
			if (!((*itr)->gameObject->GetActive() && (*itr)->GetActive()))
			{
				continue;
			}

			// ��ʃN���A�i�o�b�t�@�N���A��Z�o�b�t�@�N���A�j
			m_d3dDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

			// �J�������Z�b�g����
			(*itr)->SetCamera();

			// �Q�[���I�u�W�F�N�g��`�悷��
			GameObject::AllDraw();

			// �Q�[���I�u�W�F�N�g��UI�`�悷��
			GameObject::AllDrawUI();
		}

		// �`��I��
		m_d3dDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
