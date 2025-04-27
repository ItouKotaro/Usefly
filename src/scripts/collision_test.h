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
	void OnTriggerStay(Collision* other) override;
	void OnTriggerEnter(Collision* other) override;
	void OnTriggerExit(Collision* other) override;

	void OnCollisionStay(Collision* other) override;
	void OnCollisionEnter(Collision* other) override;
	void OnCollisionExit(Collision* other) override;
};

#endif // !_COLLISION_TEST_H_
