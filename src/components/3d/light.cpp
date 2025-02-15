//------------------------------------------------------------
// @file		light.cpp
// @brief	���C�g
// @detail	3D�I�u�W�F�N�g��\�����邽�߂ɕK�v�ȃ��C�g
//------------------------------------------------------------
#include "light.h"
#include "sysyem/manager.h"

std::vector<D3DLight*> D3DLight::m_lights;

//=============================================================
// ������
//=============================================================
void D3DLight::Init()
{
	// ���C�g���X�g�ɒǉ�����
	m_lights.push_back(this);
}

//=============================================================
// �I��
//=============================================================
void D3DLight::Uninit()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// �Ō���̃��C�g�𖳌��ɂ���
	device->LightEnable(static_cast<DWORD>(m_lights.size() - 1), FALSE);

	// ���C�g���X�g����폜����
	for (auto itr = m_lights.begin(); itr != m_lights.end(); itr++)
	{
		if (*itr == this)
		{
			m_lights.erase(itr);
			break;
		}
	}
}

//=============================================================
// �X�V
//=============================================================
void D3DLight::Update()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	for (int i = 0; i < (int)m_lights.size(); i++)
	{
		// ���C�g��ݒ肷��
		device->SetLight(i, &m_lights[i]->m_light);

		// ���C�g��L���ɂ���
		device->LightEnable(i, TRUE);
	}
}

//=============================================================
// �f�t�H���g�̃��C�g�ݒ�
//=============================================================
void D3DLight::SetDefaultLight(GameObject* gameObject)
{
	D3DLight* lightComp = gameObject->AddComponent<D3DLight>();
	lightComp->SetType(D3DLIGHT_DIRECTIONAL);
	lightComp->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	lightComp->SetDirection(D3DXVECTOR3(0.22f, -0.87f, 0.44f));

	lightComp = gameObject->AddComponent<D3DLight>();
	lightComp->SetType(D3DLIGHT_DIRECTIONAL);
	lightComp->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	lightComp->SetDirection(D3DXVECTOR3(-0.18f, 0.88f, -0.44f));

	lightComp = gameObject->AddComponent<D3DLight>();
	lightComp->SetType(D3DLIGHT_DIRECTIONAL);
	lightComp->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	lightComp->SetDirection(D3DXVECTOR3(0.89f, 0.11f, 0.44f));
}
