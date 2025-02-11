//------------------------------------------------------------
// @file		component.cpp
// @brief	コンポーネント
//------------------------------------------------------------
#include "component.h"

//=============================================================
// ゲームオブジェクトにアタッチする
//=============================================================
void Component::AttachGameObject(GameObject* attachObj)
{
	if (!m_attached)
	{ // アタッチされていないとき
		gameObject = attachObj;
		transform = gameObject->transform;
		m_attached = true;
	}
}