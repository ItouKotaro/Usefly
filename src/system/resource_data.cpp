//------------------------------------------------------------
// @file		resource_data.cpp
// @brief	リソースデータ
// @detail	データの管理を行います
//------------------------------------------------------------
#include "resource_data.h"
#include "manager.h"

//=============================================================
// テクスチャデータを参照する
//=============================================================
TextureData* ResourceDataManager::RefTexture(std::string path)
{
	// データが存在するときは返す
	auto datas = m_resourceDatas[ResourceData::FORMAT::TEXTURE];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->GetPath())
		{
			return static_cast<TextureData*>(*itr);
		}
	}

	// データが存在しないときはデータを生成する
	TextureData* data = new TextureData();
	data->SetPath(path);

	// データをロードする
	if (!data->Load(path))
	{
		Log::SendLog("テクスチャデータ \"" + path + "\" のロードに失敗しました！", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}
	
	// データを登録する
	m_resourceDatas[ResourceData::FORMAT::TEXTURE].push_back(data);

	// ログを送信する
	Log::SendLog("テクスチャデータ \"" + path + "\" のロードに成功しました！");

	// データを返す
	return data;
}

//=============================================================
// モデルデータを参照する
//=============================================================
ModelData* ResourceDataManager::RefModel(std::string path)
{
	// データが存在するときは返す
	auto datas = m_resourceDatas[ResourceData::FORMAT::MODEL];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->GetPath())
		{
			return static_cast<ModelData*>(*itr);
		}
	}

	// データが存在しないときはデータを生成する
	ModelData* data = new ModelData();
	data->SetPath(path);

	// データをロードする
	if (!data->Load(path))
	{
		Log::SendLog("モデルデータ \"" + path + "\" のロードに失敗しました！", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}

	// データを登録する
	m_resourceDatas[ResourceData::FORMAT::MODEL].push_back(data);

	// ログを送信する
	Log::SendLog("モデルデータ \"" + path + "\" のロードに成功しました！");

	// データを返す
	return data;
}

//=============================================================
// シェーダーデータを参照する
//=============================================================
ShaderData* ResourceDataManager::RefShader(std::string path)
{
	// データが存在するときは返す
	auto datas = m_resourceDatas[ResourceData::FORMAT::SHADER];
	for (auto itr = datas.begin(); itr != datas.end(); itr++)
	{
		if (path == (*itr)->GetPath())
		{
			return static_cast<ShaderData*>(*itr);
		}
	}

	// データが存在しないときはデータを生成する
	ShaderData* data = new ShaderData();
	data->SetPath(path);

	// データをロードする
	if (!data->Load(path))
	{
		Log::SendLog("シェーダーデータ \"" + path + "\" のロードに失敗しました！", Log::TYPE::TYPE_ERROR);
		delete data;
		data = nullptr;
		return data;
	}

	// データを登録する
	m_resourceDatas[ResourceData::FORMAT::SHADER].push_back(data);

	// ログを送信する
	Log::SendLog("シェーダーデータ \"" + path + "\" のロードに成功しました！");

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

//=============================================================
// 読み込み
//=============================================================
bool TextureData::Load(std::string path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

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
// 読み込み
//=============================================================
bool ModelData::Load(std::string path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// メッシュの生成
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
	{ // 失敗
		return false;
	}

	// 範囲を計算する
	CalcVertexRange();

	// 成功
	return true;
}

//=============================================================
// 解放
//=============================================================
void ModelData::Release()
{
	// メッシュの破棄
	if (m_mesh != nullptr)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}

	// マテリアルの破棄
	if (m_buffMat != nullptr)
	{
		m_buffMat->Release();
		m_buffMat = nullptr;
	}
}

//=============================================================
// 範囲を計算する
//=============================================================
void ModelData::CalcVertexRange()
{
	int numVtx;			// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE* vtxBuff;		// 頂点バッファへのポインタ

	// 頂点数の取得
	numVtx = m_mesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_mesh->GetFVF());

	// 頂点バッファのロック
	m_mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vtxBuff);

	for (int nCntVtx = 0; nCntVtx < numVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)vtxBuff;

		// 最大値を取得する
		if (vtx.x > m_maxRange.x)
		{
			m_maxRange.x = vtx.x;
		}
		if (vtx.y > m_maxRange.y)
		{
			m_maxRange.y = vtx.y;
		}
		if (vtx.z > m_maxRange.z)
		{
			m_maxRange.z = vtx.z;
		}

		// 最小値を取得する
		if (vtx.x < m_minRange.x)
		{
			m_minRange.x = vtx.x;
		}
		if (vtx.y < m_minRange.y)
		{
			m_minRange.y = vtx.y;
		}
		if (vtx.z < m_minRange.z)
		{
			m_minRange.z = vtx.z;
		}

		// 頂点フォーマットのサイズ分ポインタを進める
		vtxBuff += sizeFVF;
	}

	// 頂点バッファのアンロック
	m_mesh->UnlockVertexBuffer();
}

//=============================================================
// 読み込み
//=============================================================
bool ShaderData::Load(std::string path)
{
	auto device = Manager::GetInstance()->GetDevice();

	// シェーダーを読み込む
	if (FAILED(D3DXCreateEffectFromFile(
		device,
		path.c_str(),
		NULL,
		NULL,
		0,
		NULL,
		&m_effect,
		NULL
	)))
	{
		return false;
	}

	return true;
}

//=============================================================
// 解放
//=============================================================
void ShaderData::Release()
{
	if (m_effect != nullptr)
	{
		m_effect->Release();
		m_effect = nullptr;
	}
}
