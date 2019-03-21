//=============================================================================
//
// 波変換のコントロール処理 [waveControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _WAVE_CONTROL_H_
#define _WAVE_CONTROL_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 波形
#define TEXTURE_WAVE			_T("data/TEXTURE/waveButton/waveButton.png")	// 読み込むテクスチャファイル名
#define WAVE_POS				D3DXVECTOR3(640.0f, 410.0f, 0.0f)
#define WAVE_SIZE_X				(500.0f)
#define WAVE_SIZE_Y				(150.0f)

// GNUPLOTの残留コマンド
#define GNUPLOT_PRESIST			" -persist"

// 初期パスからセーブフォルダまでのパス
#define SAVE_PATH				"\\data\\GNUPLOT"

// 色
#define SELECT_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,0.5f)
#define NO_SELECT_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
// オーバーフロー防止(16bit符号付きで表現できる範囲)
#define WAVE_16_BIT_MAX			(32768.0)

//*****************************************************************************
// 定数定義
//*****************************************************************************
enum WAVE_TYPE
{	// 波の種類用フラグ
	WAVE_NOTHING,	// 初期状態
	WAVE_WAVE,		// 波
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct			// 音データの分析用構造体(モノ)
{
	int sf;				// Sampling frequency(サンプリング周波数)
	int precision;		// Quantization precision(量子化精度) 単位:bits
	int length;			// 長さ
	double *soundData;	// サウンドデータ
} MONO_DATA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWaveControl(int InitType);	// 初期化処理
void UninitWaveControl(void);			// 終了処理
void UpdateWaveControl(HWND hWnd);		// 更新処理
void DrawWaveControl(void);				// 描画処理



#endif