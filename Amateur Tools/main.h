//=============================================================================
//
// main���� [main.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//=============================================================================
// �}�N����`
//=============================================================================
#define CLASS_NAME		_T("AppClass")		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		_T("Amateur Tools")	// �E�C���h�E�̃L���v�V������

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W
#define PERCENT			(100)				// �p�[�Z���g�v�Z�p

#define	NUM_VERTEX		(4)					// ���_��

#define HALF			(2)					// �����Ɋ���p(2)

#define NUM_POLYGON		(2)					// �|���S��

#define ERROR_MSG_MAX	(100)				// �G���[���b�Z�[�W�̕�����

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=============================================================================
// �\���̐錾
//=============================================================================
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum E_STAGE		// ��ʑJ�ڒ萔
{
	STAGE_TUTORIAL,
	STAGE_PLAYER,
	STAGE_WAVE,
	STAGE_3D,
	STAGE_REVERB
};

enum INIT			// �������萔
{
	FIRST_INIT,
	RE_INIT
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�擾�֐�

void SetStage(int stage);
int GetStage(void);	
void SetGameLoop(bool GameLoop);

#endif