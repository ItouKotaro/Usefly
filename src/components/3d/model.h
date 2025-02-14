//------------------------------------------------------------
// @file		model.h
// @brief	���f��
// @detail	3D�̃��f��
//------------------------------------------------------------
#ifndef _COMP_MODEL_H_
#define _COMP_MODEL_H_

#include "component.h"
#include "sysyem/resource_data.h"

//@brief ���f���R���|�[�l���g
class Model : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;
	void Load(std::string path);
private:
	ModelData* m_modelData;											// ���f���f�[�^
	std::vector<LPDIRECT3DTEXTURE9> m_textures;		// �e�N�X�`��
};

#endif // !_COMP_MODEL_H_
