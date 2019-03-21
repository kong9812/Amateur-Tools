//=============================================================================
// < Amateur Toolsプログラム >
// モノラルスピーカーの処理 [monoSpeaker.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "basic.h"
#include "sound.h"
#include "reverb.h"
#include "listener.h"
#include "monoSpeaker.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Set3DStage(void);			// 画面遷移

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT			objectMonoSpeaker;	// 3Dオブジェクト
MONO_SPEAKER	monoSpeakerWk;		// モノラルスピーカー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMonoSpeaker(int initType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	if (initType == FIRST_INIT)
	{
		// オブジェクトの初期化
		objectMonoSpeaker.Texture = NULL;
		objectMonoSpeaker.Mesh = NULL;
		objectMonoSpeaker.BuffMat = NULL;
		objectMonoSpeaker.NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(
			MONO_SPEAKER_MODEL,			// 読み込むモデルファイル名(Xファイル)
			D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
			pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
			NULL,						// 隣接性データを含むバッファへのポインタ
			&objectMonoSpeaker.BuffMat,	// マテリアルデータを含むバッファへのポインタ
			NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
			&objectMonoSpeaker.NumMat,	// D3DXMATERIAL構造体の数
			&objectMonoSpeaker.Mesh)))	// ID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}
	}

	// 位置・回転・スケールの初期設定
	monoSpeaker->pos = MONO_SPEAKER_POS;
	monoSpeaker->rot = D3DXVECTOR3(0.0f, -D3DX_PI / HALF, 0.0f);
	monoSpeaker->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	monoSpeaker->reverb = DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMonoSpeaker(void)
{
	if (objectMonoSpeaker.Texture != NULL)
	{// テクスチャの開放
		objectMonoSpeaker.Texture->Release();
		objectMonoSpeaker.Texture = NULL;
	}

	if (objectMonoSpeaker.Mesh != NULL)
	{// メッシュの開放
		objectMonoSpeaker.Mesh->Release();
		objectMonoSpeaker.Mesh = NULL;
	}

	if (objectMonoSpeaker.BuffMat != NULL)
	{// マテリアルの開放
		objectMonoSpeaker.BuffMat->Release();
		objectMonoSpeaker.BuffMat = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonoSpeaker(void)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	if (monoSpeaker->soundBuffer == NULL)
	{// 音を読み込み
		monoSpeaker->soundBuffer = LoadSound(SOUND_3D);
		// 再生
		PlaySound(monoSpeaker->soundBuffer, E_DS8_FLAG_LOOP);
	}

	if (!IsPlaying(monoSpeaker->soundBuffer))
	{
		// 再生
		PlaySound(monoSpeaker->soundBuffer, E_DS8_FLAG_LOOP);
	}	

	// 画面遷移
	Set3DStage();
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawMonoSpeaker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	DRAW_TOOL MonoSpeakerTool;
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&objectMonoSpeaker.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&MonoSpeakerTool.mtxScl, monoSpeaker->scl.x, monoSpeaker->scl.y, monoSpeaker->scl.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&MonoSpeakerTool.mtxRot, monoSpeaker->rot.y, monoSpeaker->rot.x, monoSpeaker->rot.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&MonoSpeakerTool.mtxTranslate, monoSpeaker->pos.x, monoSpeaker->pos.y, monoSpeaker->pos.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &objectMonoSpeaker.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&MonoSpeakerTool.matDef);

	// マテリアル情報に対するポインタを取得(元に戻すためのBackUp)
	MonoSpeakerTool.pD3DXMat = (D3DXMATERIAL*)objectMonoSpeaker.BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)objectMonoSpeaker.NumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&MonoSpeakerTool.pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, objectMonoSpeaker.Texture);

		// 描画
		objectMonoSpeaker.Mesh->DrawSubset(nCntMat);
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&MonoSpeakerTool.matDef);

}

//=============================================================================
// モノラルスピーカーの情報を取得
//=============================================================================
MONO_SPEAKER *GetMonoSpeaker(void)
{
	return&monoSpeakerWk;
}

//=============================================================================
// 画面遷移
//=============================================================================
void Set3DStage(void)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// プレイヤー
	if (GetKeyboardTrigger(DIK_1))
	{
		StopSound(monoSpeaker->soundBuffer);
		SetStage(STAGE_PLAYER);
	}

	// 波形
	else if (GetKeyboardTrigger(DIK_2))
	{
		StopSound(monoSpeaker->soundBuffer);
		SetStage(STAGE_WAVE);
	}
}
