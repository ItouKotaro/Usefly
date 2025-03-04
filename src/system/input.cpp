#include "input.h"

//=============================================================
// コンストラクタ
//=============================================================
InputManager::InputManager()
	: m_input(nullptr)
{
}

//=============================================================
// 初期化
//=============================================================
bool InputManager::Init(HINSTANCE hInstance, HWND hwnd)
{
	// DirectInputオブジェクトの生成
	if (m_input != nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, nullptr)))
		{
			Log::SendLog("入力オブジェクトの生成に失敗しました（DirectInput8）", Log::TYPE_ERROR);
			return false;
		}
	}

	return true;
}

//=============================================================
// 終了
//=============================================================
void InputManager::Uninit()
{
	// DirectInputオブジェクトの破棄
	if (m_input != nullptr)
	{
		m_input->Release();
		m_input = nullptr;
	}
}
