//=============================================================================
// < Amateur Toolsプログラム >
// 3Dマップのマネージャー処理 [3dMapManager.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "meshfield.h"
#include "meshwall.h"
#include "monoSpeaker.h"
#include "3dMapManager.h"

//*****************************************************************************
// グローバル変数:
//*****************************************************************************


//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT Init3dMapManager(int InitType)
{
	{	// 地面(01)
		InitMeshField	
		(FIELD_01_POS,							// 座標
		FIELD_01_ROT,							// 回転
		FIELD_01_X_MAX, FIELD_01_Z_MAX,			// ブロック数(X,Z)
		FILED_01_SIZE_X, FILED_01_SIZE_Z);		// ブロックサイズ(X,Z)
	}

	{	// 壁(前)
		InitMeshWall						
		(WALL_01_POS,							// 座標
		WALL_01_ROT,							// 回転
		WALL_01_COLOR,							// 色
		WALL_01_X_MAX, WALL_01_Y_MAX, 			// ブロック数(X,Y)
		WALL_01_SIZE_X, WALL_01_SIZE_Y);		// ブロックサイズ(X,Y)
	}

	{	// 壁(後)
		InitMeshWall
		(WALL_02_POS,							// 座標
		WALL_02_ROT,							// 回転
		WALL_02_COLOR,							// 色
		WALL_02_X_MAX, WALL_02_Y_MAX, 			// ブロック数(X,Y)
		WALL_02_SIZE_X, WALL_02_SIZE_Y);		// ブロックサイズ(X,Y)
	}

	{	// 壁(後)
		InitMeshWall
		(WALL_03_POS,							// 座標
		WALL_03_ROT,							// 回転
		WALL_03_COLOR,							// 色
		WALL_03_X_MAX, WALL_03_Y_MAX, 			// ブロック数(X,Y)
		WALL_03_SIZE_X, WALL_03_SIZE_Y);		// ブロックサイズ(X,Y)
	}

	{	// 壁(後)
		InitMeshWall
		(WALL_04_POS,							// 座標
		WALL_04_ROT,							// 回転
		WALL_04_COLOR,							// 色
		WALL_04_X_MAX, WALL_04_Y_MAX, 			// ブロック数(X,Y)
		WALL_04_SIZE_X, WALL_04_SIZE_Y);		// ブロックサイズ(X,Y)
	}

	// モノラルスピーカー
	InitMonoSpeaker(InitType);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit3dMapManager(void)
{
	{	// 地面
		UninitMeshField();
	}

	{	// 壁
		UninitMeshWall();
	}

	// モノラルスピーカー
	UninitMonoSpeaker();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update3dMapManager(void)
{
	{	// 地面
		UpdateMeshField();
	}

	{	// 壁
		UpdateMeshWall();
	}

	// モノラルスピーカー
	UpdateMonoSpeaker();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw3dMapManager(void)
{
	{	// 地面
		DrawMeshField();
	}

	{	// 壁
		DrawMeshWall();
	}

	// モノラルスピーカー
	DrawMonoSpeaker();
}
