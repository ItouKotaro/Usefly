//------------------------------------------------------------
// @file		sprite.cpp
// @brief	スプライト
// @detail	2Dの板ポリゴン
//------------------------------------------------------------
#include "sprite.h"
#include "sysyem/manager.h"

//=============================================================
// 初期化
//=============================================================
void Sprite::Init()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	//頂点バッファの生成
	device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_vtxBuff, nullptr);
	VERTEX_2D* vtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	//頂点座標の設定
	vtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	vtx[0].rhw = 1.0f;
	vtx[1].rhw = 1.0f;
	vtx[2].rhw = 1.0f;
	vtx[3].rhw = 1.0f;

	//頂点カラー
	vtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_vtxBuff->Unlock();
}

//=============================================================
// 終了
//=============================================================
void Sprite::Uninit()
{
	//頂点バッファの破棄
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// 更新
//=============================================================
void Sprite::Update()
{
	if (*transform != m_oldTransform)
	{
		// 頂点を更新する
		UpdateVertex();

		// 前回のトランスフォームを保存する
		m_oldTransform = *transform;
	}
}

//=============================================================
// UI描画
//=============================================================
void Sprite::DrawUI()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// 頂点バッファをデータストリームに設定
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	device->SetTexture(0, m_texture);

	// ポリゴンの描画
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, //プリミティブの種類
		0, //描画する最初の頂点インデックス
		2); //描画するプリミティブ数
}

//=============================================================
// テクスチャを設定する
//=============================================================
void Sprite::SetTexture(std::string path)
{
	// データを参照する
	TextureData* data = Manager::GetInstance()->GetResourceDataManager()->RefTexture(path);

	// テクスチャをバインドする
	if (data != nullptr)
	{
		BindTexture(data->GetTexture());
	}
}

//=============================================================
// 頂点を更新する
//=============================================================
void Sprite::UpdateVertex()
{
	VERTEX_2D* vtx; //頂点情報へのポインタ

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationZ(&mtx, transform->GetWorldRotation().z);

	// 頂点位置を格納する
	D3DXVECTOR3 convPos[4] =
	{
		{0.0f, 0.0f, 0.0f},
		{transform->size.x, 0.0f, 0.0f},
		{0.0f, transform->size.y, 0.0f},
		{transform->size.x, transform->size.y, 0.0f}
	};

	// アンカーポイントを加味する
	for (int i = 0; i < 4; i++)
	{
		convPos[i].x -= m_anchorPoint.x;
		convPos[i].y -= m_anchorPoint.y;
	}


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&vtx, 0);

	// サイズと回転
	D3DXVec3TransformCoord(&vtx[0].pos, &convPos[0], &mtx);
	D3DXVec3TransformCoord(&vtx[1].pos, &convPos[1], &mtx);
	D3DXVec3TransformCoord(&vtx[2].pos, &convPos[2], &mtx);
	D3DXVec3TransformCoord(&vtx[3].pos, &convPos[3], &mtx);

	// 位置
	for (int i = 0; i < 4; i++)
	{
		vtx[i].pos.x += transform->GetWorldPosition().x;
		vtx[i].pos.y += transform->GetWorldPosition().y;
	}

	//頂点バッファをアンロックする
	m_vtxBuff->Unlock();
}
