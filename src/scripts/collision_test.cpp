//------------------------------------------------------------
// @file		collision_test.cpp
// @brief	コリジョンのテスト
//------------------------------------------------------------
#include "collision_test.h"

void TestCollision::OnTriggerStay(Collision* collision)
{
	Log::SendLog("範囲内です");
}

void TestCollision::OnTriggerEnter(Collision* collision)
{
	Log::SendLog("範囲に入りました");
}

void TestCollision::OnTriggerExit(Collision* collision)
{
	Log::SendLog("範囲から出ました");
}
