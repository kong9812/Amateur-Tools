//=============================================================================
// < SoundPlayerプログラム >
// モノラルスピーカーの処理 [monoSpeaker.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _MONO_SPEAKER_H_
#define _MONO_SPEAKER_H_

#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// モノラルスピーカー
#define	MONO_SPEAKER_MODEL		"data/MODEL/monoSpeaker/monoSpeaker.x"	// 読み込むモデル名
#define MONO_SPEAKER_POS		D3DXVECTOR3(0.0f, 0.0f, 100.0f)			// 座標
#define MONO_SPEAKER_ROT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// 回転
#define MONO_SPEAKER_SCL		D3DXVECTOR3(1.0f, 1.0f, 1.0f)			// スケール
#define MONO_SPEAKER_SIZE		(10)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// モノラルスピーカー構造体
{
	LPDIRECTSOUNDBUFFER8	soundBuffer;	// サウンドバッファ
	D3DXVECTOR3				pos;			// モデルの位置
	D3DXVECTOR3				rot;			// モデルの向き(回転)
	D3DXVECTOR3				scl;			// モデルの大きさ(スケール)

	int						reverb;			// 環境リバーブ

}MONO_SPEAKER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMonoSpeaker(int initType);
void UninitMonoSpeaker(void);
void UpdateMonoSpeaker(void);
void DrawMonoSpeaker(void);

MONO_SPEAKER *GetMonoSpeaker(void);

#endif 