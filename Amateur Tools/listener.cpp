//=============================================================================
// < Amateur Tools�v���O���� >
// ���X�i�[���� [listener.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "monoSpeaker.h"
#include "Collider.h"
#include "listener.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LISTENER listenerWk;			// ���X�i�[�\����

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitListener(void)
{
	LISTENER *listener = GetListener();

	// ���X�i�[�̍��W
	listener->pos	= LISTENER_POS_INIT;
	listener->rot	= LISTENER_ROT_INIT;
	listener->earRot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateListener(void)
{
	LISTENER *listener = GetListener();
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();
	CAMERA *camera = GetCamera();
	D3DXMATRIX matRot;

	// �ړ��p�x�N�g��
	D3DXVECTOR3	move = LISTENER_POS_INIT;
	D3DXVECTOR3 oldPos = listener->pos;

	// �ړ�(�O)
	if (GetKeyboardPress(DIK_W))
	{
		move.z += cosf(listener->rot.y)*LISTENER_MOVE_SPEED;
		move.x -= sinf(listener->rot.y)*LISTENER_MOVE_SPEED;
	}

	// �ړ�(��)
	if (GetKeyboardPress(DIK_S))
	{
		move.z -= cosf(listener->rot.y)*LISTENER_MOVE_SPEED;
		move.x += sinf(listener->rot.y)*LISTENER_MOVE_SPEED;
	}

	// �ړ�(��)
	if (GetKeyboardPress(DIK_A))
	{
		listener->rot.y += LISTENER_ROT_SPEED;
		SetCameraAngleZ(-LISTENER_ROT_SPEED);
		// ���X�i�[��
		D3DXMatrixRotationYawPitchRoll(&matRot, -listener->rot.y, 0, 0);
		D3DXVec3TransformCoord(&listener->earRot, &LISTENER_EAR_ROT, &matRot);
	}

	// �ړ�(�E)
	if (GetKeyboardPress(DIK_D))
	{
		listener->rot.y -= LISTENER_ROT_SPEED;
		SetCameraAngleZ(LISTENER_ROT_SPEED);
		// ���X�i�[��
		D3DXMatrixRotationYawPitchRoll(&matRot, -listener->rot.y, 0, 0);
		D3DXVec3TransformCoord(&listener->earRot, &LISTENER_EAR_ROT, &matRot);
	}

	// ���ۂ̈ړ�
	listener->pos += move;
	
	// �����蔻��
	if (CheckHitBC(monoSpeaker->pos, listener->pos, MONO_SPEAKER_SIZE, LISTENER_SIZE))
	{// �߂�
		listener->pos = oldPos;
	}


	{// �ړ�����
		if (listener->pos.x <= LISTENER_X_MIN)
		{
			listener->pos.x = LISTENER_X_MIN;
		}
		if (listener->pos.z <= LISTENER_Z_MIN)
		{
			listener->pos.z = LISTENER_Z_MIN;
		}
		if (listener->pos.x >= LISTENER_X_MAX)
		{
			listener->pos.x = LISTENER_X_MAX;
		}
		if (listener->pos.z >= LISTENER_Z_MAX)
		{
			listener->pos.z = LISTENER_Z_MAX;
		}
	}
	// ���X�i�[�̐���
	if (monoSpeaker->soundBuffer != NULL)
	{
		SetListenerPos(listener->pos);
		SetListenerRot(listener->earRot);
	}
}

//=============================================================================
// ���X�i�[�����擾
//=============================================================================
LISTENER *GetListener(void)
{
	return &listenerWk;
}