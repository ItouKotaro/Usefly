//------------------------------------------------------------
// @file		resource_data.h
// @brief	リソースデータ
// @detail	データの管理を行います
//------------------------------------------------------------
#ifndef _RESOURCE_DATA_H_
#define _RESOURCE_DATA_H_

//@brief リソースデータ（基底）
class ResourceData
{
public:
	//@brief フォーマットの種類
	enum FORMAT
	{
		TEXTURE,		// テクスチャ
		MODEL,			// モデル
		AUDIO,			// オーディオ
		MAX
	};

	ResourceData(const FORMAT& format) { m_format = format; }
	virtual ~ResourceData() {}

	//@brief ロードする
	virtual bool Load(std::string path) = 0;

	//@brief 解放する
	virtual void Release() = 0;

	//@brief フォーマットを取得する
	FORMAT getFormat() { return m_format; }

	//@brief パスを設定する
	void setPath(std::string path) { m_path = path; }

	//@brief パスを取得する
	std::string getPath() { return m_path; }
private:
	std::string m_path;		// パス
	FORMAT m_format;		// フォーマット
};

//@brief テクスチャデータ
class TextureData : public ResourceData
{
public:
	TextureData() : ResourceData(FORMAT::TEXTURE), m_texture(nullptr){}

	//@brief ロードする
	bool Load(std::string path) override;

	//@brief 解放する
	void Release() override;

	//@brief テクスチャを取得する
	LPDIRECT3DTEXTURE9 getTexture() { return m_texture; }
private:
	LPDIRECT3DTEXTURE9 m_texture;		// テクスチャ
};

//@brief リソースデータ管理クラス
class ResourceDataManager final
{
public:
	ResourceDataManager() {}
	~ResourceDataManager() {}

	//@brief テクスチャデータを参照する
	TextureData* refTexture(std::string path);

	//@brief すべてのリソースを解放する
	void AllRelease();
private:
	std::vector<ResourceData*> m_resourceDatas[ResourceData::FORMAT::MAX];
};

#endif // !_RESOURCE_DATA_H_
