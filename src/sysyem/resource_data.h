//------------------------------------------------------------
// @file		resource_data.h
// @brief	���\�[�X�f�[�^
// @detail	�f�[�^�̊Ǘ����s���܂�
//------------------------------------------------------------
#ifndef _RESOURCE_DATA_H_
#define _RESOURCE_DATA_H_

//@brief ���\�[�X�f�[�^�i���j
class ResourceData
{
public:
	//@brief �t�H�[�}�b�g�̎��
	enum FORMAT
	{
		TEXTURE,		// �e�N�X�`��
		MODEL,			// ���f��
		AUDIO,			// �I�[�f�B�I
		MAX
	};

	ResourceData(const FORMAT& format) { m_format = format; }
	virtual ~ResourceData() {}

	//@brief ���[�h����
	virtual bool Load(std::string path) = 0;

	//@brief �������
	virtual void Release() = 0;

	//@brief �t�H�[�}�b�g���擾����
	FORMAT getFormat() { return m_format; }

	//@brief �p�X��ݒ肷��
	void setPath(std::string path) { m_path = path; }

	//@brief �p�X���擾����
	std::string getPath() { return m_path; }
private:
	std::string m_path;		// �p�X
	FORMAT m_format;		// �t�H�[�}�b�g
};

//@brief �e�N�X�`���f�[�^
class TextureData : public ResourceData
{
public:
	TextureData() : ResourceData(FORMAT::TEXTURE), m_texture(nullptr){}

	//@brief ���[�h����
	bool Load(std::string path) override;

	//@brief �������
	void Release() override;

	//@brief �e�N�X�`�����擾����
	LPDIRECT3DTEXTURE9 getTexture() { return m_texture; }
private:
	LPDIRECT3DTEXTURE9 m_texture;		// �e�N�X�`��
};

//@brief ���\�[�X�f�[�^�Ǘ��N���X
class ResourceDataManager final
{
public:
	ResourceDataManager() {}
	~ResourceDataManager() {}

	//@brief �e�N�X�`���f�[�^���Q�Ƃ���
	TextureData* refTexture(std::string path);

	//@brief ���ׂẴ��\�[�X���������
	void AllRelease();
private:
	std::vector<ResourceData*> m_resourceDatas[ResourceData::FORMAT::MAX];
};

#endif // !_RESOURCE_DATA_H_
