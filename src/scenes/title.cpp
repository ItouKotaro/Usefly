//------------------------------------------------------------
// @file		title.cpp
// @brief	�^�C�g���V�[��
//------------------------------------------------------------
#include "title.h"

#include "components/3d/camera.h"
#include "components/3d/light.h"
#include "components/3d/model.h"

//=============================================================
// ������
//=============================================================
void TitleScene::Init()
{
	// �J�������쐬����
	GameObject* camera = new GameObject("Camera");
	camera->AddComponent<Camera>();
	camera->transform->position.y = 5.0f;
	camera->transform->SetEulerAngle(0.1f, 0.0f, 0.0f);

	// ���C�g���쐬����
	GameObject* light = new GameObject("Light");
	D3DLight::SetDefaultLight(light);

	// ���f�����쐬����
	GameObject* model = new GameObject("TestModel");
	model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");
	model->transform->position = { 0.0f, 0.0f, 50.0f };
}
