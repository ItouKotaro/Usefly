//------------------------------------------------------------
// @file		PCH.h
// @brief	プリコンパイル済みヘッダー
//------------------------------------------------------------
#ifndef _PCH_H_
#define _PCH_H_

// インクルード
#include <iostream>
#include <string>
#include <vector>
#include "log.h"
#include "general/component.h"

// SDK
#include <Windows.h>
#include "d3dx9.h"
#include "d3d9.h"

// ライブラリのリンク
#pragma comment(lib, "d3d9.lib")		// 描画処理に必要
#pragma comment(lib, "d3dx9.lib")		// 拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// DirectXコンポーネント
#pragma comment(lib, "winmm.lib")	// システム時刻取得に必要

#endif // !_PCH_H_