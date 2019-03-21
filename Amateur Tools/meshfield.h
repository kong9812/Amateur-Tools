//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshField							// ����������
(D3DXVECTOR3 pos, D3DXVECTOR3 rot,				// ���W�E��]
int nNumBlockX, int nNumBlockZ,					// �u���b�N��(X,Z)
float nBlockSizeX, float nBlockSizeZ);			// �u���b�N�T�C�Y(X,Z)

void UninitMeshField(void);						// �I������
void UpdateMeshField(void);						// �X�V����
void DrawMeshField(void);						// �`�揈��
		
#endif
