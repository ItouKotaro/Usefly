//------------------------------------------------------------
// @file		sprite.h
// @brief	�X�v���C�g
// @detail	2D�̔|���S��
//------------------------------------------------------------
#ifndef _COMP_SPRITE_H_
#define _COMP_SPRITE_H_

class Sprite : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void DrawUI() override;
private:

};

#endif // !_COMP_SPRITE_H_
