//=============================================================================
//
// マップのマネージャー処理 [3dMapManager.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _3D_MAP_MANAGER_H_
#define _3D_MAP_MANAGER_H_


//=============================================================================
// マクロ定義
//=============================================================================
// 地面(01)
#define FIELD_01_POS		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 座標
#define FIELD_01_ROT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 回転
#define FIELD_01_X_MAX		(4)									// ブロックの数(X)
#define FIELD_01_Z_MAX		(4)									// ブロックの数(Z)
#define FILED_01_SIZE_X		(100.0f)							// ブロックのサイズ(X)
#define FILED_01_SIZE_Z		(100.0f)							// ブロックのサイズ(Z)

// 壁(前)
#define WALL_01_POS			D3DXVECTOR3(0.0f, 0.0f, 200.0f)		// 座標
#define WALL_01_ROT			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 回転
#define WALL_01_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
#define WALL_01_X_MAX		(40)								// ブロックの数(X)
#define WALL_01_Y_MAX		(5)									// ブロックの数(Y)
#define WALL_01_SIZE_X		(10.0f)								// ブロックのサイズ(X)
#define WALL_01_SIZE_Y		(10.0f)								// ブロックのサイズ(Y)

// 壁(後)
#define WALL_02_POS			D3DXVECTOR3(0.0f, 0.0f, -200.0f)	// 座標
#define WALL_02_ROT			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// 回転
#define WALL_02_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
#define WALL_02_X_MAX		(40)								// ブロックの数(X)
#define WALL_02_Y_MAX		(5)									// ブロックの数(Y)
#define WALL_02_SIZE_X		(10.0f)								// ブロックのサイズ(X)
#define WALL_02_SIZE_Y		(10.0f)								// ブロックのサイズ(Y)

// 壁(左)
#define WALL_03_POS			D3DXVECTOR3(-200.0f, 0.0f, 0.0f)	// 座標
#define WALL_03_ROT			D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f)	// 回転
#define WALL_03_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
#define WALL_03_X_MAX		(40)								// ブロックの数(X)
#define WALL_03_Y_MAX		(5)									// ブロックの数(Y)
#define WALL_03_SIZE_X		(10.0f)								// ブロックのサイズ(X)
#define WALL_03_SIZE_Y		(10.0f)								// ブロックのサイズ(Y)

// 壁(右)
#define WALL_04_POS			D3DXVECTOR3(200.0f, 0.0f, 0.0f)		// 座標
#define WALL_04_ROT			D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f)	// 回転
#define WALL_04_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// 色
#define WALL_04_X_MAX		(40)								// ブロックの数(X)
#define WALL_04_Y_MAX		(5)									// ブロックの数(Y)
#define WALL_04_SIZE_X		(10.0f)								// ブロックのサイズ(X)
#define WALL_04_SIZE_Y		(10.0f)								// ブロックのサイズ(Y)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init3dMapManager(int InitType);	// 初期化処理
void Uninit3dMapManager(void);			// 終了処理
void Update3dMapManager(void);			// 更新処理
void Draw3dMapManager(void);			// 描画処理

#endif