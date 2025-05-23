//------------------------------------------------------------
// @file			text.h
// @brief		テキスト
// @detail	フォントを描画します
//------------------------------------------------------------
#include "text.h"
#include <regex>

const TextUI::FontData TextUI::loadFonts[TextUI::FontType::MAX] = {
    {TextUI::FontType::ZENKAKU_GOTHIC, "data\\FONT\\ZenKakuGothicNew-Bold.ttf", "Zen Kaku Gothic New"},
};

//=============================================================
// フォントの読み込み
//=============================================================
void TextUI::InitLoadFont()
{
    std::string failedFont = "";
    int failedCounter = 0;
    for (int i = 0; i < FontType::MAX; i++)
    {
        if (!(AddFontResourceEx(loadFonts[i].path.c_str(), FR_PRIVATE, NULL) > 0))
        { // 失敗
            Log::SendLog(loadFonts[i].name + " のフォント読み込みに失敗しました！", Log::TYPE_ERROR);
        }
    }
}

//=============================================================
// 初期化
//=============================================================
void TextUI::Init()
{
    // スプライトを作成する
    if (FAILED(D3DXCreateSprite(Manager::GetInstance()->GetDevice(), &m_sprite)))
    { // 失敗時
        Log::SendLog("フォント表示用スプライトの生成に失敗しました", Log::TYPE_ERROR);
    }

    // 初期設定
    m_fontName = "MS ゴシック";
    m_fontSize = 100;
    m_outlineSize = 0;
    m_maxHeight = 0.0f;
    m_outlineColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_fillColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    m_align = ALIGN::LEFT;
    m_alpha = 1.0f;
}

//=============================================================
// 終了
//=============================================================
void TextUI::Uninit()
{
    // テキストデータの破棄
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        // フォントテクスチャの破棄
        if (m_textInfos[i].texture != nullptr)
        {
            m_textInfos[i].texture->Release();
            m_textInfos[i].texture = nullptr;
        }
    }
    m_textInfos.clear();

    // スプライトの破棄
    if (m_sprite != nullptr)
    {
        m_sprite->Release();
        m_sprite = nullptr;
    }
}

