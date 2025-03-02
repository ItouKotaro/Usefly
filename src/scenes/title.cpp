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
	// ライトを作成する
	GameObject* light = new GameObject("Light");
	D3DLight::SetDefaultLight(light);

	// モデルを作成する
	GameObject* model = new GameObject("TestModel");
	model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");

	// カメラを作成する
	m_camera = new GameObject("Camera");
	m_camera->AddComponent<Camera>();
	m_camera->transform->position = { 0.0f, 10.0f, -30.0f };
	//m_camera->transform->LookAt(model->transform->position);
}

//=============================================================
// 更新
//=============================================================
void TitleScene::Update()
{
	m_camera->transform->SetEulerAngle(0.0f, m_camera->transform->GetEulerAngle().y + 0.01f, 0.0f);
}
