//------------------------------------------------------------
// @file		shader.cpp
// @brief	シェーダー
// @detail	シェーダーの命令を行います
//------------------------------------------------------------
#include "shader.h"

//=============================================================
// 更新
//=============================================================
void Shader::Update()
{
	if (m_data != nullptr)
	{
		LPD3DXEFFECT effect = m_data->GetEffect();

		effect->SetFloat("_deltaTime", Main::GetInstance().GetDeltaTime());
		effect->SetFloat("_elapsedTime", static_cast<float>(Main::GetInstance().GetElapsedTime() * 0.001f));
	}
}

//=============================================================
// リセット
//=============================================================
void Shader::Reset()
{
	m_data = nullptr;
	m_technique = "";
	m_passNum = 0;
}

//=============================================================
// 描画開始
//=============================================================
bool Shader::Begin()
{
	if (m_data == nullptr)
	{
		m_passNum = 1;
		return true;	// 標準描画を使う
	}

	// 変数を設定する
	UpdateVariable();
	
	// テクニックを設定する
	m_data->GetEffect()->SetTechnique(m_technique.c_str());

	return SUCCEEDED(m_data->GetEffect()->Begin(&m_passNum, 0));
}

//=============================================================
// 描画終了
//=============================================================
void Shader::End()
{
	if (m_data != nullptr)
	{
		m_data->GetEffect()->End();
	}
}

//=============================================================
// パス描画開始
//=============================================================
bool Shader::BeginPass(const UINT& pass)
{
	if (m_data != nullptr)
	{
		return SUCCEEDED(m_data->GetEffect()->BeginPass(pass));
	}

	return true;	// 標準シェーダー
}

//=============================================================
// パス描画終了
//=============================================================
void Shader::EndPass()
{
	if (m_data != nullptr)
	{
		m_data->GetEffect()->EndPass();
	}
}

//=============================================================
// ビルトイン変数を更新する
//=============================================================
void Shader::UpdateVariable()
{
	auto device = Manager::GetInstance()->GetDevice();

	// WVP
	D3DXMATRIX worldMtx, viewMtx, projMtx;
	device->GetTransform(D3DTS_WORLD, &worldMtx);
	device->GetTransform(D3DTS_VIEW, &viewMtx);
	device->GetTransform(D3DTS_PROJECTION, &projMtx);
	D3DXMATRIX wvp = worldMtx * viewMtx * projMtx;
	m_data->GetEffect()->SetMatrix("_wvp", &wvp);
	m_data->GetEffect()->SetMatrix("_world", &worldMtx);
	m_data->GetEffect()->SetMatrix("_view", &viewMtx);
	m_data->GetEffect()->SetMatrix("_proj", &projMtx);

	// 法線行列
	D3DXMATRIX normalMtx = worldMtx;
	D3DXMatrixInverse(&normalMtx, NULL, &worldMtx);
	D3DXMatrixTranspose(&normalMtx, &normalMtx);
	m_data->GetEffect()->SetMatrix("_normal", &normalMtx);
}
