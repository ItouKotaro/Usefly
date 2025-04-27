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
	Component() : gameObject(nullptr), transform(nullptr) {};
	virtual ~Component() = default;

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
	@brief ���̃R���W�����ƐڐG���Ă���Ƃ��ɌĂ΂��C�x���g
	*/
	virtual void OnCollisionStay(Collision* other) {}

	/*
	@brief ���̃R���W�����ƐڐG�����Ƃ��̃C�x���g
	*/
	virtual void OnCollisionEnter(Collision* other) {}

	/*
	@brief ���̃R���W�����Ɨ��ꂽ�Ƃ��̃C�x���g
	*/
	virtual void OnCollisionExit(Collision* other) {}

	/*
	@brief �g���K�[�Ƒ��̃R���W�������d�Ȃ��Ă���Ƃ��ɌĂ΂��C�x���g
	*/
	virtual void OnTriggerStay(Collision* other) {}

	/*
	@brief �g���K�[�ɑ��̃R���W�����������Ă����Ƃ��̃C�x���g
	*/
	virtual void OnTriggerEnter(Collision* other) {}

	/*
	@brief �g���K�[���瑼�̃R���W�������o���Ƃ��̃C�x���g
	*/
	virtual void OnTriggerExit(Collision* other) {}

	/*
	@brief �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
	@param[in] attachObj : �A�^�b�`��̃Q�[���I�u�W�F�N�g
	*/
	void AttachGameObject(GameObject* attachObj);

	//@brief �I�u�W�F�N�g���f�^�b�`����
	void DetachGameObject();

	GameObject* gameObject;	// �A�^�b�`��̃Q�[���I�u�W�F�N�g
	Transform* transform;			// �A�^�b�`��̃g�����X�t�H�[��
private:
	//@brief �������
	void Release() override;
};

#endif // !_COMPONENT_H_
