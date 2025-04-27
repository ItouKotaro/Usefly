//------------------------------------------------------------
// @file		collision_test.cpp
// @brief	�R���W�����̃e�X�g
//------------------------------------------------------------
#include "collision_test.h"

void TestCollision::OnTriggerStay(Collision* other)
{
	Log::SendLog("�g���K�[ : �͈͓��ł�");
}

void TestCollision::OnTriggerEnter(Collision* other)
{
	Log::SendLog("�g���K�[ : �͈͂ɓ���܂���");
}

void TestCollision::OnTriggerExit(Collision* other)
{
	Log::SendLog("�g���K�[ : �͈͂���o�܂���");
}

void TestCollision::OnCollisionStay(Collision* other)
{
	Log::SendLog("�R���W���� : �͈͓��ł�");
}

void TestCollision::OnCollisionEnter(Collision* other)
{
	Log::SendLog("�R���W���� : �͈͂ɓ���܂���");
}

void TestCollision::OnCollisionExit(Collision* other)
{
	Log::SendLog("�R���W���� : �͈͂���o�܂���");
}
