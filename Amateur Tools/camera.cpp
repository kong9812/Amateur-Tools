//=============================================================================
// < Amateur Tools�v���O���� >
// �J�������� [camera.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "listener.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_CAMERA_P_X		(0.0f)											// �J�������_�̏����ʒu(X���W)
#define	POS_CAMERA_P_Y		(10.0f)											// �J�������_�̏����ʒu(Y���W)
#define	POS_CAMERA_P_Z		(0.0f)											// �J�������_�̏����ʒu(Z���W)
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z			(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(1000.0f)										// �r���[���ʂ�FarZ�l

#define CAMERA_ANGLE		(10.0f)
#define CAMERA_MOVE			(10.0f)

#define FPS_CAMERA			(1.0f)
#define TPS_CAMERA			(50.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CameraRot(void);

CAMERA CameraWk;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXMATRIX			g_mtxView;				// �r���[�}�g���b�N�X
D3DXMATRIX			g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X

float g_fCameraAngleZ = 0.0f;
float g_fPlayerAngle = 0.0f;

float g_fCameraLength = 0.0f;

int cameraMode = CAMERA_1;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	CAMERA *camera = GetCamera();

	camera->EyePos = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	camera->AtPos = D3DXVECTOR3(0.0f, POS_CAMERA_P_Y, 0.0f);
	camera->UpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_fCameraLength = FPS_CAMERA;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(void)
{
	CameraRot();
	SetCamera();
}

//=============================================================================
// �J������]
//=============================================================================
void CameraRot(void)
{
	CAMERA *camera = GetCamera();
	LISTENER *listener = GetListener();

	camera->AtPos.x = listener->pos.x;
	camera->AtPos.z = listener->pos.z;

	//if (cameraMode == CAMERA_1)
	//{
	//	if (GetKeyboardPress(DIK_UP))
	//	{
	//		camera->AtPos.y += CAMERA_MOVE;
	//		camera->EyePos.y += CAMERA_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_DOWN))
	//	{
	//		camera->AtPos.y -= CAMERA_MOVE;
	//		camera->EyePos.y -= CAMERA_MOVE;
	//	}
	//}

	//if (cameraMode == CAMERA_2)
	//{
	//	if (GetKeyboardPress(DIK_UP))
	//	{
	//		camera->AtPos.y += CAMERA_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_DOWN))
	//	{
	//		camera->AtPos.y -= CAMERA_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_LEFT))
	//	{
	//		g_fCameraAngleZ += CAMERA_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_RIGHT))
	//	{
	//		g_fCameraAngleZ -= CAMERA_MOVE;
	//	}
	//}

	//if (cameraMode == CAMERA_3)
	//{
	//	if (GetKeyboardPress(DIK_UP))
	//	{
	//		camera->AtPos.y += CAMERA_MOVE;
	//		camera->EyePos.y += CAMERA_MOVE;
	//	}
	//	if (GetKeyboardPress(DIK_DOWN))
	//	{
	//		camera->AtPos.y -= CAMERA_MOVE;
	//		camera->EyePos.y -= CAMERA_MOVE;
	//	}
	//}

	if (GetKeyboardTrigger(DIK_1))
	{
		g_fCameraLength = FPS_CAMERA;
		camera->EyePos.y = POS_CAMERA_P_Y;
		camera->AtPos.y = POS_CAMERA_P_Y;
		g_fCameraAngleZ = g_fPlayerAngle;
		cameraMode = CAMERA_1;
	}

	if (GetKeyboardTrigger(DIK_2))
	{
		g_fCameraLength = TPS_CAMERA;
		camera->EyePos.y = POS_CAMERA_P_Y;
		camera->AtPos.y = POS_CAMERA_P_Y;
		g_fCameraAngleZ = g_fPlayerAngle;
		cameraMode = CAMERA_2;
	}

	if (GetKeyboardTrigger(DIK_3))
	{
		g_fCameraLength = TPS_CAMERA;
		camera->EyePos.y = CAMERA_MOVE * 2;
		camera->AtPos.y = POS_CAMERA_P_Y;
		g_fCameraAngleZ = g_fPlayerAngle;
		cameraMode = CAMERA_3;
	}

	camera->EyePos.x = camera->AtPos.x - sinf(g_fCameraAngleZ) * g_fCameraLength;
	camera->EyePos.z = camera->AtPos.z - cosf(g_fCameraAngleZ) * g_fCameraLength;
}

//=============================================================================
// �J�����̐ݒu
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camera = GetCamera();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);	

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView,
		&camera->EyePos,		// �J�����̎��_
		&camera->AtPos,			// �J�����̒����_
		&camera->UpVec);		// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,		// �r���[���ʂ̎���p
		VIEW_ASPECT,	// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// �J�����̊p�x��ݒ�
//=============================================================================
void SetCameraAngleZ(float angle)
{
	g_fPlayerAngle += angle;
	g_fCameraAngleZ += angle;
}

//=============================================================================
// �J�����̊p�x���擾
//=============================================================================
float GetCameraAngleZ(void)
{
	return g_fCameraAngleZ;
}

//=============================================================================
// �J���������擾
//=============================================================================
CAMERA *GetCamera(void)
{
	return&CameraWk;
}

