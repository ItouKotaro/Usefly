//------------------------------------------------------------
// @file		transform.h
// @brief	トランスフォーム
// @detail	位置や回転などの情報を持つクラス
//------------------------------------------------------------
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "d3dx9.h"

//@brief トランスフォームクラス
class Transform
{
public:
	Transform() 
	{
		position = {0.0f, 0.0f, 0.0f};
		D3DXQuaternionIdentity(&rotation);
		scale = scale;
		size = { 1.0f, 1.0f };
		m_parent = nullptr;
	}

	//@brief 親を設定する
	void setParent(Transform* parent) { m_parent = parent; }
	//@brief 親を取得する
	Transform* getParent() { return m_parent; }

	//@brief オイラー角で回転を取得する
	D3DXVECTOR3 getEulerAngle();
	//@brief オイラー角で回転を設定する
	void setEulerAngle(float x, float y, float z);
	void setEulerAngle(D3DXVECTOR3 rotation) { setEulerAngle(rotation.x, rotation.y, rotation.z); }
	void setEulerAngle(float fAngle) { setEulerAngle(getEulerAngle().x, getEulerAngle().y, fAngle); }

	//@brief ワールド基準の位置を取得する
	D3DXVECTOR3 getWorldPosition();
	//@brief ワールド基準の回転を取得する
	D3DXQUATERNION getWorldRotation();
	//@brief ワールド基準のオイラー角を取得する
	D3DXVECTOR3 getWorldEulerAngle();
	//@brief ワールド基準のスケールを取得する
	D3DXVECTOR3 getWorldScale();

	//@brief マトリックスを取得する
	D3DXMATRIX& getMatrix();
	//@brief 位置情報マトリックスを取得する
	D3DXMATRIX getTranslationMatrix();
	//@brief 回転情報マトリックスを取得する
	D3DXMATRIX getRotationMatrix();

	D3DXVECTOR3 position;			// 位置
	D3DXQUATERNION rotation;	// 回転
	D3DXVECTOR3 scale;				// スケール
	D3DXVECTOR2 size;				// サイズ
private:
	//@brief クォータニオンをオイラー角に変換する
	D3DXVECTOR3 QuaternionToEulerAngle(D3DXQUATERNION q);

	D3DXMATRIX m_matrix;			// マトリックス
	Transform* m_parent;			// 親
};

#endif // !_TRANSFORM_H_
