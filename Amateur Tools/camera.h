//=============================================================================
//
// ���f������ [camera.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

typedef struct	// �G�l�~�[�\����
{
	D3DXVECTOR3			EyePos;			// �J�����̎��_
	D3DXVECTOR3			AtPos;			// �J�����̒����_
	D3DXVECTOR3			UpVec;			// �J�����̏�����x�N�g��

}CAMERA;

enum CAMERA_MODE
{
	CAMERA_1,
	CAMERA_2,
	CAMERA_3

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);			// ������
void UninitCamera(void);			// �I������
void UpdateCamera(void);			// �X�V����
void SetCamera(void);				// �Z�b�g�J����

void SetCameraAngleZ(float angle);	// �J�����̊p�x��ݒ�
float GetCameraAngleZ(void);		// �J�����̊p�x���擾
CAMERA *GetCamera(void);			// �J���������擾

#endif
