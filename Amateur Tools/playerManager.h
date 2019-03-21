//=============================================================================
//
// プレイヤーのマネージャー処理 [playerManager.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _PLAYER_MANAGER_CONTROL_
#define _PLAYER_MANAGER_CONTROL_

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerManager(int InitType);	// 初期化処理
void UninitPlayerManager(void);				// 終了処理
void UpdatePlayerManager(HWND hWnd);		// 更新処理
void DrawPlayerManager(HWND hWnd);			// 描画処理

#endif