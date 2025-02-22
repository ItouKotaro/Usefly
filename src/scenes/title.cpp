//------------------------------------------------------------
// @file		title.cpp
// @brief	タイトルシーン
//------------------------------------------------------------
#include "title.h"

#include "components/3d/camera.h"
#include "components/3d/light.h"
#include "components/3d/model.h"
#include "components/2d/sprite.h"

//=============================================================
// 初期化
//=============================================================
void TitleScene::Init()
{
	// ポリゴンを生成する
	GameObject* poly = new GameObject("Polygon");
	poly->AddComponent<Sprite>();
	poly->transform->size = { 300.0f, 300.0f };
	poly->transform->SetEulerAngle(0.2f);

	// ライトを作成する
	GameObject* light = new GameObject("Light");
	D3DLight::SetDefaultLight(light);

	// モデルを作成する
	GameObject* model = new GameObject("TestModel");
	model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");
	model->transform->position = { 0.0f, 0.0f, 50.0f };

	// カメラを作成する
	GameObject* camera = new GameObject("Camera");
	camera->AddComponent<Camera>();
	camera->transform->LookAt(model->transform->position);
}
