//------------------------------------------------------------
// @file			physics.h
// @brief		物理
// @detail	物理演算の処理
//------------------------------------------------------------
#ifndef _PHYSICS_H_
#define _PHYSICS_H_

// インクルード
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// ライブラリのリンク
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

// 前方宣言
class Collision;

/**
 * @brief 物理クラス
 * @details 物理システムの根幹
*/
class Physics final
{
public:
	//@brief 初期化
	void Init();
	//@brief 終了
	void Uninit();
	//@brief 更新
	void Update();

	//@brief ワールドを取得する
	btDiscreteDynamicsWorld* GetWorld() { return m_world; }

	////@brief コリジョンオブジェクトを追加する
	//void AddCollisionObject(Collision* collision);
	////@brief コリジョンオブジェクトを削除する
	//void RemoveCollisionObject(Collision* collision);
private:
	btDiscreteDynamicsWorld* m_world;							// ワールド
	std::vector<btCollisionShape*> m_collisionShapes;		// 形状コリジョンリスト

	btDefaultCollisionConfiguration* m_collisionConfiguration;	
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btGhostPairCallback* m_ghostPairCollback;
};


#endif // !_PHYSICS_H_
