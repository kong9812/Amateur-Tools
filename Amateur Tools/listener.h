//=============================================================================
//
// リスナー処理 [listener.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _LISTENER_H_
#define _LISTENER_H_

//=============================================================================
// マクロ定義
//=============================================================================
// リスナー
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
// 構造体宣言
//=============================================================================
// リスナー構造体
typedef struct
{
	D3DXVECTOR3	pos;	// 座標
	D3DXVECTOR3 rot;	// 回転
	D3DXVECTOR3 earRot;	// 耳の回転
} LISTENER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitListener(void);		// 初期化処理
void UpdateListener(void);		// 更新処理

LISTENER *GetListener(void);	// リスナー情報を取得

#endif