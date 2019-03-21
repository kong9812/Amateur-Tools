//=============================================================================
// < Amateur Toolsプログラム >
// チュートリアル処理 [tutorial.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "tutorial.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
TEXTURE			tutorialScreen;		// チュートリアル画面


//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitTutorial(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TUTORIAL_SCREEN,					// ファイルの名前
		&tutorialScreen.texture);					// 読み込むメモリー
	}

	{
		tutorialScreen.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 初期位置
	}

	// 頂点フォーマット
	MakeVtx4PointData(tutorialScreen.vertexWk, tutorialScreen.pos, SCREEN_WIDTH, SCREEN_HEIGHT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	if (tutorialScreen.texture != NULL)
	{// テクスチャの開放
		tutorialScreen.texture->Release();
		tutorialScreen.texture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	// ENTERキーを押したら進む
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_PLAYER);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, tutorialScreen.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tutorialScreen.vertexWk, sizeof(VERTEX_2D));

}


