//------------------------------------------------------------
// @file		main.h
// @brief	メイン処理
// @detail	ウィンドウの作成やメインループ処理を行います
//------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

 // マクロ定義
#define CLASS_NAME			"WindowClass"	// クラス名
#define WINDOW_NAME	"Usefly"			// ウィンドウ名

// インクルード
#include <thread>

//@brief ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//@brief メインクラス
class Main final
{
public:
	Main();
	~Main();

	//@brief スレッドの開始
	void ThreadStart();
	//@brief スレッドの終了を待つ
	void ThreadJoin();

	//@brief デルタタイムを取得する
	static float getDeltaTime() { return m_deltaTime; }
	//@brief FPS値を取得する
	static int getFPS() { return m_fps; }
	//@brief ウィンドウのアクティブ状態を取得する
	static bool isActiveWindow();
	//@brief アプリケーションを終了する
	static void ExitApplication();
	//@brief カーソルの表示状態を変更する
	static void setShowCursor(const bool& show);
private:
	//@brief メインループ
	void MainLoop();

	std::thread* m_thread;		// スレッド
	DWORD m_currentTime;	// 現在時刻
	DWORD m_execLastTime;	// 前回の更新時刻
	DWORD m_fpsLastTime;		// 前回のFPS更新時刻
	int m_frameCount;				// フレームのカウント

	static float m_deltaTime;	// デルタタイム
	static int m_fps;					// FPS値
};

#endif // !_MAIN_H_