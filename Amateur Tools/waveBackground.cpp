//=============================================================================
// < Amateur Toolsプログラム >
// 波の背景処理 [waveBackground.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "waveBackground.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理


//*****************************************************************************
// グローバル変数
//*****************************************************************************
TEXTURE				waveBackground;	// 背景

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWaveBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_WAVE_BACKGROUND,						// ファイルの名前
		&waveBackground.texture);					// 読み込むメモリー
	}

	// 頂点フォーマット(著作権宣言)
	MakeVtx4PointData(waveBackground.vertexWk, waveBackground.pos, SCREEN_WIDTH, SCREEN_HEIGHT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWaveBackground(void)
{
	if (waveBackground.texture != NULL)
	{// テクスチャの開放
		waveBackground.texture->Release();
		waveBackground.texture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWaveBackground(void)
{
	// 特になし :D
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWaveBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, waveBackground.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, waveBackground.vertexWk, sizeof(VERTEX_2D));
}
