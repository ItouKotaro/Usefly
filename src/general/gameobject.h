//------------------------------------------------------------
// @file		gameobject.h
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "sysyem/object.h"
#include "general/transform.h"

// コンポーネントの宣言
class Component;

//@brief ゲームオブジェクト
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawUI();

	//@brief コンポーネントを追加する
	template<class T, typename ...Args > inline T* AddComponent(Args... args) {
		// コンポーネントを作成する
		T* component = new T(args...);

		// ゲームオブジェクトにアタッチする
		component->AttachGameObject(this);

		// コンポーネントを追加する
		m_components.push_back(component);

		// コンポーネントの初期化処理を実行する
		component->Init();

		// 作成したコンポーネントを返す
		return component;
	}


	Transform* transform;	// トランスフォーム情報
private:
	std::vector<Component*> m_components;
	static std::vector<GameObject*> m_gameObjects;
};

#endif // !_GAMEOBJECT_H_
