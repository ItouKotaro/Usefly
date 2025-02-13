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

	/*
	@brief �R���|�[�l���g���擾����
	@param[in] includeChild : �q�N���X���܂߂邩
	*/
	template<class T> inline T* GetComponent(const bool& includeChild = false) {
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // �q���܂ނƂ�
				if (T* pComp = dynamic_cast<T*>(*itr))
					return (T*)*itr;
			}
			else
			{ // �q���܂܂Ȃ��Ƃ�
				if (typeid(T) == typeid(**itr))
					return (T*)*itr;
			}
		}
		return nullptr;
	}

	/*
	@brief �����̃R���|�[�l���g���擾����
	@param[in] includeChild : �q�N���X���܂߂邩
	*/
	template<class T> inline std::vector<T*> GetComponents(const bool& includeChild = false) {
		std::vector<T*> result;
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // �q���܂ނƂ�
				if (T* pComp = dynamic_cast<T*>(*itr))
					result.push_back((T*)*itr);
			}
			else
			{ // �q���܂܂Ȃ��Ƃ�
				if (typeid(T) == typeid(**itr))
					result.push_back((T*)*itr);
			}
		}
		return result;
	}

	//@brief ���ׂẴR���|�[�l���g���擾����
	std::vector<Component*>& GetComponents() {
		return m_components;
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
