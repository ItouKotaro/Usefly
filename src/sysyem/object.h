//------------------------------------------------------------
// @file		object.h
// @brief	オブジェクト
// @detail	オブジェクト類の基本クラス
//------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//@brief オブジェクトクラス
class Object
{
public:
	Object();
	virtual ~Object();

	//@brief デスフラグのオブジェクトを破棄する
	static void ReleaseDeathFlag();

	//@brief すべてのオブジェクトを破棄する
	static void AllDestroy();

	//@brief オブジェクトを破棄する
	static void Destroy(Object* obj) { obj->m_deathFlag = true; }

protected:
	//@brief 解放処理
	virtual void Release() = 0;
private:
	bool m_deathFlag;
	static std::vector<Object*> m_objects;
};

#endif // !_OBJECT_H_

