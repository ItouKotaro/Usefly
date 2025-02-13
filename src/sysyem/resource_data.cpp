//------------------------------------------------------------
// @file		resource_data.cpp
// @brief	���\�[�X�f�[�^
// @detail	�f�[�^�̊Ǘ����s���܂�
//------------------------------------------------------------
#include "resource_data.h"
#include "manager.h"

//=============================================================
// �ǂݍ���
//=============================================================
bool TextureData::Load(std::string path)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::getInstance()->getDevice();

	// �e�N�X�`���̍쐬
	if (FAILED(D3DXCreateTextureFromFile(device, path.c_str(), &m_texture)))
	{
		return false;
	}
	return true;
}

//=============================================================
// ���
//=============================================================
void TextureData::Release()
{
	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

//=============================================================
// �e�N�X�`���f�[�^���Q�Ƃ���
//=============================================================
TextureData* ResourceDataManager::refTexture(std::string path)
{
	// �f�[�^�����݂���Ƃ��͕Ԃ�
	auto datas = m_resourceDatas[ResourceData::FORMAT::TEXTURE];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->getPath())
		{
			return static_cast<TextureData*>(*itr);
		}
	}

	// �f�[�^�����݂��Ȃ��Ƃ��̓f�[�^�𐶐�����
	TextureData* data = new TextureData();
	data->setPath(path);

	// �f�[�^�����[�h����
	if (!data->Load(path))
	{
		Log::sendLog("�e�N�X�`���f�[�^ \"" + path + "\" �̃��[�h�Ɏ��s���܂����I", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}
	
	// �f�[�^��o�^����
	m_resourceDatas->push_back(data);

	// ���O�𑗐M����
	Log::sendLog("�e�N�X�`���f�[�^ \"" + path + "\" �̃��[�h�ɐ������܂����I");

	// �f�[�^��Ԃ�
	return data;
}

//=============================================================
// ���ׂẴ��\�[�X���������
//=============================================================
void ResourceDataManager::AllRelease()
{
	for (int i = 0; i < ResourceData::FORMAT::MAX; i++)
	{
		for (auto itr = m_resourceDatas[i].begin(); itr != m_resourceDatas[i].end(); itr++)
		{
			// �f�[�^���������
			(*itr)->Release();

			// ���\�[�X���̂�j������
			delete* itr;
			*itr = nullptr;
		}

		// ���\�[�X����ɂ���
		m_resourceDatas[i].clear();
	}
}
