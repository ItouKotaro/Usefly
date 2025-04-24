//------------------------------------------------------------
// @file		gameobject.h
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "system/object.h"
#include "transform.h"

// マクロ定義
#define TAG_NODESTROY		"NO_DESTROY"

// コンポーネントの宣言
class Component;

//@brief ゲームオブジェクト
class GameObject : public Object
{
public:
	GameObject(std::string vName = "", std::string vTag = "");
	virtual ~GameObject();

	/**
	 * @brief 初期化
	 * @details ゲームオブジェクトに含まれるコンポーネントを初期化します（デフォルトでは使用されません）
	*/
	void Init();
	/**
	 * @brief 終了
	 * @details ゲームオブジェクトに含まれるコンポーネントを終了します（デフォルトでは使用されません）
	*/
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

	//@brief すべてのゲームオブジェクトを取得する
	static std::vector<GameObject*>& GetAllGameObjects() { return m_gameObjects; }

	Transform* transform;	// トランスフォーム情報
	std::string name;			// 名前
	std::string tag;				// タグ
private:
	//@brief 解放処理
	void Release() override;

	std::vector<Component*> m_components;					// コンポーネント
	static std::vector<GameObject*> m_gameObjects;		// すべてのゲームオブジェクト
};

#endif // !_GAMEOBJECT_H_
