//=============================================================================
// < Amateur Toolsプログラム >
// カメラ処理 [camera.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "listener.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_CAMERA_P_X		(0.0f)											// カメラ視点の初期位置(X座標)
#define	POS_CAMERA_P_Y		(10.0f)											// カメラ視点の初期位置(Y座標)
#define	POS_CAMERA_P_Z		(0.0f)											// カメラ視点の初期位置(Z座標)
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z			(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(1000.0f)										// ビュー平面のFarZ値

#define CAMERA_ANGLE		(10.0f)
#define CAMERA_MOVE			(10.0f)

#define FPS_CAMERA			(1.0f)
#define TPS_CAMERA			(50.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CameraRot(void);

CAMERA CameraWk;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXMATRIX			g_mtxView;				// ビューマトリックス
D3DXMATRIX			g_mtxProjection;			// プロジェクションマトリックス

float g_fCameraAngleZ = 0.0f;
float g_fPlayerAngle = 0.0f;

float g_fCameraLength = 0.0f;

int cameraMode = CAMERA_1;
//=============================================================================
// 初期化処理
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
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(void)
{
	CameraRot();
	SetCamera();
}

//=============================================================================
// カメラ回転
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
// カメラの設置
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camera = GetCamera();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);	

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView,
		&camera->EyePos,		// カメラの視点
		&camera->AtPos,			// カメラの注視点
		&camera->UpVec);		// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,		// ビュー平面の視野角
		VIEW_ASPECT,	// ビュー平面のアスペクト比
		VIEW_NEAR_Z,	// ビュー平面のNearZ値
		VIEW_FAR_Z);	// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの角度を設定
//=============================================================================
void SetCameraAngleZ(float angle)
{
	g_fPlayerAngle += angle;
	g_fCameraAngleZ += angle;
}

//=============================================================================
// カメラの角度を取得
//=============================================================================
float GetCameraAngleZ(void)
{
	return g_fCameraAngleZ;
}

//=============================================================================
// カメラ情報を取得
//=============================================================================
CAMERA *GetCamera(void)
{
	return&CameraWk;
}

