//------------------------------------------------------------
// @file		component.h
// @brief	コンポーネント
//------------------------------------------------------------
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "gameobject.h"

//@brief コンポーネントクラス
class Component : public Object
{
public:
	Component() : gameObject(nullptr), transform(nullptr) {};
	virtual ~Component() = default;

	/*
	@brief 初期化処理
	@details コンポーネントが追加された際に呼ばれるイベント
	*/
	virtual void Init() {}

	/*
	@brief 終了処理
	@details コンポーネントが破棄された際に呼ばれるイベント [強制]
	*/
	virtual void Uninit() {}

	/*
	@brief 更新処理
	@details 毎フレーム呼ばれるイベント
	*/
	virtual void Update() {}

	/*
	@brief オブジェクト描画処理
	@details オブジェクト描画の際に呼ばれるイベント
	*/
	virtual void Draw() {}

	/*
	@brief UI描画処理
	@details UI描画の際に呼ばれるイベント
	*/
	virtual void DrawUI() {}

	/*
	@brief 他のコリジョンと重なっているときに呼ばれるイベント
	*/
	virtual void OnTriggerStay(Collision* collision) {}

	/*
	@brief 他のコリジョンが入ってきたときのイベント
	*/
	virtual void OnTriggerEnter(Collision* collision) {}

	/*
	@brief 他のコリジョンが出たときのイベント
	*/
	virtual void OnTriggerExit(Collision* collision) {}

	/*
	@brief ゲームオブジェクトにアタッチする
	@param[in] attachObj : アタッチ先のゲームオブジェクト
	*/
	void AttachGameObject(GameObject* attachObj);

	//@brief オブジェクトをデタッチする
	void DetachGameObject();

	GameObject* gameObject;	// アタッチ先のゲームオブジェクト
	Transform* transform;			// アタッチ先のトランスフォーム
private:
	//@brief 解放処理
	void Release() override;
};

#endif // !_COMPONENT_H_