//=============================================================
// UI描画
//=============================================================
void TextUI::DrawUI()
{
    // スケールと回転のマトリックス
    D3DXMATRIX mtx, mtxScale, mtxRot;
    D3DXMatrixIdentity(&mtx);
    D3DXMatrixScaling(&mtxScale, transform->GetWorldScale().x, transform->GetWorldScale().y, transform->GetWorldScale().z);
    mtxRot = transform->GetRotationMatrix();
    D3DXMatrixMultiply(&mtx, &mtxScale, &mtxRot);

    // スプライトにマトリックスを適用する
    m_sprite->SetTransform(&mtx);

    m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

    for (auto itr = m_textInfos.begin(); itr != m_textInfos.end(); itr++)
    {
        D3DXVECTOR3 pos = { transform->GetWorldPosition().x + (*itr).pos.x, transform->GetWorldPosition().y - (*itr).pos.y + m_maxHeight * (*itr).line, 0.0f };
        m_sprite->Draw((*itr).texture, 0, 0, &pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
    }

    m_sprite->End();
}

//=============================================================
// テキストの設定
//=============================================================
void TextUI::SetText(const std::string& text)
{
    if (m_text != text)
    {
        m_text = text;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// 色の設定
//=============================================================
void TextUI::SetColor(const D3DXCOLOR& color)
{
    if (m_fillColor != color || m_outlineColor != color)
    {
        m_fillColor = color;
        m_outlineColor = color;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// フォントサイズの設定
//=============================================================
void TextUI::SetFontSize(const int& size)
{
    if (m_fontSize != size)
    {
        m_fontSize = size;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// フォント名の設定
//=============================================================
void TextUI::SetFont(const FontType& fontType)
{
    if (m_fontName != loadFonts[fontType].name)
    {
        m_fontName = loadFonts[fontType].name;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// 整列の設定
//=============================================================
void TextUI::SetAlign(const ALIGN& align)
{
    if (m_align != align)
    {
        m_align = align;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// 透明度の設定
//=============================================================
void TextUI::SetAlpha(const float& fAlpha)
{
    m_alpha = fAlpha;
}

//=============================================================
// アウトラインサイズの設定
//=============================================================
void TextUI::SetOutlineSize(const int& size)
{
    if (m_outlineSize != size)
    {
        m_outlineSize = size;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// アウトラインの色設定
//=============================================================
void TextUI::SetOutlineColor(const D3DXCOLOR& color)
{
    if (m_outlineColor != color)
    {
        m_outlineColor = color;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// フォントの色設定
//=============================================================
void TextUI::SetFontColor(const D3DXCOLOR& color)
{
    if (m_fillColor != color)
    {
        m_fillColor = color;

        // テキストの更新
        UpdateText();
    }
}

//=============================================================
// テキストの更新
//=============================================================
void TextUI::UpdateText()
{
    // 今までのテクスチャを破棄する
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        // フォントテクスチャの破棄
        if (m_textInfos[i].texture != nullptr)
        {
            m_textInfos[i].texture->Release();
            m_textInfos[i].texture = nullptr;
        }
    }
    m_textInfos.clear();
    m_maxHeight = 0.0f;

    // 表示テキスト
    std::string showText = m_text;

    // テキストタグ
    std::vector<TextTag*> vecTextTag;

    // サイズタグ
    std::regex sizeTag(R"(<size=(\d+)>)");
    std::smatch match;
    auto it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, sizeTag))
    {
        SizeTextTag* pSizeTag = new SizeTextTag();
        pSizeTag->SetSize(atoi(match.str(1).c_str()));

        pSizeTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pSizeTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // カラータグ
    std::regex colorTag(R"(<color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, colorTag))
    {
        ColorTextTag* pColorTag = new ColorTextTag();
        pColorTag->SetColor(D3DCOLOR_RGBA( atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // カラータグ（リセット）
    std::regex colorResetTag(R"(<color=reset>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, colorResetTag))
    {
        ColorTextTag* pColorTag = new ColorTextTag();
        pColorTag->SetFillColor(m_fillColor);
        pColorTag->SetEdgeColor(m_outlineColor);

        pColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // フォントカラータグ
    std::regex fontColorTag(R"(<font-color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, fontColorTag))
    {
        FontColorTextTag* pFontColorTag = new FontColorTextTag();
        pFontColorTag->SetColor(D3DCOLOR_RGBA(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pFontColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pFontColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // フォントカラータグ（リセット）
    std::regex fontColorResetTag(R"(<font-color=reset>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, fontColorResetTag))
    {
        FontColorTextTag* pFontColorTag = new FontColorTextTag();
        pFontColorTag->SetColor(m_fillColor);

        pFontColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pFontColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // エッジカラータグ
    std::regex edgeColorTag(R"(<edge-color=(\d+),\s?(\d+),\s?(\d+)>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, edgeColorTag))
    {
        EdgeColorTextTag* pEdgeColorTag = new EdgeColorTextTag();
        pEdgeColorTag->SetColor(D3DCOLOR_RGBA(atoi(match.str(1).c_str()), atoi(match.str(2).c_str()), atoi(match.str(3).c_str()), 255));

        pEdgeColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pEdgeColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    // エッジカラータグ（リセット）
    std::regex edgeColorResetTag(R"(<edge-color=reset>)");
    it = showText.cbegin();
    while (std::regex_search(it, showText.cend(), match, edgeColorResetTag))
    {
        EdgeColorTextTag* pEdgeColorTag = new EdgeColorTextTag();
        pEdgeColorTag->SetColor(m_outlineColor);

        pEdgeColorTag->SetIdx(static_cast<int>(match.position(0)));
        showText.erase(match.position(0), match.length());
        vecTextTag.push_back(pEdgeColorTag);

        // タグの位置調整
        for (int i = 0; i < (int)vecTextTag.size(); i++)
        {
            if (vecTextTag[i]->GetIdx() > match.position(0))
            {
                vecTextTag[i]->SetIdx(vecTextTag[i]->GetIdx() - static_cast<int>(match.length()));
            }
        }
    }

    int nTextLength = static_cast<int>(showText.length());     // 文字数
    float fTextWidth = 0.0f;
    int fontSize = m_fontSize;
    D3DXCOLOR fillColor = m_fillColor;
    D3DXCOLOR edgeColor = m_outlineColor;
    int lineCounter = 1;
    for (int i = 0; i < nTextLength; i++)
    {
        TextInfo textInfo;
        RECT strInfo;

        // テキストタグ
        for (int n = 0; n < (int)vecTextTag.size(); n++)
        {
            if (vecTextTag[n]->GetIdx() == i)
            {
                if (vecTextTag[n]->GetType() == TextTag::TYPE::SIZE)
                {
                    SizeTextTag* sizeTag = (SizeTextTag*)vecTextTag[n];
                    fontSize = sizeTag->GetSize();
                }
                else if (vecTextTag[n]->GetType() == TextTag::TYPE::COLOR)
                {
                    ColorTextTag* colorTag = (ColorTextTag*)vecTextTag[n];
                    fillColor = colorTag->GetFillColor();
                    edgeColor = colorTag->GetEdgeColor();
                }
                else if (vecTextTag[n]->GetType() == TextTag::TYPE::FONT_COLOR)
                {
                    FontColorTextTag* fontColorTag = (FontColorTextTag*)vecTextTag[n];
                    fillColor = fontColorTag->GetColor();
                }
                else if (vecTextTag[n]->GetType() == TextTag::TYPE::EDGE_COLOR)
                {
                    EdgeColorTextTag* edgeColorTag = (EdgeColorTextTag*)vecTextTag[n];
                    edgeColor = edgeColorTag->GetColor();
                }
            }
        }

        // 文字
        const char* pChar = nullptr;
        std::string text;
        if (IsDBCSLeadByte(showText[i]))
        { // 2バイト文字
            text = showText.substr(i, 2);
            pChar = text.c_str();
            i++;
        }
        else
        { // 1バイト文字
            text = showText.substr(i, 1);
            pChar = text.c_str();
        }

        // 改行
        if (strcmp(&pChar[0], "\n") == 0)
        {
            lineCounter++;
            fTextWidth = 0.0f;
            continue;
        }

        // フォントテクスチャの生成
        textInfo.texture = CreateFontTexture(
            m_fontName.c_str(),
            SHIFTJIS_CHARSET,
            pChar,
            fontSize,
            0,
            m_outlineSize,
            edgeColor,
            fillColor,
            3,
            &strInfo
        );

        // 描画位置を決める
        textInfo.pos = { fTextWidth, (float)strInfo.bottom - (float)strInfo.top, 0.0f };
        textInfo.line = lineCounter;
        fTextWidth += strInfo.right;

        if (m_maxHeight < textInfo.pos.y)
        {
            m_maxHeight = textInfo.pos.y;
        }

        m_textInfos.push_back(textInfo);
    }

    // 整列
    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        if (m_align == ALIGN::CENTER)
        { // 中央揃え
            m_textInfos[i].pos.x -= fTextWidth / 2;
        }
        else if (m_align == ALIGN::RIGHT)
        { // 右揃え
            m_textInfos[i].pos.x -= fTextWidth;
        }
    }

    // テキストタグを破棄する
    for (int i = 0; i < (int)vecTextTag.size(); i++)
    {
        if (vecTextTag[i] != nullptr)
        {
            delete vecTextTag[i];
            vecTextTag[i] = nullptr;
        }
    }
}

//=============================================================
// フォントテクスチャの生成（1文字）
//=============================================================
IDirect3DTexture9* TextUI::CreateFontTexture(
    const char* faceName,
    unsigned char charSet,
    const char* str,
    unsigned fontHeight,
    unsigned weight,
    int penSize,
    D3DXCOLOR edgeColor,
    D3DXCOLOR fillColor,
    int quality,
    RECT* info)
{
    penSize *= quality;
    IDirect3DTexture9* tex = 0;

    // ハンドルとデバイスの取得
    HWND hWnd = Main::GetInstance().GetHWND();
    LPDIRECT3DDEVICE9 pDevice = Manager::GetInstance()->GetDevice();

    // デバイスコンテキスト作成
    HDC hDC = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    // フォント作成
    LOGFONTA lf = {};
    lf.lfHeight = fontHeight * quality;
    lf.lfCharSet = charSet;
    lf.lfWeight = weight;
    lf.lfQuality = ANTIALIASED_QUALITY;
    memcpy(lf.lfFaceName, faceName, strlen(faceName));
    HFONT hFont = CreateFontIndirectA(&lf);
    HFONT oldFont = (HFONT)SelectObject(memDC, hFont);

    // 描画するBMPを作成
    TEXTMETRICA tm;
    GLYPHMETRICS gm;
    MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
    int len = IsDBCSLeadByte(str[0]) ? 2 : 1;
    UINT code = (len == 2 ? (unsigned char)str[0] << 8 | (unsigned char)str[1] : (unsigned char)str[0]);
    GetTextMetricsA(memDC, &tm);
    GetGlyphOutlineA(memDC, code, GGO_METRICS, &gm, 0, 0, &mat);

    RECT charRegion =
    {
            gm.gmptGlyphOrigin.x - penSize / 2,
            tm.tmAscent - gm.gmptGlyphOrigin.y - penSize / 2,
            gm.gmptGlyphOrigin.x + (LONG)gm.gmBlackBoxX + penSize / 2,
            tm.tmAscent - gm.gmptGlyphOrigin.y + (LONG)gm.gmBlackBoxY + penSize / 2
    };

    RECT charWH = { 0, 0, ((LONG)gm.gmBlackBoxX + penSize + quality - 1) / quality * quality, ((LONG)gm.gmBlackBoxY + penSize + quality - 1) / quality * quality };
    int bmpW = charWH.right;
    int bmpH = charWH.bottom;
    BITMAPINFO bmpInfo = {};
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = bmpW;
    bmpInfo.bmiHeader.biHeight = -bmpH;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 24;
    unsigned char* p = 0;
    HBITMAP hBitMap = CreateDIBSection(0, &bmpInfo, DIB_RGB_COLORS, (void**)&p, 0, 0);
    HBITMAP oldBMP = (HBITMAP)SelectObject(memDC, hBitMap);

    // BMP背景を青色で初期化
    HBRUSH bgBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
    FillRect(memDC, &charWH, bgBrush);
    DeleteObject(bgBrush);

    // パスを描く
    // パス色は緑、塗は赤
    HPEN   hPen = (HPEN)CreatePen(PS_SOLID, penSize, RGB(0, 255, 0));
    HBRUSH hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
    HPEN   oldPen = (HPEN)SelectObject(memDC, hPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

    SetBkMode(memDC, TRANSPARENT);
    BeginPath(memDC);
    TextOutA(memDC, -charRegion.left, -charRegion.top, str, len);
    EndPath(memDC);
    StrokeAndFillPath(memDC);

    SelectObject(memDC, oldPen);
    SelectObject(memDC, oldBrush);
    SelectObject(memDC, oldFont);
    SelectObject(memDC, oldBMP);
    DeleteObject(hBrush);
    DeleteObject(hPen);
    DeleteObject(hFont);

    // DirectXのテクスチャにBMPの色分けを使いフォントを穿つ
    int texW = charWH.right / quality;
    int texH = charWH.bottom / quality;
    int q2 = quality * quality;
    if (FAILED(pDevice->CreateTexture(texW, texH, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, 0)))
    {
        return nullptr;
    }
    D3DLOCKED_RECT lockR;
    if (SUCCEEDED(tex->LockRect(0, &lockR, 0, 0))) {
        char* d = (char*)lockR.pBits;
        unsigned BMPPitch = (charWH.right * 3 + 3) / 4 * 4;
        for (int y = 0; y < texH; y++) {
            for (int x = 0; x < texW; x++) {
                unsigned& v = *((unsigned*)d + x + y * texW);   // テクスチャのピクセル位置
                unsigned alph = 0;
                unsigned edge = 0;
                unsigned fill = 0;
                // quality倍率分点を平均化
                for (int i = 0; i < quality; i++) {
                    for (int j = 0; j < quality; j++) {
                        alph += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 0];
                        edge += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 1];
                        fill += p[(y * quality + i) * BMPPitch + (x * quality + j) * 3 + 2];
                    }
                }
                alph /= q2;
                edge /= q2;
                fill /= q2;

                // 色の形式変換
                int colEdge[4] = { (int)(edgeColor.r * 255), (int)(edgeColor.g * 255), (int)(edgeColor.b * 255), (int)(edgeColor.a * 255) };
                int colFill[4] = { (int)(fillColor.r * 255), (int)(fillColor.g * 255), (int)(fillColor.b * 255), (int)(fillColor.a * 255) };

                // 不透明の場合はブレンド色を採用
                unsigned a = 0xff - alph;
                if (a < 0xff) {
                    // 半透明
                    unsigned r = colEdge[0];
                    unsigned g = colEdge[1];
                    unsigned b = colEdge[2];
                    a = (a * colEdge[3]) >> 8;
                    v = a << 24 | r << 16 | g << 8 | b;
                }
                else {
                    // 不透明
                    unsigned r = ((colEdge[0] * edge) >> 8) + ((colFill[0] * fill) >> 8);
                    unsigned g = ((colEdge[1] * edge) >> 8) + ((colFill[1] * fill) >> 8);
                    unsigned b = ((colEdge[2] * edge) >> 8) + ((colFill[2] * fill) >> 8);
                    a = ((colEdge[3] * edge) >> 8) + ((colFill[3] * fill) >> 8);
                    v = a << 24 | r << 16 | g << 8 | b;
                }
            }
        }
        tex->UnlockRect(0);
    }

    DeleteObject(hBitMap);
    DeleteDC(memDC);

    if (info) {
        info->left = charRegion.left / quality;
        info->top = charRegion.top / quality;
        info->right = (gm.gmCellIncX + penSize) / quality;
        info->bottom = (tm.tmHeight + penSize) / quality;
    }
    return tex;
}


//=============================================================
// コンストラクタ
//=============================================================
TypingTextUI::TypingTextUI()
{
    m_typingSpeed = 30;
    m_typingCounter = 0;
    m_typingNum = 0;
}

//=============================================================
// 更新
//=============================================================
void TypingTextUI::Update()
{
    m_typingCounter--;
    if (m_typingCounter <= 0 &&
        m_typingNum <= (int)m_textInfos.size())
    {
        m_typingNum++;

        // リセット
        m_typingCounter = m_typingSpeed;
    }
}

//=============================================================
// 描画
//=============================================================
void TypingTextUI::DrawUI()
{
    m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

    for (int i = 0; i < (int)m_textInfos.size(); i++)
    {
        if (i < m_typingNum)
        {
            D3DXVECTOR3 pos = { transform->GetWorldPosition().x + m_textInfos[i].pos.x, transform->GetWorldPosition().y - m_textInfos[i].pos.y + m_maxHeight, 0.0f };
            m_sprite->Draw(m_textInfos[i].texture, 0, 0, &pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_alpha));
        }
    }

    m_sprite->End();
}