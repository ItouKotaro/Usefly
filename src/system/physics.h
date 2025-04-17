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

/**
 * @brief 物理クラス
 * @details 物理システムの根幹
*/
class Physics final
{
public:
	//@brief インスタンスの取得
	static Physics& GetInstance()
	{
		static Physics instance;
		return instance;
	}

private:
	Physics() = default;
	~Physics() = default;
};


#endif // !_PHYSICS_H_
