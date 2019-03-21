//=============================================================================
//
// メッシュ壁の処理 [meshwall.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshWall					// 初期化処理
(D3DXVECTOR3 pos, D3DXVECTOR3 rot,		// 座標・回転
D3DXCOLOR col,							// 色
int nNumBlockX, int nNumBlockY,			// ブロック数(X,Z)
float fSizeBlockX, float fSizeBlockY);	// ブロックサイズ(X,Z)

void UninitMeshWall(void);				// 終了処理
void UpdateMeshWall(void);				// 更新処理
void DrawMeshWall(void);				// 描画処理


#endif
