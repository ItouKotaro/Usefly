//------------------------------------------------------------
// @file		model.cpp
// @brief	���f��
// @detail	3D�̃��f��
//------------------------------------------------------------
#include "model.h"
#include "sysyem/manager.h"

//=============================================================
// ������
//=============================================================
void Model::Init()
{

}

//=============================================================
// �I��
//=============================================================
void Model::Uninit()
{
}

//=============================================================
// �`��
//=============================================================
void Model::Draw()
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	if (m_modelData == nullptr)
		return;

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &transform->GetMatrix());

	// ���݂̃}�e���A�����擾
	device->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_modelData->GetBufferMaterial()->GetBufferPointer();

	for (int i = 0; i < static_cast<int>(m_modelData->GetNumMaterial()); i++)
	{
		// �}�e���A���̐ݒ�
		device->SetMaterial(&pMat[i].MatD3D);

		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, pMat[i].pTextureFilename != nullptr ? m_textures[i] : nullptr);

		// ���f���i�p�[�c�j�̕`��
		m_modelData->GetMesh()->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A���ɖ߂�
	device->SetMaterial(&matDef);
}

//=============================================================
// �`��
//=============================================================
void Model::Load(std::string path)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// ���b�V������j��
	Uninit();

	// ���b�V����ǂݍ���
	m_modelData = Manager::GetInstance()->GetResourceDataManager()->RefModel(path);

	// ���f���e�N�X�`���̓ǂݍ���
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_modelData->GetBufferMaterial()->GetBufferPointer();
	m_textures.resize(m_modelData->GetNumMaterial());
	for (int nCntMat = 0; nCntMat < (int)m_modelData->GetNumMaterial(); nCntMat++)
	{
		if (mat[nCntMat].pTextureFilename != nullptr)
		{ // �e�N�X�`��������Ƃ�

			// �e�N�X�`���̑��݃`�F�b�N
			if (!PathFileExistsA(mat[nCntMat].pTextureFilename))
			{ // ���݂��Ȃ��Ƃ�
				mat[nCntMat].pTextureFilename = nullptr;
				m_textures[nCntMat] = nullptr;
				continue;
			}

			// �e�N�X�`�����쐬
			m_textures[nCntMat] = Manager::GetInstance()->GetResourceDataManager()->RefTexture(mat[nCntMat].pTextureFilename)->GetTexture();
		}
		else
		{
			m_textures[nCntMat] = nullptr;
		}
	}
}
