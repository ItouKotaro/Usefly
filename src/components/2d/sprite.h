//------------------------------------------------------------
// @file		sprite.h
// @brief	�X�v���C�g
// @detail	2D�̔|���S��
//------------------------------------------------------------
#ifndef _COMP_SPRITE_H_
#define _COMP_SPRITE_H_

#include "component.h"

class Sprite : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void DrawUI() override;

	//@brief �e�N�X�`����ݒ肷��
	void SetTexture(std::string path);

	//@brief �e�N�X�`�����o�C���h����
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_texture = texture; }

	//@brief �A���J�[�|�C���g��ݒ肷��
	void SetAnchorPoint(D3DXVECTOR2 anchor) { m_anchorPoint = anchor; }
private:
	//@brief ���_���X�V����
	void UpdateVertex();

	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;	// ���_���
	LPDIRECT3DTEXTURE9 m_texture;				// �e�N�X�`��
	Transform m_oldTransform;						// �O��̃g�����X�t�H�[��
	D3DXVECTOR2 m_anchorPoint;					// �A���J�[�|�C���g
};

#endif // !_COMP_SPRITE_H_
