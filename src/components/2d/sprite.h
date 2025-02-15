//------------------------------------------------------------
// @file		sprite.h
// @brief	スプライト
// @detail	2Dの板ポリゴン
//------------------------------------------------------------
#ifndef _COMP_SPRITE_H_
#define _COMP_SPRITE_H_

#include "component.h"

class Sprite : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void DrawUI() override;

	//@brief テクスチャを設定する
	void SetTexture(std::string path);

	//@brief テクスチャをバインドする
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_texture = texture; }

	//@brief アンカーポイントを設定する
	void SetAnchorPoint(D3DXVECTOR2 anchor) { m_anchorPoint = anchor; }
private:
	//@brief 頂点を更新する
	void UpdateVertex();

	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;	// 頂点情報
	LPDIRECT3DTEXTURE9 m_texture;				// テクスチャ
	Transform m_oldTransform;						// 前回のトランスフォーム
	D3DXVECTOR2 m_anchorPoint;					// アンカーポイント
};

#endif // !_COMP_SPRITE_H_
