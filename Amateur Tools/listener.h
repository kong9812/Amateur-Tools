//=============================================================================
//
// ���X�i�[���� [listener.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _LISTENER_H_
#define _LISTENER_H_

//=============================================================================
// �}�N����`
//=============================================================================
// ���X�i�[
#define LISTENER_MOVE_SPEED		(1.0f)
#define LISTENER_ROT_SPEED		(D3DXToRadian(1.0f))
#define LISTENER_EAR_ROT		D3DXVECTOR3(0.0f,0.0f,1.0f)
#define LISTENER_POS_INIT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define LISTENER_ROT_INIT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define LISTENER_X_MAX			(180)
#define LISTENER_X_MIN			(-180)
#define LISTENER_Z_MAX			(180)
#define LISTENER_Z_MIN			(-180)
#define LISTENER_SIZE			(10)

//=============================================================================
// �\���̐錾
//=============================================================================
// ���X�i�[�\����
typedef struct
{
	D3DXVECTOR3	pos;	// ���W
	D3DXVECTOR3 rot;	// ��]
	D3DXVECTOR3 earRot;	// ���̉�]
} LISTENER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitListener(void);		// ����������
void UpdateListener(void);		// �X�V����

LISTENER *GetListener(void);	// ���X�i�[�����擾

#endif