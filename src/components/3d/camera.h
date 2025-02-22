//------------------------------------------------------------
// @file		camera.h
// @brief	カメラ
// @detail	3D空間に存在するオブジェクトを描画するためのデバイス
//------------------------------------------------------------
#ifndef _COMP_CAMERA_H_
#define _COMP_CAMERA_H_

#include "component.h"

// 定義
constexpr float CLIPPING_NEAR = 0.1f;			// 最短描画距離
constexpr float CLIPPING_FAR = 2000.0f;			// 最高描画距離
constexpr float CAMERA_LENGTH = 100.0f;		// 視点と注視点の距離

//@brief カメラコンポーネント
class Camera : public Component
{
public:
	//@brief 投影モード
	enum MODE
	{
		MODE_PERSPECTIVE,		// 透視投影
		MODE_PARALLEL,			// 平行投影
	};

	//@brief 初期化
	void Init() override;
	//@brief 終了
	void Uninit() override;
	//@brief 更新
	void Update() override;

	//@brief 上向きベクトルを設定する
	void SetVectorUp(D3DXVECTOR3 up) { m_vecU = up; }
	//@brief 視点と注視点の距離を設定する
	void SetLength(float length) { m_length = length; }
	//@brief 最短描画距離を設定する
	void SetClippingPlaneNear(float value) { m_clippingPlanes.min = value; }
	//@brief 最高描画距離を設定する
	void SetClippingPlaneFar(float value) { m_clippingPlanes.max = value; }
	//@brief 投影モードを設定する
	void SetMode(MODE mode) { m_mode = mode; }

	//@brief 上向きベクトルを取得する
	D3DXVECTOR3 GetVectorUp() { return m_vecU; }
	//@brief 視点と注視点の距離を取得する
	float GetLength() { return m_length; }
	//@brief 最短描画距離を取得する
	float GetClippingPlaneNear() { return m_clippingPlanes.min; }
	//@brief 最高描画距離を取得する
	float GetClippingPlaneFar() { return m_clippingPlanes.max; }
	//@brief 投影モードを取得する
	MODE GetMode() { return m_mode; }

	//@brief ビューポートの位置を設定する
	void SetViewportPosition(float x, float y);
	//@brief ビューポートのサイズを設定する
	void SetViewportSize(float width, float height);

	//@brief カメラの設置
	void SetCamera();

	//@brief すべてのカメラを取得する
	static const std::vector<Camera*>& GetAllCameras() { return m_cameras; }
private:
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_vecU;				// 上向きベクトル
	float m_length;							// 視点と注視点の距離
	Range<float> m_clippingPlanes;	// 描画範囲
	MODE m_mode;							// 投影モード

	D3DXMATRIX m_projMtx;			// プロジェクションマトリックス
	D3DXMATRIX m_viewMtx;			// ビューマトリックス
	D3DVIEWPORT9 m_viewport;		// ビューポート

	static std::vector<Camera*> m_cameras;
};

#endif // !_COMP_CAMERA_H_
