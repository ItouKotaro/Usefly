//------------------------------------------------------------
// @file			physics.h
// @brief		����
// @detail	�������Z�̏���
//------------------------------------------------------------
#ifndef _PHYSICS_H_
#define _PHYSICS_H_

// �C���N���[�h
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// ���C�u�����̃����N
#pragma comment(lib, "Bullet2FileLoader.lib")
#pragma comment(lib, "Bullet3Collision.lib")
#pragma comment(lib, "Bullet3Common.lib")
#pragma comment(lib, "Bullet3Dynamics.lib")
#pragma comment(lib, "Bullet3Geometry.lib")
#pragma comment(lib, "Bullet3OpenCL_clew.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletExampleBrowserLib.lib")
#pragma comment(lib, "BulletFileLoader.lib")
#pragma comment(lib, "BulletInverseDynamics.lib")
#pragma comment(lib, "BulletInverseDynamicsUtils.lib")
#pragma comment(lib, "BulletRobotics.lib")
#pragma comment(lib, "BulletRoboticsGUI.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "BulletWorldImporter.lib")
#pragma comment(lib, "BulletXmlWorldImporter.lib")
#pragma comment(lib, "BussIK.lib")
#pragma comment(lib, "clsocket.lib")
#pragma comment(lib, "ConvexDecomposition.lib")
#pragma comment(lib, "GIMPACTUtils.lib")
#pragma comment(lib, "gwen.lib")
#pragma comment(lib, "HACD.lib")
#pragma comment(lib, "LinearMath.lib")
#pragma comment(lib, "OpenGLWindow.lib")

/**
 * @brief �����N���X
 * @details �����V�X�e���̍���
*/
class Physics final
{
public:
	//@brief ������
	void Init();
	//@brief �I��
	void Uninit();
	//@brief �X�V
	void Update();
private:
	btDiscreteDynamicsWorld* m_world;										// ���[���h
	std::vector<btCollisionShape*> m_collisionShapes;				// �R���W�������X�g

	btDefaultCollisionConfiguration* m_collisionConfiguration;	
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btGhostPairCallback* m_ghostPairCollback;
};


#endif // !_PHYSICS_H_
