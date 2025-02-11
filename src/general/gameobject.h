//------------------------------------------------------------
// @file		gameobject.h
// @brief	�Q�[���I�u�W�F�N�g
// @detail	�R���|�[�l���g�̏����������I�u�W�F�N�g�ł�
//------------------------------------------------------------
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "sysyem/object.h"
#include "general/transform.h"

// �R���|�[�l���g�̐錾
class Component;

//@brief �Q�[���I�u�W�F�N�g
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawUI();

	//@brief �R���|�[�l���g��ǉ�����
	template<class T, typename ...Args > inline T* AddComponent(Args... args) {
		// �R���|�[�l���g���쐬����
		T* component = new T(args...);

		// �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
		component->AttachGameObject(this);

		// �R���|�[�l���g��ǉ�����
		m_components.push_back(component);

		// �R���|�[�l���g�̏��������������s����
		component->Init();

		// �쐬�����R���|�[�l���g��Ԃ�
		return component;
	}


	Transform* transform;	// �g�����X�t�H�[�����
private:
	std::vector<Component*> m_components;
	static std::vector<GameObject*> m_gameObjects;
};

#endif // !_GAMEOBJECT_H_
