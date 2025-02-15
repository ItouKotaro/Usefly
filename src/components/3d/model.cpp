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
	LPDIRECT3DDEVICE9 device = Manager::getInstance()->getDevice();
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	if (m_modelData == nullptr)
		return;

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &transform->getMatrix());

	// ���݂̃}�e���A�����擾
	device->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_modelData->getBufferMaterial()->GetBufferPointer();

	for (int i = 0; i < static_cast<int>(m_modelData->getNumMaterial()); i++)
	{
		// �}�e���A���̐ݒ�
		device->SetMaterial(&pMat[i].MatD3D);

		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, pMat[i].pTextureFilename != nullptr ? m_textures[i] : nullptr);

		// ���f���i�p�[�c�j�̕`��
		m_modelData->getMesh()->DrawSubset(i);
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
	LPDIRECT3DDEVICE9 device = Manager::getInstance()->getDevice();

	// ���b�V������j��
	Uninit();

	// ���b�V����ǂݍ���
	m_modelData = Manager::getInstance()->getResourceDataManager()->refModel(path);

	// ���f���e�N�X�`���̓ǂݍ���
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_modelData->getBufferMaterial()->GetBufferPointer();
	m_textures.resize(m_modelData->getNumMaterial());
	for (int nCntMat = 0; nCntMat < (int)m_modelData->getNumMaterial(); nCntMat++)
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
			m_textures[nCntMat] = Manager::getInstance()->getResourceDataManager()->refTexture(mat[nCntMat].pTextureFilename)->getTexture();
		}
		else
		{
			m_textures[nCntMat] = nullptr;
		}
	}
}
