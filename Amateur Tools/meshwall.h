//=============================================================================
//
// ���b�V���ǂ̏��� [meshwall.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshWall					// ����������
(D3DXVECTOR3 pos, D3DXVECTOR3 rot,		// ���W�E��]
D3DXCOLOR col,							// �F
int nNumBlockX, int nNumBlockY,			// �u���b�N��(X,Z)
float fSizeBlockX, float fSizeBlockY);	// �u���b�N�T�C�Y(X,Z)

void UninitMeshWall(void);				// �I������
void UpdateMeshWall(void);				// �X�V����
void DrawMeshWall(void);				// �`�揈��


#endif
