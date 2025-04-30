//------------------------------------------------------------
// @file			text.h
// @brief		�e�L�X�g
// @detail	�t�H���g��`�悵�܂�
//------------------------------------------------------------
#ifndef _TEXT_H_
#define _TEXT_H_

#include "component.h"

//@brief �e�L�X�g�R���|�[�l���g
class TextUI : public Component
{
public:
	//@brief �t�H���g�̎��
	enum FontType
	{
		ZENKAKU_GOTHIC,		// Zen Kaku Gothic New
		MAX
	};

public:
	//@brief ����
	enum ALIGN
	{
		LEFT,		// ������
		CENTER,	// ��������
		RIGHT		// �E����
	};

	//@brief �������
	struct TextInfo
	{
		IDirect3DTexture9* texture;	// �����̃e�N�X�`��
		D3DXVECTOR3 pos;				// �����ʒu
		int line;									// �s��
	};

	//@brief �t�H���g�f�[�^
	struct FontData
	{
		FontType type;
		std::string path;
		std::string name;
	};

	void Init() override;
	void Uninit() override;
	virtual void DrawUI() override;

	//@brief �e�L�X�g��ݒ肷��
	void SetText(const std::string& text);
	//@brief �F��ݒ肷��
	void SetColor(const D3DXCOLOR& color);
	//@brief �t�H���g�T�C�Y��ݒ肷��
	void SetFontSize(const int& size);
	//@brief �t�H���g�T�C�Y���擾����
	int GetFontSize() { return m_fontSize; }
	//@brief �t�H���g�̐F��ݒ肷��
	void SetFontColor(const D3DXCOLOR& color);
	//@brief �����̃T�C�Y��ݒ肷��
	void SetOutlineSize(const int& size);
	//@brief �����̐F��ݒ肷��
	void SetOutlineColor(const D3DXCOLOR& color);
	//@brief �t�H���g��ݒ肷��
	void SetFont(const FontType& fontType);
	//@brief �����ݒ肷��
	void SetAlign(const ALIGN& align);
	//@brief �����x��ݒ肷��
	void SetAlpha(const float& fAlpha);
	//@brief �����x���擾����
	float GetAlpha() { return m_alpha; }

	//@brief �t�H���g��ǂݍ��ށi�������j
	static void InitLoadFont();
	static const FontData loadFonts[FontType::MAX];
protected:
	LPD3DXSPRITE m_sprite;					// �X�v���C�g
	std::vector<TextInfo> m_textInfos;	// �����Ǘ�
	float m_maxHeight;								// �����̒��ł��ő�T�C�Y
	float m_alpha;										// �s�����x
private:
	void UpdateText();

	//@brief 1�����̃e�N�X�`���𐶐�����
	IDirect3DTexture9* CreateFontTexture(
		const char* faceName = "MS �S�V�b�N",
		unsigned char charSet = SHIFTJIS_CHARSET,
		const char* str = "T",
		unsigned fontHeight = 450,
		unsigned weight = 0,
		int penSize = 5,
		D3DXCOLOR edgeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXCOLOR fillColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
		int quality = 3,
		RECT* info = 0);

	// ���
	std::string m_text;					// ����
	unsigned char m_charSet;		// �����Z�b�g
	int m_fontSize;						// �t�H���g�T�C�Y
	float m_weight;						// �t�H���g�̑���
	int m_outlineSize;					// �A�E�g���C���T�C�Y
	D3DXCOLOR m_fillColor;			// �h��Ԃ��F
	D3DXCOLOR m_outlineColor;	// �A�E�g���C���F
	int m_quality;							// �A���`�G�C���A�X�i1�ȏ�j
	RECT* m_info;
	ALIGN m_align;						// ����

	// �t�H���g���
	std::string m_fontName;		// �t�H���g��
};

// �^�C�s���O�e�L�X�g
class TypingTextUI : public TextUI
{
public:
	TypingTextUI();
	void Update() override;
	void DrawUI() override;
	void SetTypingSpeed(const int& nSpeed) { m_typingSpeed = nSpeed; }
private:
	int m_typingCounter;	// �^�C�s���O�J�E���^�[
	int m_typingSpeed;		// �^�C�s���O�X�s�[�h
	int m_typingNum;		// �^�C�s���O�ς�
};

//@brief �e�L�X�g�^�O�i���j
class TextTag
{
public:
	enum TYPE
	{
		SIZE,
		COLOR,
		FONT_COLOR,
		EDGE_COLOR,
	};
	TextTag(const TYPE& type) { m_type = type; }
	void SetIdx(const int& idx) { m_idx = idx; }
	int GetIdx() { return m_idx; }
	TYPE GetType() { return m_type; }
private:
	int m_idx;
	TYPE m_type;
};

//@brief  �T�C�Y�^�O
class SizeTextTag : public TextTag
{
public:
	SizeTextTag() : TextTag(SIZE) {}
	void SetSize(const int& size) { m_size = size; }
	int GetSize() { return m_size; }
private:
	int m_size;
};

//@brief  �J���[�^�O
class ColorTextTag : public TextTag
{
public:
	ColorTextTag() : TextTag(COLOR) {}
	void SetColor(const D3DXCOLOR& color) { 
		m_fillColor = color; 
		m_edgeColor = color;
	}
	void SetFillColor(const D3DXCOLOR& color) { m_fillColor = color; }
	void SetEdgeColor(const D3DXCOLOR& color) { m_edgeColor = color; }
	D3DXCOLOR GetFillColor() { return m_fillColor; }
	D3DXCOLOR GetEdgeColor() { return m_edgeColor; }
private:
	D3DXCOLOR m_fillColor;
	D3DXCOLOR m_edgeColor;
};

//@brief  �t�H���g�J���[�^�O
class FontColorTextTag : public TextTag
{
public:
	FontColorTextTag() : TextTag(FONT_COLOR) {}
	void SetColor(const D3DXCOLOR& color) { m_color = color; }
	D3DXCOLOR GetColor() { return m_color; }
private:
	D3DXCOLOR m_color;
};

//@brief  �G�b�W�J���[�^�O
class EdgeColorTextTag : public TextTag
{
public:
	EdgeColorTextTag() : TextTag(EDGE_COLOR) {}
	void SetColor(const D3DXCOLOR& color) { m_color = color; }
	D3DXCOLOR GetColor() { return m_color; }
private:
	D3DXCOLOR m_color;
};

#endif // !_TEXT_H_
