//------------------------------------------------------------
// @file		model.h
// @brief	モデル
// @detail	3Dのモデル
//------------------------------------------------------------
#ifndef _COMP_MODEL_H_
#define _COMP_MODEL_H_

#include "component.h"
#include "system/resource_data.h"

//@brief モデルコンポーネント
class Model : public Component
{
public:
	Model() : m_modelData(nullptr) {}
	void Init() override;
	void Uninit() override;
	void Draw() override;

	/**
	 * @brief モデルを読み込みます
	 * @param[in] path : Xファイルのパス
	*/
	void Load(std::string path);
private:
	ModelData* m_modelData;											// モデルデータ
	std::vector<LPDIRECT3DTEXTURE9> m_textures;		// テクスチャ
};

#endif // !_COMP_MODEL_H_
