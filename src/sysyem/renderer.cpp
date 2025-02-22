//------------------------------------------------------------
// @file		renderer.cpp
// @brief	レンダラー
// @detail	描画を行うシステムです
//------------------------------------------------------------
#include "renderer.h"
#include "gameobject.h"
#include "components/3d/camera.h"

//=============================================================
// 初期化
//=============================================================
HRESULT Renderer::Init(HINSTANCE hInstance, HWND hWnd)
{
	D3DDISPLAYMODE d3ddm;					// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));														// パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;												// 画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;											// 画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;												// バックバッファの形式
	d3dpp.BackBufferCount = 1;																	// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									// ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;													// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;									// デプスバッファ
	d3dpp.Windowed = RENDERER_WINDOWED;											// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// プレゼンテーションインターバル

		// Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
	{
		// Direct3Dデバイスの生成（描画処理はハードウェアで頂点処理はCPUで行う）
		if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
		{
			// Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// ハンドルの代入
	m_hwnd = hWnd;

	// レンダーステートの設定
	m_d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 成功を返す
	return S_OK;
}

//=============================================================
// 終了
//=============================================================
void Renderer::Uninit()
{
	// Direct3Dデバイスの破棄
	if (m_d3dDevice != nullptr)
	{
		m_d3dDevice->Release();
		m_d3dDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_d3d != nullptr)
	{
		m_d3d->Release();
		m_d3d = nullptr;
	}
}

//=============================================================
// 更新
//=============================================================
void Renderer::Update()
{

}

//=============================================================
// 描画
//=============================================================
void Renderer::Draw()
{
	// カメラを取得する
	auto& cameras = Camera::GetAllCameras();

	if (SUCCEEDED(m_d3dDevice->BeginScene()))
	{ // 描画開始が成功した場合
		for (auto itr = cameras.begin(); itr != cameras.end(); itr++)
		{
			// 非アクティブのとき
			if (!((*itr)->gameObject->GetActive() && (*itr)->GetActive()))
			{
				continue;
			}

			// 画面クリア（バッファクリア＆Zバッファクリア）
			m_d3dDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

			// カメラをセットする
			(*itr)->SetCamera();

			// ゲームオブジェクトを描画する
			GameObject::AllDraw();

			// ゲームオブジェクトをUI描画する
			GameObject::AllDrawUI();
		}

		// 描画終了
		m_d3dDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
