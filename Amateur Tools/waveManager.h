//=============================================================================
//
// �g�̃}�l�[�W���[���� [waveManager.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _WAVE_MANAGER_CONTROL_
#define _WAVE_MANAGER_CONTROL_


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitWaveManager(int InitType);	// ����������
void UninitWaveManager(void);			// �I������
void UpdateWaveManager(HWND hWnd);		// �X�V����
void DrawWaveManager(void);				// �`�揈��

#endif