//=============================================================================
//
// �v���C���[�̃}�l�[�W���[���� [playerManager.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _PLAYER_MANAGER_CONTROL_
#define _PLAYER_MANAGER_CONTROL_

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerManager(int InitType);	// ����������
void UninitPlayerManager(void);				// �I������
void UpdatePlayerManager(HWND hWnd);		// �X�V����
void DrawPlayerManager(HWND hWnd);			// �`�揈��

#endif