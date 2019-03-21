//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshField							// 初期化処理
(D3DXVECTOR3 pos, D3DXVECTOR3 rot,				// 座標・回転
int nNumBlockX, int nNumBlockZ,					// ブロック数(X,Z)
float nBlockSizeX, float nBlockSizeZ);			// ブロックサイズ(X,Z)

void UninitMeshField(void);						// 終了処理
void UpdateMeshField(void);						// 更新処理
void DrawMeshField(void);						// 描画処理
		
#endif
