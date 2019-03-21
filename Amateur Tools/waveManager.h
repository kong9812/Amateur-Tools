//=============================================================================
//
// 波のマネージャー処理 [waveManager.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _WAVE_MANAGER_CONTROL_
#define _WAVE_MANAGER_CONTROL_


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWaveManager(int InitType);	// 初期化処理
void UninitWaveManager(void);			// 終了処理
void UpdateWaveManager(HWND hWnd);		// 更新処理
void DrawWaveManager(void);				// 描画処理

#endif