//------------------------------------------------------------
// @file		title.cpp
// @brief	タイトルシーン
//------------------------------------------------------------
#include "title.h"

#include "components/3d/camera.h"
#include "components/3d/light.h"
#include "components/3d/model.h"
#include "components/3d/collision.h"
#include "scripts/collision_test.h"
#include "system/gizmo.h"
//=============================================================
// 初期化
//=============================================================
void TitleScene::Init()
{
	// ライトを作成する
	GameObject* light = new GameObject("Light");
	D3DLight::SetDefaultLight(light);

	// 床
	GameObject* floor = new GameObject("Floor");
	floor->AddComponent<BoxCollider>()->SetSize({ 100.0f, 0.5f, 100.0f });
	floor->transform->position.y -= 10.0f;

	// 判定
	GameObject* judge = new GameObject("Judge");
	judge->AddComponent<BoxCollider>()->SetSize({ 20.0f, 2.0f, 20.0f });
	judge->GetComponent<Collision>()->SetTrigger(true);
	//judge->AddComponent<TestCollision>();

	// カメラを作成する
	m_camera = new GameObject("Camera");
	m_camera->AddComponent<Camera>();
	m_camera->transform->position = { 0.0f, 10.0f, -100.0f };
}

//=============================================================
// 更新
//=============================================================
void TitleScene::Update()
{
	if (Input->GetKeyDown(KeyCode::Space))
	{
		// モデルを作成する
		GameObject* model = new GameObject("TestModel");
		model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");
		model->AddComponent<BoxCollider>()->SetSize({ 4.5f, 3.0f, 10.0f });
		model->GetComponent<BoxCollider>()->SetOffset({ 0.0f, 1.5f, 0.0f });
		model->AddComponent<RigidBody>();
		model->AddComponent<TestCollision>();
		model->transform->position.y += 50.0f;
	}
}
