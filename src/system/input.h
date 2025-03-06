//------------------------------------------------------------
// @file		input.h
// @brief	入力
// @detail	入力に対するトリガーを提供します
//------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "KeyTables.h"

//@brief 入力デバイス（ベース）
class InputDevice
{
public:
	//@brief 初期化
	virtual void Init(HINSTANCE hInstance, HWND hwnd) = 0;

	//@brief 終了
	virtual void Uninit() = 0;

	//@brief 更新
	virtual void Update() = 0;

	//@brief 入力情報の取得
	virtual bool GetKey(const std::string&) { return false; }
};



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

	//@brief 更新
	void Update();

private:
	LPDIRECTINPUT8 m_input;						// 入力
	std::vector<InputDevice*> m_devices;	// 入力デバイス
	std::vector<KeyCode> m_keyData;			// キーデータ
	std::vector<KeyCode> m_oldKeyData;	// 前回のキーデータ
};


#endif // !_INPUT_H_