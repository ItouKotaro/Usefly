//------------------------------------------------------------
// @file			render_texture.h
// @brief		テクスチャにレンダリングする
//------------------------------------------------------------
#ifndef _RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_

#include "component.h"
#include "components/3d/camera.h"

/** 
 * @brief レンダーテクスチャ
 * @details カメラコンポーネントが必須です
*/
class RenderTexture : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;

	//@brief 作成する
	bool Create(const int& width, const int& height);

	//@brief テクスチャを取得する
	LPDIRECT3DTEXTURE9 GetTexture() { return m_renderTexture; }

	//@brief 描画開始
	bool Begin();
	//@brief 描画終了
	void End();
private:
	D3DXVECTOR2 m_size;

	LPDIRECT3DTEXTURE9 m_renderTexture;		// レンダリング先のテクスチャ
	LPDIRECT3DSURFACE9 m_textureSurface;		// サーフェイス
	LPDIRECT3DSURFACE9 m_depthSurface;			// 深度バッファ
};

#endif // !_RENDER_TEXTURE_H_
