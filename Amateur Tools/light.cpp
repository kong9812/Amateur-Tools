//=============================================================================
// < Amateur Toolsプログラム >
// モデル処理 [light.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_LIGHT			(5)	// ライトの数

#define LIGHT00_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT01_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT02_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT03_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT04_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)

#define LIGHT00_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT01_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT02_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT03_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT04_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)

#define LIGHT00_DIRECTON	D3DXVECTOR3(-1.0f, -1.0f, 1.0f)
#define LIGHT01_DIRECTON	D3DXVECTOR3(-1.0f, -1.0f, -1.0f)
#define LIGHT02_DIRECTON	D3DXVECTOR3(1.0f, -1.0f, 1.0f)
#define LIGHT03_DIRECTON	D3DXVECTOR3(1.0f, -1.0f, -1.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetLight(int no, _D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXCOLOR ambient, D3DXVECTOR3 dir);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9			g_aLight[NUM_LIGHT];		// ライト情報


//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	SetLight(0, D3DLIGHT_DIRECTIONAL, LIGHT00_DIFFUSE, LIGHT00_AMBIENT, LIGHT00_DIRECTON);
	SetLight(1, D3DLIGHT_DIRECTIONAL, LIGHT01_DIFFUSE, LIGHT01_AMBIENT, LIGHT01_DIRECTON);
	SetLight(2, D3DLIGHT_DIRECTIONAL, LIGHT02_DIFFUSE, LIGHT02_AMBIENT, LIGHT02_DIRECTON);
	SetLight(3, D3DLIGHT_DIRECTIONAL, LIGHT03_DIFFUSE, LIGHT03_AMBIENT, LIGHT03_DIRECTON);

	// ライティングモードをON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ライトを設定する
//=============================================================================
void SetLight(int no, _D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXCOLOR ambient, D3DXVECTOR3 dir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体をでクリアする
	ZeroMemory(&g_aLight[no], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[no].Type = type;

	// ライトの拡散光の設定
	g_aLight[no].Diffuse = diffuse;

	// ライトの環境光の設定
	g_aLight[no].Ambient = ambient;

	// ライトの方向の設定
	vecDir = dir;
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[no].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(no, &g_aLight[no]);

	// ライトを使用使用状態に
	pDevice->LightEnable(no, TRUE);

}


//=============================================================================
// 終了処理
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLight(void)
{

}

