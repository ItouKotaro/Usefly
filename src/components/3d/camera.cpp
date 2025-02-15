//------------------------------------------------------------
// @file		camera.cpp
// @brief	カメラ
// @detail	3D空間に存在するオブジェクトを描画するためのデバイス
//------------------------------------------------------------
#include "camera.h"
#include "sysyem/manager.h"

std::vector<Camera*> Camera::m_cameras;

//=============================================================
// 初期化
//=============================================================
void Camera::Init()
{
	// 初期設定
	m_vecU = { 0.0f, 1.0f, 0.0f };
	m_posR = { 0.0f, 0.0f, 0.0f };
	m_length = CAMERA_LENGTH;
	m_mode = MODE::MODE_PERSPECTIVE;

	// 描画距離の設定
	m_clippingPlanes.min = CLIPPING_NEAR;
	m_clippingPlanes.max = CLIPPING_FAR;
	m_clippingPlanes.Sort();

	// ビューポートの設定
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewportPosition(0.0f, 0.0f);
	SetViewportSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	// カメラリストに追加する
	m_cameras.push_back(this);
}

//=============================================================
// 終了
//=============================================================
void Camera::Uninit()
{
	// カメラリストから削除する
	for (auto itr = m_cameras.begin(); itr != m_cameras.end(); itr++)
	{
		if (*itr == this)
		{
			m_cameras.erase(itr);
			break;
		}
	}
}

//=============================================================
// 更新
//=============================================================
void Camera::Update()
{
	// 前方から指定の長さ分伸ばす
	D3DXMATRIX rotMtx = transform->GetRotationMatrix();
	m_posR = { 0.0f, 0.0f, m_length };
	D3DXVec3TransformCoord(&m_posR, &m_posR, &rotMtx);

	// 位置を加算する
	m_posR += transform->GetWorldPosition();
}

//=============================================================
// ビューポートの位置を設定する
//=============================================================
void Camera::SetViewportPosition(float x, float y)
{
	m_viewport.X = static_cast<DWORD>(x);
	m_viewport.Y = static_cast<DWORD>(y);
}

//=============================================================
// ビューポートのサイズを設定する
//=============================================================
void Camera::SetViewportSize(float width, float height)
{
	m_viewport.Width = static_cast<DWORD>(width);
	m_viewport.Height = static_cast<DWORD>(height);
}

//=============================================================
// カメラの設置
//=============================================================
void Camera::SetCamera()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_projMtx);

	// ウィンドウサイズの取得
	D3DXVECTOR2 windowSize = Main::GetWindowSize();

	// 投影モードごとに設定する
	switch (m_mode)
	{
	case Camera::MODE_PERSPECTIVE:
		D3DXMatrixPerspectiveFovLH(
			&m_projMtx,
			D3DXToRadian(45.0f),
			windowSize.x / windowSize.y,
			m_clippingPlanes.min,
			m_clippingPlanes.max);
		break;

	case Camera::MODE_PARALLEL:
		D3DXMatrixOrthoLH(
			&m_projMtx,
			windowSize.x,
			windowSize.y,
			m_clippingPlanes.min,
			m_clippingPlanes.max);

		// スケーリング調整
		D3DXMATRIX mtxScale;
		D3DXMatrixIdentity(&mtxScale);
		D3DXMatrixScaling(&mtxScale, 10.0f, 10.0f, 1.0f);
		D3DXMatrixMultiply(&m_projMtx, &m_projMtx, &mtxScale);
		break;
	}

	// プロジェクションマトリックスの設定
	device->SetTransform(D3DTS_PROJECTION, &m_projMtx);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_viewMtx);

	// ビューマトリックスの作成
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	D3DXMatrixLookAtLH(&m_viewMtx, &pos, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	device->SetTransform(D3DTS_VIEW, &m_viewMtx);

	// ビューポートの設定
	device->SetViewport(&m_viewport);
}
