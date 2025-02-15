//------------------------------------------------------------
// @file		object.h
// @brief	�I�u�W�F�N�g
// @detail	�I�u�W�F�N�g�ނ̊�{�N���X
//------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//@brief �I�u�W�F�N�g�N���X
class Object
{
public:
	Object();
	virtual ~Object();

	//@brief �f�X�t���O�̃I�u�W�F�N�g��j������
	static void ReleaseDeathFlag();

	//@brief ���ׂẴI�u�W�F�N�g��j������
	static void AllDestroy();

	//@brief �I�u�W�F�N�g��j������
	static void Destroy(Object* obj) { obj->m_deathFlag = true; }

protected:
	//@brief �������
	virtual void Release() = 0;
private:
	bool m_deathFlag;
	static std::vector<Object*> m_objects;
};

#endif // !_OBJECT_H_

