//------------------------------------------------------------
// @file		collision_test.cpp
// @brief	�R���W�����̃e�X�g
//------------------------------------------------------------
#include "collision_test.h"

void TestCollision::OnTriggerStay(Collision* collision)
{
	Log::SendLog("�͈͓��ł�");
}

void TestCollision::OnTriggerEnter(Collision* collision)
{
	Log::SendLog("�͈͂ɓ���܂���");
}

void TestCollision::OnTriggerExit(Collision* collision)
{
	Log::SendLog("�͈͂���o�܂���");
}
