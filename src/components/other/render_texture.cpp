//------------------------------------------------------------
// @file			render_texture.cpp
// @brief		テクスチャにレンダリングする
//------------------------------------------------------------
#include "render_texture.h"

//=============================================================
// 初期化
//=============================================================
void RenderTexture::Init()
{
	m_renderTexture = nullptr;
	m_textureSurface = nullptr;
	m_depthSurface = nullptr;
}

//=============================================================
// 終了
//=============================================================
void RenderTexture::Uninit()
{
	// テクスチャの破棄
	if (m_renderTexture != nullptr)
	{
		m_renderTexture->Release();
		m_renderTexture = nullptr;
	}

	// テクスチャサーフェイスの破棄
	if (m_textureSurface != nullptr)
	{
		m_textureSurface->Release();
		m_textureSurface = nullptr;
	}

	// 震度バッファの破棄
	if (m_depthSurface != nullptr)
	{
		m_depthSurface->Release();
		m_depthSurface = nullptr;
	}
}

//=============================================================
// 描画
//=============================================================
void RenderTexture::Draw()
{
}

//=============================================================
// 作成する
//=============================================================
bool RenderTexture::Create(const int& width, const int& height)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// 破棄
	this->Uninit();

	// テクスチャの作成
	if (FAILED(D3DXCreateTexture(
		device,
		width,
		height,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_renderTexture)))
	{
		return false;
	}

	// 深度バッファの作成
	if (FAILED(device->CreateDepthStencilSurface(
		width,
		height,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_depthSurface,
		NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================
// 描画開始
//=============================================================
bool RenderTexture::Begin()
{
	// 設定チェック
	if (m_renderTexture == nullptr ||
		m_depthSurface == nullptr)
	{
		return false;
	}

	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// 作成したステンシルバッファを設定する
	device->SetDepthStencilSurface(m_depthSurface);

	// 作成したテクスチャにレンダリングターゲットを変更
	LPDIRECT3DSURFACE9 surface;
	if (FAILED(m_renderTexture->GetSurfaceLevel(0, &surface)))
	{
		return false;
	}
	device->SetRenderTarget(0, surface);

	// 記憶しておく
	m_textureSurface = surface;

	// シーンの開始
	return SUCCEEDED(device->BeginScene());
}

//=============================================================
// 描画終了
//=============================================================
void RenderTexture::End()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// シーンの終了
	device->EndScene();
}
