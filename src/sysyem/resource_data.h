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

//@brief モデルデータ
class ModelData : public ResourceData
{
public:
	ModelData() : ResourceData(FORMAT::MODEL), m_mesh(nullptr), m_buffMat(nullptr), m_numMat(0) {}

	//@brief ロードする
	bool Load(std::string path) override;

	//@brief 解放する
	void Release() override;

	//@brief メッシュを取得する
	LPD3DXMESH getMesh() { return m_mesh; }
	//@brief マテリアルデータを取得する
	LPD3DXBUFFER getBufferMaterial() { return m_buffMat; }
	//@brief マテリアル数を取得する
	DWORD getNumMaterial() { return m_numMat; }
private:
	LPD3DXMESH m_mesh;				// メッシュデータ
	LPD3DXBUFFER m_buffMat;		// マテリアルデータ
	DWORD m_numMat;					// マテリアル数
};




//@brief リソースデータ管理クラス
class ResourceDataManager final
{
public:
	ResourceDataManager() {}
	~ResourceDataManager() {}

	//@brief テクスチャデータを参照する
	TextureData* refTexture(std::string path);
	//@brief モデルデータを参照する
	ModelData* refModel(std::string path);

	//@brief すべてのリソースを解放する
	void AllRelease();
private:
	std::vector<ResourceData*> m_resourceDatas[ResourceData::FORMAT::MAX];
};

#endif // !_RESOURCE_DATA_H_
