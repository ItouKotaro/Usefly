//------------------------------------------------------------
// @file		title.cpp
// @brief	�^�C�g���V�[��
//------------------------------------------------------------
#include "title.h"

#include "components/3d/model.h"

//=============================================================
// ������
//=============================================================
void TitleScene::Init()
{
	// ���f�����쐬����
	GameObject* model = new GameObject("TestModel");
	model->AddComponent<Model>()->Load("data\\MODEL\\bench.x");


}
