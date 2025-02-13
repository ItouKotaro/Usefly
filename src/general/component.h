//------------------------------------------------------------
// @file		component.h
// @brief	�R���|�[�l���g
//------------------------------------------------------------
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "gameobject.h"

//@brief �R���|�[�l���g�N���X
class Component : public Object
{
public:
	/*
	@brief ����������
	@details �R���|�[�l���g���ǉ����ꂽ�ۂɌĂ΂��C�x���g
	*/
	virtual void Init() {}

	/*
	@brief �I������
	@details �R���|�[�l���g���j�����ꂽ�ۂɌĂ΂��C�x���g [����]
	*/
	virtual void Uninit() {}

	/*
	@brief �X�V����
	@details ���t���[���Ă΂��C�x���g
	*/
	virtual void Update() {}

	/*
	@brief �I�u�W�F�N�g�`�揈��
	@details �I�u�W�F�N�g�`��̍ۂɌĂ΂��C�x���g
	*/
	virtual void Draw() {}

	/*
	@brief UI�`�揈��
	@details UI�`��̍ۂɌĂ΂��C�x���g
	*/
	virtual void DrawUI() {}

	/*
	@brief ���̃R���W�����Əd�Ȃ��Ă���Ƃ��ɌĂ΂��C�x���g
	*/
	virtual void OnTriggerStay(GameObject* other) {}

	/*
	@brief ���̃R���W�����������Ă����Ƃ��̃C�x���g
	*/
	virtual void OnTriggerEnter(GameObject* other) {}

	/*
	@brief ���̃R���W�������o���Ƃ��̃C�x���g
	*/
	virtual void OnTriggerExit(GameObject* other) {}

	/*
	@brief ���̃I�u�W�F�N�g�������ꂽ�Ƃ��ɌĂ΂��C�x���g
	*/
	virtual void OnDestroyOtherObject(Object* other) {}

	/*
	@brief �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
	@param[in] attachObj : �A�^�b�`��̃Q�[���I�u�W�F�N�g
	*/
	void AttachGameObject(GameObject* attachObj);

	GameObject* gameObject;	// �A�^�b�`��̃Q�[���I�u�W�F�N�g
	Transform* transform;		// �A�^�b�`��̃g�����X�t�H�[��
private:
	//@brief �������
	void Release() override;
};

#endif // !_COMPONENT_H_
