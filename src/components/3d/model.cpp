﻿//------------------------------------------------------------
// @file		model.cpp
// @brief	モデル
// @detail	3Dのモデル
//------------------------------------------------------------
#include "model.h"
#include "system/manager.h"

//=============================================================
// 初期化
//=============================================================
void Model::Init()
{

}

//=============================================================
// 終了
//=============================================================
void Model::Uninit()
{
}

//=============================================================
// 描画
//=============================================================
void Model::Draw()
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();
	D3DMATERIAL9 matDef;					// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;					// マテリアルデータへのポインタ

	if (m_modelData == nullptr)
		return;

	// ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &transform->GetMatrix());

	// 現在のマテリアルを取得
	device->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_modelData->GetBufferMaterial()->GetBufferPointer();

	for (int i = 0; i < static_cast<int>(m_modelData->GetNumMaterial()); i++)
	{
		// マテリアルの設定
		device->SetMaterial(&pMat[i].MatD3D);

		// テクスチャの設定
		device->SetTexture(0, pMat[i].pTextureFilename != nullptr ? m_textures[i] : nullptr);

		// モデル（パーツ）の描画
		m_modelData->GetMesh()->DrawSubset(i);
	}

	// 保存していたマテリアルに戻す
	device->SetMaterial(&matDef);
}

//=============================================================
// 描画
//=============================================================
void Model::Load(std::string path)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// メッシュ情報を破棄
	Uninit();

	// メッシュを読み込む
	m_modelData = Manager::GetInstance()->GetResourceDataManager()->RefModel(path);

	// モデルテクスチャの読み込み
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_modelData->GetBufferMaterial()->GetBufferPointer();
	m_textures.resize(m_modelData->GetNumMaterial());
	for (int nCntMat = 0; nCntMat < (int)m_modelData->GetNumMaterial(); nCntMat++)
	{
		if (mat[nCntMat].pTextureFilename != nullptr)
		{ // テクスチャがあるとき

			// テクスチャの存在チェック
			if (!PathFileExistsA(mat[nCntMat].pTextureFilename))
			{ // 存在しないとき
				mat[nCntMat].pTextureFilename = nullptr;
				m_textures[nCntMat] = nullptr;
				continue;
			}

			// テクスチャを作成
			m_textures[nCntMat] = Manager::GetInstance()->GetResourceDataManager()->RefTexture(mat[nCntMat].pTextureFilename)->GetTexture();
		}
		else
		{
			m_textures[nCntMat] = nullptr;
		}
	}
}
