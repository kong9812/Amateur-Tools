//=============================================================================
// < Amateur Toolsプログラム >
// 波変換のコントロール処理 [waveControl.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "playerControl.h"
#include "waveControl.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// サウンド読み込み
void LoadMonoData(MONO_DATA *monoData);		// モノデータの読み込み

// 波形出力
void OutputWaveGnuplot(void);				// GNUPLOTの出力(波形)

// 描画処理
void DrawWaveButton(void);					// GNUPLOTの出力ボタン(波形)

// 画面遷移
void SetWaveStage(void);					// 画面遷移
				
//*****************************************************************************
// グローバル変数
//*****************************************************************************
WIN32_FIND_DATA		findGnuplot;			// ファイル情報
MONO_DATA			mono_data;				// モノデータ
char				gnuplotPath[MAX_PATH];	// ファイルのパス
int					gnuplotType;			// 波の種類

TEXTURE				waveButton;			// GNUPLOTの出力ボタン(波形)

float				waveAlpha;			// ボタン色のalpha値

//=============================================================================
// GNUPLOTの読み込み
//=============================================================================
bool OpenGnuplot(HWND hWnd)
{
	OPENFILENAME ofn;

	gnuplotPath[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));		//構造体を0でクリア
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = "C:\\gnuplot\\bin";	// テスト用PCのGNUPLOTパス( なくても大丈夫 @_@ )
	ofn.lpstrFilter = "gnuplot(*.exe)\0*.exe\0\0";
	ofn.lpstrFile = gnuplotPath;
	ofn.nMaxFile = sizeof(gnuplotPath);
	ofn.lpstrDefExt = "exe";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// ファイル名を取り出す
	FindFirstFile(ofn.lpstrFile, &findGnuplot);

	return TRUE;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWaveControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_WAVE,					// ファイルの名前
		&waveButton.texture);			// 読み込むメモリー

	}

	// 色の初期化
	waveButton.col	= NO_SELECT_COLOR;

	// 波の種類 
	gnuplotType = WAVE_NOTHING;

	// 頂点情報の読み込み
	MakeVtxCenterData(waveButton.vertexWk, WAVE_POS, WAVE_SIZE_X, WAVE_SIZE_Y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWaveControl(void)
{
	if (waveButton.texture != NULL)
	{// テクスチャの開放	
		waveButton.texture->Release();
		waveButton.texture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWaveControl(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();
	char lpMsgBuf[CHAR_MAX] = "GNUPLOTのパスが取得できません";	// エラーメッセージ

	// 波形
	if (gnuplotType == WAVE_NOTHING)
	{
		if (CheckHitBB(GetMousePos(hWnd), WAVE_POS, CURSOR_SIZE, D3DXVECTOR2(WAVE_SIZE_X * 2, WAVE_SIZE_Y * 2)))
		{
			waveButton.col = SELECT_COLOR;

			if (IsMouseLeftTriggered() == true)
			{
				gnuplotType = WAVE_WAVE;

				if (!OpenGnuplot(hWnd))
				{
					// エラーメッセージ
					MessageBox(hWnd, (LPCTSTR)lpMsgBuf, _TEXT("エラー"), MB_OK | MB_ICONINFORMATION);

					// 無限ループにならないように
					gnuplotType = WAVE_NOTHING;
				}

				// 一時停止
				StopSound(song->soundBuffer);

				// 出力
				OutputWaveGnuplot();

				// 無限ループにならないように
				gnuplotType = WAVE_NOTHING;
			}
		}

		else
		{
			waveButton.col = NO_SELECT_COLOR;
		}
	}

	// 画面遷移
	SetWaveStage();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWaveControl(void)
{
	DrawWaveButton();	// 波形
}

//=============================================================================
// 描画処理(GNUPLOTの出力ボタン----波形)
//=============================================================================
void DrawWaveButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, waveButton.texture);

	// 反射光の設定(全頂点)
	SetAllDiffuseData(waveButton.vertexWk, waveButton.col);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &waveButton.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// モノデータの読み込み
//=============================================================================
void LoadMonoData(MONO_DATA *monoData)
{
	FILE  *soundFile;				// ファイル読み込み用
	char  riffID[4];				// RIFFヘッダ
	long  riffSize;					// RIFF以降のファイルサイズ
	char  riffType[4];				// RIFFの種類(WAVEヘッダ)
	char  fmtID[4];					// フォーマットの定義
	long  fmtSize;					// fmt チャンクのバイト数
	short fmtFormatID;				// フォーマットID
	short fmtChannel;				// チャンネル数
	long  fmtSamplesPerSec;			// サンプリングレート(Hz)
	long  fmtBytesPerSec;			// データ速度 (Byte/sec)
	short fmtBlockSize;				// ブロックサイズ (Byte/sample×チャンネル数)
	short fmtBitsPerSample;			// サンプルあたりのビット数 (bit/sample)	
	char  dataID[4];				// data チャンク 	
	long  dataSize;					// 波形データのバイト数
	short soundData;				// 音のデータ

	// ファイルの読み込み
	soundFile = fopen(GetSoundPath(), "rb");
	fread(riffID, 1, 4, soundFile);
	fread(&riffSize, 4, 1, soundFile);
	fread(riffType, 1, 4, soundFile);
	fread(fmtID, 1, 4, soundFile);
	fread(&fmtSize, 4, 1, soundFile);
	fread(&fmtFormatID, 2, 1, soundFile);
	fread(&fmtChannel, 2, 1, soundFile);
	fread(&fmtSamplesPerSec, 4, 1, soundFile);
	fread(&fmtBytesPerSec, 4, 1, soundFile);
	fread(&fmtBlockSize, 2, 1, soundFile);
	fread(&fmtBitsPerSample, 2, 1, soundFile);
	fread(dataID, 1, 4, soundFile);
	fread(&dataSize, 4, 1, soundFile);

	monoData->sf			= fmtSamplesPerSec;
	monoData->precision		= fmtBitsPerSample;
	monoData->length		= dataSize / HALF;
	monoData->soundData		= (double *)calloc(monoData->length, sizeof(double));

	// データを取得
	for (int i = 0; i < monoData->length; i++)
	{
		fread(&soundData, 2, 1, soundFile);
		monoData->soundData[i] = (double)soundData / WAVE_16_BIT_MAX;
	}

	// ファイルを閉じる
	fclose(soundFile);
}

//=============================================================================
// 波形 (GNUPLOT)
// 縦軸:音圧(? 振幅(? 電圧(? 音の大きさ(? 
// 横軸:時間(バイト)
//=============================================================================
void OutputWaveGnuplot(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE *gnuplot;				// GNUPLOT
	double max;					// 最大値
	double min;					// 最小値
	double x, y;				// GNUPLOT中の座標
	char savePath[MAX_PATH];	// PNGを保存する場所

	// パスとコマンドを結合
	strcat(gnuplotPath, GNUPLOT_PRESIST);

	// セーブパスと初期パスを結合
	strcpy(savePath, GetOldPath());
	
	// セーブパスとセーブフォルダパスを結合
	strcat(savePath, SAVE_PATH);

	// モノデータの読み込み
	LoadMonoData(&mono_data);

	// 最大値と最小値
	min = max = mono_data.soundData[0];
	for (int i = 0; i < mono_data.length; i++)
	{
		if (mono_data.soundData[i] < min) min = mono_data.soundData[i];
		if (mono_data.soundData[i] > max) max = mono_data.soundData[i];
	}

	// グラフ
	gnuplot = _popen(gnuplotPath, "w");										// GNUPLOTを書き込みモードで開く
	fprintf(gnuplot, "set title \"wave \" \n");								// タイトルの設定
	fprintf(gnuplot, "set xrange [0:%d]\n", mono_data.length);				// xの範囲
	fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// yの範囲
	fprintf(gnuplot, "set terminal png\n");									// 画像出力の準備
	fprintf(gnuplot, "set term png size 1000,500\n");						// 画像のサイズ
	fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// プロット

	for (int i = 0; i < mono_data.length; i++)
	{
		x = i;
		y = mono_data.soundData[i];
		fprintf(gnuplot, "%f\t%f\n", x, y);
	}
	fprintf(gnuplot, "e\n");

	fprintf(gnuplot, "set output '%s\\\\Wave.png'\n", savePath);	
	fprintf(gnuplot, "replot '%s\\\\Data.txt'using 1:2 w l title 'OutputData' lw 2\n", savePath); 	// テキストデータのプロット	
	fprintf(gnuplot, "set output\n");

	// GNUPLOTの画面を閉じる
	_pclose(gnuplot);

	// 解放
	free(mono_data.soundData);

	// セーブパスとファイル名を結合
	strcat(savePath, "\\Wave.png");

	// テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
	savePath,							// ファイルの名前
	&waveButton.texture);				// 読み込むメモリー

}

//=============================================================================
// 画面遷移
//=============================================================================
void SetWaveStage(void)
{
	// プレイヤー
	if (GetKeyboardTrigger(DIK_1))
	{
		SetStage(STAGE_PLAYER);
	}

	// 3D
	else if (GetKeyboardTrigger(DIK_3))
	{
		SetStage(STAGE_3D);
	}
}
