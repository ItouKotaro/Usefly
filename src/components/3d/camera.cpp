//------------------------------------------------------------
// @file		camera.cpp
// @brief	�J����
// @detail	3D��Ԃɑ��݂���I�u�W�F�N�g��`�悷�邽�߂̃f�o�C�X
//------------------------------------------------------------
#include "camera.h"
#include "sysyem/manager.h"

std::vector<Camera*> Camera::m_cameras;

//=============================================================
// ������
//=============================================================
void Camera::Init()
{
	// �����ݒ�
	m_vecU = { 0.0f, 1.0f, 0.0f };
	m_posR = { 0.0f, 0.0f, 0.0f };
	m_length = CAMERA_LENGTH;
	m_mode = MODE::MODE_PERSPECTIVE;

	// �`�拗���̐ݒ�
	m_clippingPlanes.min = CLIPPING_NEAR;
	m_clippingPlanes.max = CLIPPING_FAR;
	m_clippingPlanes.Sort();

	// �r���[�|�[�g�̐ݒ�
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewportPosition(0.0f, 0.0f);
	SetViewportSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	// �J�������X�g�ɒǉ�����
	m_cameras.push_back(this);
}

//=============================================================
// �I��
//=============================================================
void Camera::Uninit()
{
	// �J�������X�g����폜����
	for (auto itr = m_cameras.begin(); itr != m_cameras.end(); itr++)
	{
		if (*itr == this)
		{
			m_cameras.erase(itr);
			break;
		}
	}
}

//=============================================================
// �X�V
//=============================================================
void Camera::Update()
{
	// �O������w��̒������L�΂�
	D3DXMATRIX rotMtx = transform->GetRotationMatrix();
	m_posR = { 0.0f, 0.0f, m_length };
	D3DXVec3TransformCoord(&m_posR, &m_posR, &rotMtx);

	// �ʒu�����Z����
	m_posR += transform->GetWorldPosition();
}

//=============================================================
// �r���[�|�[�g�̈ʒu��ݒ肷��
//=============================================================
void Camera::SetViewportPosition(float x, float y)
{
	m_viewport.X = static_cast<DWORD>(x);
	m_viewport.Y = static_cast<DWORD>(y);
}

//=============================================================
// �r���[�|�[�g�̃T�C�Y��ݒ肷��
//=============================================================
void Camera::SetViewportSize(float width, float height)
{
	m_viewport.Width = static_cast<DWORD>(width);
	m_viewport.Height = static_cast<DWORD>(height);
}

//=============================================================
// �J�����̐ݒu
//=============================================================
void Camera::SetCamera()
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_projMtx);

	// �E�B���h�E�T�C�Y�̎擾
	D3DXVECTOR2 windowSize = Main::GetWindowSize();

	// ���e���[�h���Ƃɐݒ肷��
	switch (m_mode)
	{
	case Camera::MODE_PERSPECTIVE:
		D3DXMatrixPerspectiveFovLH(
			&m_projMtx,
			D3DXToRadian(45.0f),
			windowSize.x / windowSize.y,
			m_clippingPlanes.min,
			m_clippingPlanes.max);
		break;

	case Camera::MODE_PARALLEL:
		D3DXMatrixOrthoLH(
			&m_projMtx,
			windowSize.x,
			windowSize.y,
			m_clippingPlanes.min,
			m_clippingPlanes.max);

		// �X�P�[�����O����
		D3DXMATRIX mtxScale;
		D3DXMatrixIdentity(&mtxScale);
		D3DXMatrixScaling(&mtxScale, 10.0f, 10.0f, 1.0f);
		D3DXMatrixMultiply(&m_projMtx, &m_projMtx, &mtxScale);
		break;
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_PROJECTION, &m_projMtx);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_viewMtx);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	D3DXMatrixLookAtLH(&m_viewMtx, &pos, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_VIEW, &m_viewMtx);

	// �r���[�|�[�g�̐ݒ�
	device->SetViewport(&m_viewport);
}
