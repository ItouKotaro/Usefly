//------------------------------------------------------------
// @file		resource_data.cpp
// @brief	���\�[�X�f�[�^
// @detail	�f�[�^�̊Ǘ����s���܂�
//------------------------------------------------------------
#include "resource_data.h"
#include "manager.h"

//=============================================================
// �e�N�X�`���f�[�^���Q�Ƃ���
//=============================================================
TextureData* ResourceDataManager::RefTexture(std::string path)
{
	// �f�[�^�����݂���Ƃ��͕Ԃ�
	auto datas = m_resourceDatas[ResourceData::FORMAT::TEXTURE];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->GetPath())
		{
			return static_cast<TextureData*>(*itr);
		}
	}

	// �f�[�^�����݂��Ȃ��Ƃ��̓f�[�^�𐶐�����
	TextureData* data = new TextureData();
	data->SetPath(path);

	// �f�[�^�����[�h����
	if (!data->Load(path))
	{
		Log::SendLog("�e�N�X�`���f�[�^ \"" + path + "\" �̃��[�h�Ɏ��s���܂����I", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}
	
	// �f�[�^��o�^����
	m_resourceDatas->push_back(data);

	// ���O�𑗐M����
	Log::SendLog("�e�N�X�`���f�[�^ \"" + path + "\" �̃��[�h�ɐ������܂����I");

	// �f�[�^��Ԃ�
	return data;
}

//=============================================================
// ���f���f�[�^���Q�Ƃ���
//=============================================================
ModelData* ResourceDataManager::RefModel(std::string path)
{
	// �f�[�^�����݂���Ƃ��͕Ԃ�
	auto datas = m_resourceDatas[ResourceData::FORMAT::MODEL];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->GetPath())
		{
			return static_cast<ModelData*>(*itr);
		}
	}

	// �f�[�^�����݂��Ȃ��Ƃ��̓f�[�^�𐶐�����
	ModelData* data = new ModelData();
	data->SetPath(path);

	// �f�[�^�����[�h����
	if (!data->Load(path))
	{
		Log::SendLog("���f���f�[�^ \"" + path + "\" �̃��[�h�Ɏ��s���܂����I", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}

	// �f�[�^��o�^����
	m_resourceDatas->push_back(data);

	// ���O�𑗐M����
	Log::SendLog("���f���f�[�^ \"" + path + "\" �̃��[�h�ɐ������܂����I");

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

//=============================================================
// �ǂݍ���
//=============================================================
bool TextureData::Load(std::string path)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

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
// �ǂݍ���
//=============================================================
bool ModelData::Load(std::string path)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// ���b�V���̐���
	if (FAILED(D3DXLoadMeshFromX(
		path.c_str(),
		D3DXMESH_SYSTEMMEM,
		device,
		nullptr,
		&m_buffMat,
		nullptr,
		&m_numMat,
		&m_mesh
	)))
	{ // ���s
		return false;
	}

	// ����
	return true;
}

//=============================================================
// ���
//=============================================================
void ModelData::Release()
{
	// ���b�V���̔j��
	if (m_mesh != nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}

	// �}�e���A���̔j��
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}
}
