//------------------------------------------------------------
// @file		PCH.h
// @brief	�v���R���p�C���ς݃w�b�_�[
//------------------------------------------------------------
#ifndef _PCH_H_
#define _PCH_H_

// �C���N���[�h
#include <iostream>
#include <string>
#include <vector>
#include "log.h"
#include "general/component.h"

// SDK
#include <Windows.h>
#include "d3dx9.h"
#include "d3d9.h"

// ���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// DirectX�R���|�[�l���g
#pragma comment(lib, "winmm.lib")	// �V�X�e�������擾�ɕK�v

#endif // !_PCH_H_