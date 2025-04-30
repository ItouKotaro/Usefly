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

// �O���錾
class Collision;

/**
 * @brief �A�N�V�����C���^�[�t�F�C�X
 * @details �����C�x���g�̒ʒm���s���܂�
*/
class ActionInterface : public btActionInterface
{
public:
	void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep) override;
	void debugDraw(btIDebugDraw* debugDrawer) {}
};

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

	//@brief ���[���h���擾����
	btDiscreteDynamicsWorld* GetWorld() { return m_world; }

	//@brief �R���W������ǉ�����
	void AddCollision(Collision* collision);
	//@brief �R���W�������폜����
	void RemoveCollision(Collision* collision);
	//@brief �R���W�������擾����
	std::vector<Collision*>& GetCollisions() { return m_collisions; }
	//@brief btCollisionObject����Collision��T��
	Collision* FindCollision(btCollisionObject* collisionObject);
private:
	/**
	 * @brief �����f�o�b�O�N���X
	 * @details �R���W���������o�����܂�
	*/
	class DebugPhysics : public btIDebugDraw
	{
	public:
		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
		void reportErrorWarning(const char* warningString) override {};
		void draw3dText(const btVector3& location, const char* textString) override {};
		void setDebugMode(int debugMode) override { m_debugMode = debugMode; };
		int getDebugMode() const override { return m_debugMode; };
	private:
		int m_debugMode;
	};

	btDiscreteDynamicsWorld* m_world;							// ���[���h
	btDefaultCollisionConfiguration* m_collisionConfiguration;	
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btGhostPairCallback* m_ghostPairCollback;
	DebugPhysics* m_debugDrawer;
	ActionInterface* m_actionInterface;
	std::vector<Collision*> m_collisions;
};


#endif // !_PHYSICS_H_
