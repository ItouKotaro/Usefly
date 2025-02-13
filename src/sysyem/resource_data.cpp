//------------------------------------------------------------
// @file		resource_data.cpp
// @brief	リソースデータ
// @detail	データの管理を行います
//------------------------------------------------------------
#include "resource_data.h"
#include "manager.h"

//=============================================================
// 読み込み
//=============================================================
bool TextureData::Load(std::string path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::getInstance()->getDevice();

	// テクスチャの作成
	if (FAILED(D3DXCreateTextureFromFile(device, path.c_str(), &m_texture)))
	{
		return false;
	}
	return true;
}

//=============================================================
// 解放
//=============================================================
void TextureData::Release()
{
	// テクスチャの破棄
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

//=============================================================
// テクスチャデータを参照する
//=============================================================
TextureData* ResourceDataManager::refTexture(std::string path)
{
	// データが存在するときは返す
	auto datas = m_resourceDatas[ResourceData::FORMAT::TEXTURE];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->getPath())
		{
			return static_cast<TextureData*>(*itr);
		}
	}

	// データが存在しないときはデータを生成する
	TextureData* data = new TextureData();
	data->setPath(path);

	// データをロードする
	if (!data->Load(path))
	{
		Log::sendLog("テクスチャデータ \"" + path + "\" のロードに失敗しました！", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}
	
	// データを登録する
	m_resourceDatas->push_back(data);

	// ログを送信する
	Log::sendLog("テクスチャデータ \"" + path + "\" のロードに成功しました！");

	// データを返す
	return data;
}

//=============================================================
// すべてのリソースを解放する
//=============================================================
void ResourceDataManager::AllRelease()
{
	for (int i = 0; i < ResourceData::FORMAT::MAX; i++)
	{
		for (auto itr = m_resourceDatas[i].begin(); itr != m_resourceDatas[i].end(); itr++)
		{
			// データを解放する
			(*itr)->Release();

			// リソース自体を破棄する
			delete* itr;
			*itr = nullptr;
		}

		// リソースを空にする
		m_resourceDatas[i].clear();
	}
}
