//------------------------------------------------------------
// @file		PCH.h
// @brief	プリコンパイル済みヘッダー
//------------------------------------------------------------
#ifndef _PCH_H_
#define _PCH_H_

// SDK
#include <Windows.h>
#include "d3dx9.h"
#include "d3d9.h"
#include <shlwapi.h>

// インクルード
#include <iostream>
#include <string>
#include <vector>
#include "sysyem/main.h"
#include "sysyem/log.h"
#include "sysyem/benlib.h"
#include "gameobject.h"

// ライブラリのリンク
#pragma comment(lib, "d3d9.lib")		// 描画処理に必要
#pragma comment(lib, "d3dx9.lib")		// 拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// DirectXコンポーネント
#pragma comment(lib, "winmm.lib")	// システム時刻取得に必要
#pragma comment(lib, "shlwapi.lib")	// ファイルの存在確認

// マクロ定義
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//@brief 頂点情報 [2D]
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;					// 座標変換用係数（1.0fで固定）
	D3DCOLOR col;			// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//@brief 頂点情報 [3D]
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;			// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

//@brief 範囲
template<class T = float>
class Range
{
public:
	Range() {}

	//@param vMin: 最小値
	//@param vMax: 最大値
	Range(const T& vMin, const T& vMax)
	{
		min = vMin;
		max = vMax;
	}

	T min;	// 最小値
	T max;	// 最大値

	//@brief 最小値と最大値を比べて、正しく並べ替える
	void Sort()
	{
		if (min > max)
		{
			T temp = min;
			min = max;
			max = temp;
		}
	}
};

#endif // !_PCH_H_