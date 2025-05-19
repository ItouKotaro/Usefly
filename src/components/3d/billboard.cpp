//------------------------------------------------------------
// @file		billboard.cpp
// @brief	�r���{�[�h
//------------------------------------------------------------
#include "billboard.h"

//=============================================================
// ������
//=============================================================
void Billboard::Init()
{
	// �ϐ��̏�����
	m_vtxBuff = nullptr;											// ���_�o�b�t�@
	m_texture = nullptr;											// �e�N�X�`��
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[
	m_monitor = new TransformMonitor(transform);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// ���_�o�b�t�@�̐���
	device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vtxBuff, NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	VERTEX_3D* vtx;
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// ���_���W�̐ݒ�
	vtx[0].pos = D3DXVECTOR3(-transform->size.x * 0.5f, transform->size.y * 0.5f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(transform->size.x * 0.5f, transform->size.y * 0.5f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(-transform->size.x * 0.5f, -transform->size.y * 0.5f, 0.0f);
	vtx[3].pos = D3DXVECTOR3(transform->size.x * 0.5f, -transform->size.y * 0.5f, 0.0f);

	// �@���̐ݒ�
	vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[
	vtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}

//=============================================================
// �I��
//=============================================================
void Billboard::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// �X�V
//=============================================================
void Billboard::Update()
{
	if (m_monitor->HasSizeChanged())
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		VERTEX_3D* vtx;
		m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

		// ���_���W�̐ݒ�
		vtx[0].pos = D3DXVECTOR3(-transform->size.x * 0.5f, transform->size.y * 0.5f, 0.0f);
		vtx[1].pos = D3DXVECTOR3(transform->size.x * 0.5f, transform->size.y * 0.5f, 0.0f);
		vtx[2].pos = D3DXVECTOR3(-transform->size.x * 0.5f, -transform->size.y * 0.5f, 0.0f);
		vtx[3].pos = D3DXVECTOR3(transform->size.x * 0.5f, -transform->size.y * 0.5f, 0.0f);

		// �@���̐ݒ�
		vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[
		vtx[0].col = m_color;
		vtx[1].col = m_color;
		vtx[2].col = m_color;
		vtx[3].col = m_color;

		// �e�N�X�`�����W�̐ݒ�
		vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_vtxBuff->Unlock();
	}
}

//=============================================================
// �`��
//=============================================================
void Billboard::Draw()
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();		// �f�o�C�X���擾
	D3DXMATRIX mtx;
	D3DXMATRIX mtxView;

	// ���C�g�𖳌��ɂ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 0);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �r���[�}�g���b�N�X���擾
	device->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtx, NULL, &mtxView);	// �t�s������߂�
	mtx._41 = 0.0f;
	mtx._42 = 0.0f;
	mtx._43 = 0.0f;

	D3DXMATRIX rotMtx;
	D3DXMatrixRotationZ(&rotMtx, transform->GetWorldEulerAngle().z);
	mtx *= rotMtx;

	// �I�u�W�F�N�g�̃}�g���b�N�X���|����
	D3DXMATRIX mtxTrans = transform->GetTranslationMatrix();
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &mtx);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, m_texture);

	// �|���S���̕`��
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);				//�`�悷��v���~�e�B�u��

	// ���C�g��L���ɖ߂�
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================
// �e�N�X�`���̐ݒ�
//=============================================================
void Billboard::SetTexture(const std::string& path)
{
	BindTexture(Manager::GetInstance()->GetResourceDataManager()->RefTexture(path)->GetTexture());
}

//=============================================================
// �F
//=============================================================
void Billboard::SetColor(const D3DXCOLOR& color)
{
	m_color = color;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	VERTEX_3D* vtx;
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// ���_�J���[
	vtx[0].col = m_color;
	vtx[1].col = m_color;
	vtx[2].col = m_color;
	vtx[3].col = m_color;

	// ���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}