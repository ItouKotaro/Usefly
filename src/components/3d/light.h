//------------------------------------------------------------
// @file		light.h
// @brief	���C�g
// @detail	3D�I�u�W�F�N�g��\�����邽�߂ɕK�v�ȃ��C�g
//------------------------------------------------------------
#ifndef _COMP_LIGHT_H_
#define _COMP_LIGHT_H_

#include "component.h"

//@brief ���C�g�R���|�[�l���g
class D3DLight : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	//@brief �^�C�v��ݒ肷��
	void SetType(D3DLIGHTTYPE type) { m_light.Type = type; }
	//@brief �g�U����ݒ肷��
	void SetDiffuse(D3DXCOLOR col) { m_light.Diffuse = col; }
	//@brief ������ݒ肷��
	void SetDirection(D3DXVECTOR3 dir) { m_light.Direction = dir; }

	//@brief �f�t�H���g�̃��C�g�ݒ�
	static void SetDefaultLight(GameObject* gameObject);
private:
	D3DLIGHT9 m_light;		// ���C�g
	static std::vector<D3DLight*> m_lights;
};

#endif // !_COMP_LIGHT_H_
