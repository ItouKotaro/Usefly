//------------------------------------------------------------
// @file		collision_test.cpp
// @brief	コリジョンのテスト
//------------------------------------------------------------
#include "collision_test.h"

void TestCollision::OnTriggerStay(Collision* other)
{
	Log::SendLog("トリガー : 範囲内です");
}

void TestCollision::OnTriggerEnter(Collision* other)
{
	Log::SendLog("トリガー : 範囲に入りました");
}

void TestCollision::OnTriggerExit(Collision* other)
{
	Log::SendLog("トリガー : 範囲から出ました");
}

void TestCollision::OnCollisionStay(Collision* other)
{
	Log::SendLog("コリジョン : 範囲内です");
}

void TestCollision::OnCollisionEnter(Collision* other)
{
	Log::SendLog("コリジョン : 範囲に入りました");
}

void TestCollision::OnCollisionExit(Collision* other)
{
	Log::SendLog("コリジョン : 範囲から出ました");
}
