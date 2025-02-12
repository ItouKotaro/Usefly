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
#define DEFAULT_SCREEN_WIDTH					(1920)

// ウィンドウサイズ（高さ）
#define DEFAULT_SCREEN_HEIGHT				(1080)

// ウィンドウか
#define RENDERER_WINDOWED		(TRUE)

//-----------------------------------------------------------


//@brief レンダラークラス
class Renderer final
{
public:
	Renderer() : m_d3d(nullptr), m_d3dDevice(nullptr), m_hwnd(nullptr) {}
	~Renderer() {}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();
private:
	LPDIRECT3D9 m_d3d;								// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_d3dDevice;			// Direct3Dデバイスへのポインタ
	HWND m_hwnd;										// ハンドル
};

#endif // !_RENDERER_H_
