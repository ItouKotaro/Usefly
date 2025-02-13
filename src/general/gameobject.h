//------------------------------------------------------------
// @file		gameobject.h
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "sysyem/object.h"
#include "transform.h"

// コンポーネントの宣言
class Component;

//@brief ゲームオブジェクト
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

	//@brief 初期化
	void Init();
	//@brief 終了
	void Uninit();
	//@brief 更新
	void Update();
	//@brief 描画
	void Draw();
	//@brief UI描画
	void DrawUI();

	//@brief すべてのオブジェクトを更新する
	static void AllUpdate();
	//@brief すべてのオブジェクトを描画する
	static void AllDraw();
	//@brief すべてのオブジェクトをUI描画する
	static void AllDrawUI();

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

	/*
	@brief コンポーネントを取得する
	@param[in] includeChild : 子クラスを含めるか
	*/
	template<class T> inline T* GetComponent(const bool& includeChild = false) {
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // 子を含むとき
				if (T* pComp = dynamic_cast<T*>(*itr))
					return (T*)*itr;
			}
			else
			{ // 子を含まないとき
				if (typeid(T) == typeid(**itr))
					return (T*)*itr;
			}
		}
		return nullptr;
	}

	/*
	@brief 複数のコンポーネントを取得する
	@param[in] includeChild : 子クラスを含めるか
	*/
	template<class T> inline std::vector<T*> GetComponents(const bool& includeChild = false) {
		std::vector<T*> result;
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // 子を含むとき
				if (T* pComp = dynamic_cast<T*>(*itr))
					result.push_back((T*)*itr);
			}
			else
			{ // 子を含まないとき
				if (typeid(T) == typeid(**itr))
					result.push_back((T*)*itr);
			}
		}
		return result;
	}

	//@brief すべてのコンポーネントを取得する
	std::vector<Component*>& GetComponents() {
		return m_components;
	}

	//@brief コンポーネントをデタッチする
	void DetachComponent(Component* component);

	Transform* transform;	// トランスフォーム情報
private:
	//@brief 解放処理
	void Release() override;

	std::vector<Component*> m_components;
	static std::vector<GameObject*> m_gameObjects;
};

#endif // !_GAMEOBJECT_H_
