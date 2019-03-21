//=============================================================================
// < Amateur Toolsプログラム >
// リスナー処理 [listener.cpp]
// Author : 蔡 友剛
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
// グローバル変数:
//*****************************************************************************
LISTENER listenerWk;			// リスナー構造体

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitListener(void)
{
	LISTENER *listener = GetListener();

	// リスナーの座標
	listener->pos	= LISTENER_POS_INIT;
	listener->rot	= LISTENER_ROT_INIT;
	listener->earRot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateListener(void)
{
	LISTENER *listener = GetListener();
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();
	CAMERA *camera = GetCamera();
	D3DXMATRIX matRot;

	// 移動用ベクトル
	D3DXVECTOR3	move = LISTENER_POS_INIT;
	D3DXVECTOR3 oldPos = listener->pos;

	// 移動(前)
	if (GetKeyboardPress(DIK_W))
	{
		move.z += cosf(listener->rot.y)*LISTENER_MOVE_SPEED;
		move.x -= sinf(listener->rot.y)*LISTENER_MOVE_SPEED;
	}

	// 移動(後)
	if (GetKeyboardPress(DIK_S))
	{
		move.z -= cosf(listener->rot.y)*LISTENER_MOVE_SPEED;
		move.x += sinf(listener->rot.y)*LISTENER_MOVE_SPEED;
	}

	// 移動(左)
	if (GetKeyboardPress(DIK_A))
	{
		listener->rot.y += LISTENER_ROT_SPEED;
		SetCameraAngleZ(-LISTENER_ROT_SPEED);
		// リスナー耳
		D3DXMatrixRotationYawPitchRoll(&matRot, -listener->rot.y, 0, 0);
		D3DXVec3TransformCoord(&listener->earRot, &LISTENER_EAR_ROT, &matRot);
	}

	// 移動(右)
	if (GetKeyboardPress(DIK_D))
	{
		listener->rot.y -= LISTENER_ROT_SPEED;
		SetCameraAngleZ(LISTENER_ROT_SPEED);
		// リスナー耳
		D3DXMatrixRotationYawPitchRoll(&matRot, -listener->rot.y, 0, 0);
		D3DXVec3TransformCoord(&listener->earRot, &LISTENER_EAR_ROT, &matRot);
	}

	// 実際の移動
	listener->pos += move;
	
	// 当たり判定
	if (CheckHitBC(monoSpeaker->pos, listener->pos, MONO_SPEAKER_SIZE, LISTENER_SIZE))
	{// 戻る
		listener->pos = oldPos;
	}


	{// 移動制限
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
	// リスナーの制御
	if (monoSpeaker->soundBuffer != NULL)
	{
		SetListenerPos(listener->pos);
		SetListenerRot(listener->earRot);
	}
}

//=============================================================================
// リスナー情報を取得
//=============================================================================
LISTENER *GetListener(void)
{
	return &listenerWk;
}