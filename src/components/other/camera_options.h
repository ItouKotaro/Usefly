//------------------------------------------------------------
// @file			camera_options.h
// @brief		カメラのオプション
//------------------------------------------------------------
#ifndef _CAMERA_OPTIONS_H_
#define _CAMERA_OPTIONS_H_

#include "component.h"

//@brief 描画オブジェクトの制限(カメラオプション)
class LimitObjects : public Component
{
public:
	//@brief 制限タイプ
	enum TYPE
	{
		WHITE,	// ホワイト (指定オブジェクトのみ描画)
		BLACK	// ブラック (指定オブジェクト以外描画)
	};
	LimitObjects() : m_type(WHITE), m_ignoreActive(false){}

	//@brief 制限タイプを設定する
	void SetLimitType(const TYPE& type) { m_type = type; }

	//@brief リストにオブジェクトを追加する
	void AddObject(GameObject* object);
	//@brief リストにオブジェクトを削除する
	void RemoveObject(GameObject* object);
	//@brief リストをリセットする
	void ResetObject();

	//@brief アクティブ状態を無視するか
	void SetIgnoreActive(const bool& enabled) { m_ignoreActive = enabled; }

	//@brief 描画する
	void LimitDraw();

private:
	TYPE m_type;
	bool m_ignoreActive;
	std::vector<GameObject*> m_objects;
};

#endif // !_CAMERA_OPTIONS_H_
