//------------------------------------------------------------
// @file		sprite.cpp
// @brief	�X�v���C�g
// @detail	2D�̔|���S��
//------------------------------------------------------------
#include "sprite.h"
#include "sysyem/manager.h"

//=============================================================
// ������
//=============================================================
void Sprite::Init()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	//���_�o�b�t�@�̐���
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_vtxBuff, nullptr);
	VERTEX_2D* vtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	//���_���W�̐ݒ�
	vtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	//���_�J���[
	vtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}

//=============================================================
// �I��
//=============================================================
void Sprite::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// �X�V
//=============================================================
void Sprite::Update()
{
	if (*transform != m_oldTransform)
	{
		// ���_���X�V����
		UpdateVertex();

		// �O��̃g�����X�t�H�[����ۑ�����
		m_oldTransform = *transform;
	}
}

//=============================================================
// UI�`��
//=============================================================
void Sprite::DrawUI()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, m_texture);

	// �|���S���̕`��
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//=============================================================
// �e�N�X�`����ݒ肷��
//=============================================================
void Sprite::SetTexture(std::string path)
{
	// �f�[�^���Q�Ƃ���
	TextureData* data = Manager::GetInstance()->GetResourceDataManager()->RefTexture(path);

	// �e�N�X�`�����o�C���h����
	if (data != nullptr)
	{
		BindTexture(data->GetTexture());
	}
}

//=============================================================
// ���_���X�V����
//=============================================================
void Sprite::UpdateVertex()
{
	VERTEX_2D* vtx; //���_���ւ̃|�C���^

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationZ(&mtx, transform->GetWorldRotation().z);

	// ���_�ʒu���i�[����
	D3DXVECTOR3 convPos[4] =
	{
		{0.0f, 0.0f, 0.0f},
		{transform->size.x, 0.0f, 0.0f},
		{0.0f, transform->size.y, 0.0f},
		{transform->size.x, transform->size.y, 0.0f}
	};

	// �A���J�[�|�C���g����������
	for (int i = 0; i < 4; i++)
	{
		convPos[i].x -= m_anchorPoint.x;
		convPos[i].y -= m_anchorPoint.y;
	}


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// �T�C�Y�Ɖ�]
	D3DXVec3TransformCoord(&vtx[0].pos, &convPos[0], &mtx);
	D3DXVec3TransformCoord(&vtx[1].pos, &convPos[1], &mtx);
	D3DXVec3TransformCoord(&vtx[2].pos, &convPos[2], &mtx);
	D3DXVec3TransformCoord(&vtx[3].pos, &convPos[3], &mtx);

	// �ʒu
	for (int i = 0; i < 4; i++)
	{
		vtx[i].pos.x += transform->GetWorldPosition().x;
		vtx[i].pos.y += transform->GetWorldPosition().y;
	}

	//���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}
