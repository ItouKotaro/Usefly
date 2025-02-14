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
#include "sysyem/log.h"
#include "gameobject.h"

// SDK
#include <Windows.h>
#include "d3dx9.h"
#include "d3d9.h"
#include <shlwapi.h>

// ���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// DirectX�R���|�[�l���g
#pragma comment(lib, "winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib, "shlwapi.lib")	// �t�@�C���̑��݊m�F

// �}�N����`
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;					// ���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

#endif // !_PCH_H_