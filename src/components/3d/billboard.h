//------------------------------------------------------------
// @file		billboard.h
// @brief	�r���{�[�h
//------------------------------------------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "component.h"

/**
 * @brief �r���{�[�h
*/
class Billboard : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//@brief �e�N�X�`�������蓖�Ă�
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_texture = texture; }
	//@brief �e�N�X�`�����摜�p�X����ݒ肷��
	void SetTexture(const std::string& path);
	//@brief �F��ݒ肷��
	void SetColor(const D3DXCOLOR& color);

	//@brief �F���擾����
	D3DXCOLOR GetColor() { return m_color; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_texture;					// �e�N�X�`��
	D3DXCOLOR m_color;									// �F
	TransformMonitor* m_monitor;
};

#endif // !_FIELD_H_
