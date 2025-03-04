//------------------------------------------------------------
// @file		input.h
// @brief	入力
// @detail	入力に対するトリガーを提供します
//------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//@brief 入力マネージャー
class InputManager final
{
public:
	//@brief コンストラクタ
	InputManager();

	//@brief 初期化
	bool Init(HINSTANCE hInstance, HWND hwnd);

	//@brief 終了
	void Uninit();

private:
	LPDIRECTINPUT8 m_input;
};


#endif // !_INPUT_H_