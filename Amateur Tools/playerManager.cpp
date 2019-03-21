//=============================================================================
// < Amateur Toolsプログラム >
// プレイヤーのマネージャー処理 [playerManager.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "soundEffect.h"
#include "frequencyControl.h"
#include "playerControl.h"
#include "playerButton.h"
#include "effectControl.h"
#include "playerBackground.h"
#include "playerManager.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//------------描画処理
void DrawPlayerDebugFont(HWND hWnd);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
#ifdef _DEBUG
LPD3DXFONT				g_pD3DXPlayerDebugFont = NULL;			// フォントへのポインタ
#endif

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitPlayerManager(int InitType)
{
	// プレイヤーの背景
	InitPlayerBackground(InitType);

	// プレイヤーのコントロール
	InitPlayerControl(InitType);

	// プレイヤーのボタン
	InitPlayerButton(InitType);

	// エフェクトのコントロール
	InitEffectControl(InitType);

	// 周波数のコントロール
	InitFrequencyControl(InitType);

#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(GetDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXPlayerDebugFont);
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerManager(void)
{
	// プレイヤーの背景
	UninitPlayerBackground();

	// プレイヤーのコントロール
	UninitPlayerControl();

	// プレイヤーのボタン
	UninitPlayerButton();

	// エフェクトのコントロール
	UninitEffectControl();

	// 周波数のコントロール
	UninitFrequencyControl();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerManager(HWND hWnd)
{
	// プレイヤーの背景
	UpdatePlayerBackground();
	
	// プレイヤーのコントロール
	UpdatePlayerControl(hWnd);
	
	// プレイヤーのボタン
	UpdatePlayerButton(hWnd);
	
	// エフェクトのコントロール
	UpdateEffectControl(hWnd);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerManager(HWND hWnd)
{
	// プレイヤーの背景
	DrawPlayerBackground();
	
	// プレイヤーのコントロール
	DrawPlayerControl();
	
	// プレイヤーのボタン
	DrawPlayerButton();
	
	// エフェクトのコントロール
	DrawEffectControl();

	// 周波数のコントロール
	DrawFrequencyControl();

#ifdef _DEBUG
	// デバッグ表示
	DrawPlayerDebugFont(hWnd);
#endif
}

#ifdef _DEBUG
//=============================================================================
// デバッグ表示処理
//=============================================================================
void DrawPlayerDebugFont(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[CHAR_MAX];

	// sound effect
	rect.top = 20;				// 初期の高さ(FPSの下)
	switch (song->effectNo)
	{
	case NULL_SOUND_EFFECT:
		sprintf(str, _T("NULL エフェクトなし"));
		break;
	case WATER_SOUND_EFFECT:
		sprintf(str, _T("GARGLE ガーグル"));
		break;
	case CHORUS_SOUND_EFFECT:
		sprintf(str, _T("CHORUS コーラス"));
		break;
	case FLANGER_SOUND_EFFECT:
		sprintf(str, _T("FLANGER フランジ"));
		break;
	case ECHO_SOUND_EFFECT:
		sprintf(str, _T("ECHO エコー"));
		break;
	case DISTORTION_SOUND_EFFECT:
		sprintf(str, _T("DISTORTION ディストーション"));
		break;
	case COMPRESSOR_SOUND_EFFECT:
		sprintf(str, _T("COMPRESSOR コンプレッサー"));
		break;
	case PARAMEQ_SOUND_EFFECT:
		sprintf(str, _T("PARAMEQ パラメトリック イコライザー"));
		break;
	case I3DL2REVERB_SOUND_EFFECT:
		sprintf(str, _T("I3DL2REVERB 環境リバーブ"));
		break;
	case WAVES_REVERB_SOUND_EFFECT:
		sprintf(str, _T("WAVES_REVERB Wave 残響"));
		break;
	default:
		break;
	}
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0xff, 0xff));

	// sound_pos
	rect.top += 20;
	sprintf(str, _T("pos:%f%%"), song->playPos);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// frequency
	rect.top += 20;
	sprintf(str, _T("frequency:%d"), song->frequency);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// db
	rect.top += 20;
	sprintf(str, _T("db:%ld"), song->balanceVolume);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// 曲名
	rect.top += 20;
	sprintf(str, _T("name:%s"), GetSoundPath());
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// マウス座標
	rect.top += 20;
	sprintf(str, _T("mousePos:%f,%f"), (float)GetMousePos(hWnd).x, (float)GetMousePos(hWnd).y);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// マウスPress座標
	rect.top += 20;
	sprintf(str, _T("mousePressPos:%f"), (float)GetMouseX());
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// GetCurrentPosition-------write
	rect.top += 20;
	sprintf(str, _T("write:%f"), (float)GetSoundCurrentPosition(song->soundBuffer, GET_WRITE));
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
