//=============================================================================
//
// モデル処理 [camera.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

typedef struct	// エネミー構造体
{
	D3DXVECTOR3			EyePos;			// カメラの視点
	D3DXVECTOR3			AtPos;			// カメラの注視点
	D3DXVECTOR3			UpVec;			// カメラの上方向ベクトル

}CAMERA;

enum CAMERA_MODE
{
	CAMERA_1,
	CAMERA_2,
	CAMERA_3

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);			// 初期化
void UninitCamera(void);			// 終了処理
void UpdateCamera(void);			// 更新処理
void SetCamera(void);				// セットカメラ

void SetCameraAngleZ(float angle);	// カメラの角度を設定
float GetCameraAngleZ(void);		// カメラの角度を取得
CAMERA *GetCamera(void);			// カメラ情報を取得

#endif
