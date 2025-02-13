//------------------------------------------------------------
// @file		gameobject.h
// @brief	�Q�[���I�u�W�F�N�g
// @detail	�R���|�[�l���g�̏����������I�u�W�F�N�g�ł�
//------------------------------------------------------------
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "sysyem/object.h"
#include "transform.h"

// �R���|�[�l���g�̐錾
class Component;

//@brief �Q�[���I�u�W�F�N�g
class GameObject : public Object
{
public:
	GameObject();
	virtual ~GameObject();

	//@brief ������
	void Init();
	//@brief �I��
	void Uninit();
	//@brief �X�V
	void Update();
	//@brief �`��
	void Draw();
	//@brief UI�`��
	void DrawUI();

	//@brief ���ׂẴI�u�W�F�N�g���X�V����
	static void AllUpdate();
	//@brief ���ׂẴI�u�W�F�N�g��`�悷��
	static void AllDraw();
	//@brief ���ׂẴI�u�W�F�N�g��UI�`�悷��
	static void AllDrawUI();

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

	//@brief �R���|�[�l���g���f�^�b�`����
	void DetachComponent(Component* component);

	Transform* transform;	// �g�����X�t�H�[�����
private:
	//@brief �������
	void Release() override;

	std::vector<Component*> m_components;
	static std::vector<GameObject*> m_gameObjects;
};

#endif // !_GAMEOBJECT_H_
