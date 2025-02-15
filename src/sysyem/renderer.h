//------------------------------------------------------------
// @file		renderer.h
// @brief	レンダラー
// @detail	描画を行うシステムです
//------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

//-----------------------------------------------------------
// 設定項目

// ウィンドウサイズ（横）
#define SCREEN_WIDTH					(1920)

// ウィンドウサイズ（高さ）
#define SCREEN_HEIGHT				(1080)

// ウィンドウか
#define RENDERER_WINDOWED		(TRUE)

//-----------------------------------------------------------


//@brief レンダラークラス
class Renderer final
{
public:
	Renderer() : m_d3d(nullptr), m_d3dDevice(nullptr), m_hwnd(nullptr) {}
	~Renderer() {}

	//@brief 初期化
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	//@brief 終了
	void Uninit();
	//@brief 更新
	void Update();
	//@brief 描画
	void Draw();

	//@brief デバイスを取得する
	LPDIRECT3DDEVICE9 GetDevice() { return m_d3dDevice; }
private:
	LPDIRECT3D9 m_d3d;								// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_d3dDevice;			// Direct3Dデバイスへのポインタ
	HWND m_hwnd;										// ハンドル
};

#endif // !_RENDERER_H_
