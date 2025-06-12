//------------------------------------------------------------
// @file		shader.h
// @brief	シェーダー
// @detail	シェーダーの命令を行います
//------------------------------------------------------------
#ifndef _SHADER_H_
#define _SHADER_H_

#include "component.h"

/**
 * @brief シェーダーコンポーネント
 * @details シェーダーを適用します
*/
class Shader : public Component
{
public:
	void Update() override;

	//@brief 適用したいシェーダーを設定します
	void SetShader(const std::string& path) { m_data = Manager::GetInstance()->GetResourceDataManager()->RefShader(path); }
	//@brief 適用したいシェーダーを設定します
	void SetShader(ShaderData* data) { m_data = data; }
	//@brief テクニックを設定します
	void SetTechnique(const std::string& technique) { m_technique = technique; }
	//@brief リセットする
	void Reset();

	//---------------------------- ここから内部処理 ----------------------------

	//@brief 描画開始
	bool Begin();
	//@brief 描画終了
	void End();
	//@brief パス描画開始
	bool BeginPass(const UINT& pass);
	//@brief パス描画終了
	void EndPass();
	//@brief パス数を取得する
	UINT GetPassNum() { return m_passNum; }
private:
	// ビルトイン変数を更新する
	void UpdateVariable();

	ShaderData* m_data;
	std::string m_technique;
	UINT m_passNum;
};

#endif // !_SHADER_H_
