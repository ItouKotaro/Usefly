//------------------------------------------------------------
// @file		gizmo.cpp
// @brief	�M�Y��
// @detail �M�Y���@�\��񋟂��܂�
//------------------------------------------------------------
#include "gizmo.h"


//=============================================================
// 3D�����_�����O
//=============================================================
void GizmoSystem::Render3D()
{
	// ���C��3D
	for (auto itr = m_line3d.begin(); itr != m_line3d.end();)
	{
		// �`��
		if ((*itr).GetUse())
		{
			(*itr).Get().Draw();
		}

		// �X�V
		if ((*itr).Update())
		{
			(*itr).Get().Uninit();
			itr = m_line3d.erase(itr);
			continue;
		}

		// ����
		(*itr).GetUse() = false;
		itr++;
	}
}

//=============================================================
// 2D�����_�����O
//=============================================================
void GizmoSystem::Render2D()
{
	// ���C��2D
	for (auto itr = m_line2d.begin(); itr != m_line2d.end();)
	{
		// �`��
		if ((*itr).GetUse())
		{
			(*itr).Get().Draw();
		}

		// �X�V
		if ((*itr).Update())
		{
			(*itr).Get().Uninit();
			itr = m_line2d.erase(itr);
			continue;
		}

		// ����
		(*itr).GetUse() = false;
		itr++;
	}
}

//=============================================================
// ���C���̕`��
//=============================================================
void GizmoSystem::DrawLine(const D3DXVECTOR3& from, const D3DXVECTOR3& to, const D3DXCOLOR& color)
{
	// �]���Ă���Ƃ�
	for (auto itr = m_line3d.begin(); itr != m_line3d.end(); itr++)
	{
		if (!(*itr).GetUse())
		{
			(*itr).Get().Set(from, to, color);
			(*itr).GetUse() = true;
			return;
		}
	}

	// �V�K�쐬
	GizmoObject<Line3D> data;
	data.Get().Init();
	data.Get().Set(from, to, color);
	m_line3d.emplace_back(data);
}

//=============================================================
// 2D���C���̕`��
//=============================================================
void GizmoSystem::DrawLine2D(const D3DXVECTOR2& from, const D3DXVECTOR2& to, const float& bold, const D3DXCOLOR& color)
{
	// �]���Ă���Ƃ�
	for (auto itr = m_line2d.begin(); itr != m_line2d.end(); itr++)
	{
		if (!(*itr).GetUse())
		{
			(*itr).Get().Set(from, to, bold, color);
			(*itr).GetUse() = true;
			return;
		}
	}

	// �V�K�쐬
	GizmoObject<Line2D> data;
	data.Get().Init();
	data.Get().Set(from, to, bold, color);
	m_line2d.emplace_back(data);
}

//=============================================================
// �����`��2D���C���̕`��
//=============================================================
void GizmoSystem::DrawRectangle(const D3DXVECTOR2& start, const D3DXVECTOR2& size, const float& bold, const D3DXCOLOR& color, const float& angle)
{
	D3DXVECTOR2 point[4] =
	{
		{size.x * -0.5f, size.y * -0.5f },
		{size.x * 0.5f, size.y * -0.5f},
		{size.x * 0.5f, size.y * 0.5f},
		{size.x * -0.5f, size.y * 0.5f}
	};

	// ��]
	D3DXMATRIX mtx;
	D3DXMatrixRotationZ(&mtx, angle);
	for (int i = 0; i < 4; i++)
		D3DXVec2TransformCoord(&point[i], &point[i], &mtx);

	// �ړ�
	for (int i = 0; i < 4; i++)
		point[i] += start + size * 0.5f;

	// ����`�悷��
	DrawLine2D(point[0], point[1], bold, color);
	DrawLine2D(point[1], point[2], bold, color);
	DrawLine2D(point[2], point[3], bold, color);
	DrawLine2D(point[3], point[0], bold, color);
}


//=============================================================
// 3D���C�� : ������
//=============================================================
void GizmoSystem::Line3D::Init()
{
	// �o�b�t�@���m�ۂ���
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();
	device->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vtxBuff, nullptr);
}

//=============================================================
// 3D���C�� : �I��
//=============================================================
void GizmoSystem::Line3D::Uninit()
{
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// 3D���C�� : �`��
//=============================================================
void GizmoSystem::Line3D::Draw()
{
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	device->SetTransform(D3DTS_WORLD, &mtx);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, nullptr);

	// �|���S���̕`��
	device->DrawPrimitive(D3DPT_LINELIST, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		1);				//�`�悷��v���~�e�B�u��
}

//=============================================================
// 3D���C�� : �Z�b�g
//=============================================================
void GizmoSystem::Line3D::Set(const D3DXVECTOR3& from, const D3DXVECTOR3& to, const D3DXCOLOR& color)
{
	VERTEX_3D* vtx;
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// ���_���W�̐ݒ�
	vtx[0].pos = from;
	vtx[1].pos = to;

	// �@���x�N�g���̐ݒ�
	vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[
	vtx[0].col = color;
	vtx[1].col = color;

	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}


//=============================================================
// 2D���C�� : ������
//=============================================================
void GizmoSystem::Line2D::Init()
{
	// �o�b�t�@���m�ۂ���
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_vtxBuff, nullptr);
}

//=============================================================
// 2D���C�� : �I��
//=============================================================
void GizmoSystem::Line2D::Uninit()
{
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// 2D���C�� : �`��
//=============================================================
void GizmoSystem::Line2D::Draw()
{
	auto device = Manager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, nullptr);

	// �|���S���̕`��
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//=============================================================
// 2D���C�� : �Z�b�g
//=============================================================
void GizmoSystem::Line2D::Set(const D3DXVECTOR2& from, const D3DXVECTOR2& to, const float& bold, const D3DXCOLOR& color)
{
	// �������v�Z����
	float length = sqrtf(fabsf(from.x - to.x) * fabsf(from.x - to.x) + fabsf(from.y - to.y) * fabsf(from.y - to.y));

	// from����to�̊p�x���v�Z����
	float angle = atan2f(to.x - from.x, to.y - from.y) + D3DX_PI;

	// 4�_�̍��W���v�Z����
	D3DXVECTOR2 points[4] =
	{
		{-bold * 0.5f, -length - bold * 0.5f},
		{bold * 0.5f, -length - bold * 0.5f},
		{-bold * 0.5f, bold * 0.5f},
		{bold * 0.5f, bold * 0.5f}
	};
	D3DXMATRIX rotMtx;
	D3DXMatrixIdentity(&rotMtx);
	D3DXMatrixRotationZ(&rotMtx, -angle);
	for (int i = 0; i < 4; i++)
		D3DXVec2TransformCoord(&points[i], &points[i], &rotMtx);

	// �ړ�������
	for (int i = 0; i < 4; i++)
		points[i] += from;

	VERTEX_2D* vtx;
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// ���_���W�̐ݒ�
	vtx[0].pos = { points[0].x, points[0].y, 0.0f };
	vtx[1].pos = { points[1].x, points[1].y, 0.0f };
	vtx[2].pos = { points[2].x, points[2].y, 0.0f };
	vtx[3].pos = { points[3].x, points[3].y, 0.0f };

	// ���_�J���[
	vtx[0].col = color;
	vtx[1].col = color;
	vtx[2].col = color;
	vtx[3].col = color;

	// ���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}
