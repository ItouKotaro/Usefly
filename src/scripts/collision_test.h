//------------------------------------------------------------
// @file		collision_test.h
// @brief	コリジョンのテスト
//------------------------------------------------------------
#ifndef _COLLISION_TEST_H_
#define _COLLISION_TEST_H_

#include "component.h"

class TestCollision : public Component
{
public:
	void OnTriggerStay(Collision* collision) override;
	void OnTriggerEnter(Collision* collision) override;
	void OnTriggerExit(Collision* collision) override;
};

#endif // !_COLLISION_TEST_H_
