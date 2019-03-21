//=============================================================================
// < Amateur Toolsプログラム >
// サウンド処理 [sound.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "monoSpeaker.h"
#include "soundEffect.h"
#include "sound.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//=============================================================================
// グローバル変数
//=============================================================================
IDirectSound8	*g_pDirectSound = NULL;		// サウンドインターフェース
LONG			g_fvolume = 0l;				// 初期音量	
DWORD			dwResults;					// エフェクトのインデックス
DWORD			g_soundSize = 0;			// サイズ(Byte)
char            soundPath[MAX_PATH];		// ファイルのパス
int				initFrequency = 0;			// 初期周波数
WIN32_FIND_DATA	findSound;					// ファイル情報
WORD			soundChannel;				// 音源種類
char			oldPath[MAX_PATH];			// 初期パス

LPDIRECTSOUND3DBUFFER8		p3DBuffer = NULL;	// 3Dサウンドバッファ
LPDIRECTSOUND3DLISTENER8	pLisBuffer = NULL;	// リスナーバッファ

//=============================================================================
// サウンドの初期化
// hWnd:ウィンドウハンドル
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	// DirectSoundオブジェクトの作成
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// 協調レベル設定 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	// 音源種類の初期化
	soundChannel = SOUND_UNKNOWN;

	return S_OK;
}

//=============================================================================
// サウンドの読み込み
//=============================================================================
bool OpenSound(HWND hWnd)
{
	OPENFILENAME ofn;

	// カレントディレクトリを取り出す
	GetCurrentDirectory(MAX_PATH, oldPath);

	soundPath[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));  //構造体を0でクリア
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = oldPath;
	ofn.lpstrFilter = "sound file(*.wav)\0*.wav\0\0";
	ofn.lpstrFile = soundPath;
	ofn.nMaxFile = sizeof(soundPath);
	ofn.lpstrDefExt = "wav";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// ファイル名を取り出す
	FindFirstFile(ofn.lpstrFile, &findSound);

	// カレントディレクトリを設定する
	SetCurrentDirectory(oldPath);

	return TRUE;
}

//=============================================================================
// 後片付け
//=============================================================================
void UninitSound(void)
{
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}

}

//=============================================================================
// サウンドのロード
// no:サウンドナンバー（ヘッダに定義された列挙型定数）
//=============================================================================
LPDIRECTSOUNDBUFFER8 LoadSound(int type)
{
	// MMIO = マルチメディア入出力、の略。
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// 曲データの総合バッファ
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// 曲データのバッファ
	LPDIRECTSOUNDBUFFER  pPrimary = NULL;	// プライマリバッファ
	DSBUFFERDESC buff;						// バッファ設定構造体
	WAVEFORMATEX pcm;						// 曲データフォーマット構造体

	HMMIO hMmio = NULL;						// MMIOハンドル
	MMIOINFO mmioInfo;						// マルチメディアデータ構造体

	MMRESULT mmRes;								// MM処理結果格納変数
	MMCKINFO riffChunk, formatChunk, dataChunk;	// チャンクデータ構造体
	DWORD size;									// データサイズ格納用

	LPVOID pBlock;							// セカンダリバッファのデータ書き込み先アドレス
	DWORD  dwSize;							// セカンダリバッファのサイズ

	// 1.ハンドルをもとにファイルを開く
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)soundPath, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.ファイル解析① RIFFチャンク検索
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// 検索キーワード
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// キーワードをもとに検索
	
	if(mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.ファイル解析② フォーマットチャンク検索
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// 検索キーワード
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索

	if(mmRes != MMSYSERR_NOERROR)		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// 検索情報をもとに読み込み
	
	// 初期周波数のバックアップを取る
	initFrequency = (int)pcm.nSamplesPerSec;

	if(size != formatChunk.cksize) 		// 正しく読み込めなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.ファイル解析③ データチャンク検索
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// 検索キーワード
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// キーワードをもとに検索
	
	if(mmRes != MMSYSERR_NOERROR) 		// 見つからなかったら異常終了
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.データ読み込み
	char *pData = new char[dataChunk.cksize];					// 必要な大きさの領域を確保して
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// データを読み込む
	
	if(size != dataChunk.cksize)  		// 正しく読み込めなかったら異常終了
	{
		delete[] pData;
		return NULL;
	}

	// 2Dサウンド
	if (type == SOUND_2D)
	{
		// 6.曲を読み込む「セカンダリバッファ」を用意
		ZeroMemory(&buff, sizeof(DSBUFFERDESC));	// まず初期化
		buff.dwSize = sizeof(DSBUFFERDESC);			// そこから各種設定
		buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
			DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFX;
		buff.dwBufferBytes = size;

		soundChannel = pcm.nChannels;

		g_soundSize = size;

		buff.lpwfxFormat = &pcm;

		// 総合バッファを作る
		if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
			return NULL;

		// サウンドバッファを取り出す
		if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
			return NULL;
	}

	// 3Dサウンド
	else if (type == SOUND_3D)
	{
		MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

		// 6.曲を読み込む「セカンダリバッファ」を用意
		ZeroMemory(&buff, sizeof(DSBUFFERDESC));	// まず初期化
		buff.dwSize = sizeof(DSBUFFERDESC);			// そこから各種設定
		buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
			DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRL3D | DSBCAPS_CTRLFX;
		buff.dwBufferBytes = size;
		g_soundSize = size;
		buff.guid3DAlgorithm = DS3DALG_HRTF_FULL;
		buff.lpwfxFormat = &pcm;

		// 総合バッファを作る
		if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
			return NULL;

		// サウンドバッファを取り出す
		if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
			return NULL;

		// 3Dバッファを取り出す
		if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&p3DBuffer)))
			return NULL;

		//最小距離と最大距離の設定
		p3DBuffer->SetPosition(monoSpeaker->pos.x, monoSpeaker->pos.y, monoSpeaker->pos.z, DS3D_IMMEDIATE);
		p3DBuffer->SetMinDistance(150, DS3D_IMMEDIATE);
		p3DBuffer->SetMaxDistance(300, DS3D_IMMEDIATE);
		p3DBuffer->SetConeAngles(360, 360, DS3D_IMMEDIATE);
		p3DBuffer->SetConeOrientation(0, 1, -1, DS3D_IMMEDIATE);
		p3DBuffer->SetConeOutsideVolume(-1000, DS3D_IMMEDIATE);
		
		//リスナーインターフェイスを取得する  
		ZeroMemory(&buff, sizeof(DSBUFFERDESC));
		buff.dwSize = sizeof(DSBUFFERDESC);
		buff.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

		// プライマリバッファを作る
		if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pPrimary, NULL)))
			return NULL;

		// サウンドバッファを取り出す
		if (FAILED(pPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&pLisBuffer)))
			return NULL;

		// ロールオフ係数(距離によって生じる音の減衰は現実の2倍)
		pLisBuffer->SetRolloffFactor(2.0f, DS3D_IMMEDIATE);

		// 取り出したらバッファを捨てる
		pPrimary->Release();
	}

	// 取り出したら総合バッファを捨てる
	pBaseBuffer->Release();

	// 7.作られたセカンダリバッファにデータを転送
	// まずは書き込みできるようバッファをロック
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// データ転送
	delete[] pData;					// 元の読み込み領域を消す

	// バッファロック解除
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// 再生位置を0に戻す
	pBuffer->SetCurrentPosition(0);

	// セカンダリバッファを返してようやく完了...
	return pBuffer;
}

//=============================================================================
// 音を鳴らす
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
// flag   :1(E_DS8_FLAG_LOOP)ならループ再生
//=============================================================================
void PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag/*=0*/)
{
	if (pBuffer != NULL)
	{
		// 続きから鳴らすので、最初から鳴らしたい場合はSetCurrentPosition(0)をすること
		pBuffer->Play(0, 0, flag);
	}
}

//=============================================================================
// 音を止める
//=============================================================================
void PauseSound( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	if (pBuffer != NULL)
	{
		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)	// 鳴っていたら
		{
			pBuffer->Stop();				// 意味的にはPauseになる。
		}
	}
}

//=============================================================================
// 音を停止
//=============================================================================
void StopSound(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;

	if (pBuffer != NULL)
	{
		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)	// 鳴っていたら
		{
			pBuffer->Stop();
		}
		pBuffer->SetCurrentPosition(0);
	}

}

//=============================================================================
// 再生中かどうか調べる
// pBuffer:音を鳴らしたいサウンドデータのセカンダリバッファ
//=============================================================================
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	if (pBuffer != NULL)
	{
		DWORD status;

		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// 相対音量を取得
//=============================================================================
LONG GetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	LONG db = 0l;

	if (pBuffer != NULL)
	{
		pBuffer->GetPan((LPLONG)db);
	}
	return db;
}

//=============================================================================
// 相対音量を設定
//=============================================================================
void SetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer,LONG db)
{
	if (pBuffer != NULL)
	{
		pBuffer->SetPan(db);
	}
}

//=============================================================================
// 音量取得
//=============================================================================
int GetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	return (int)g_fvolume;
}

//=============================================================================
// 音量調整
//=============================================================================
void SetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer,int type)
{
	if (pBuffer != NULL)
	{
		if (type == VOLUME_UP)
		{
			g_fvolume += 100l;
			if (g_fvolume > DSBVOLUME_MAX)
			{
				g_fvolume = DSBVOLUME_MAX;
			}
		}

		else if (type == VOLUME_DOWN)
		{
			g_fvolume -= 100l;

			if (g_fvolume < DSBVOLUME_MIN)
			{
				g_fvolume = DSBVOLUME_MIN;
			}
		}

		else if (type == VOLUME_MULT)
		{
			g_fvolume = DSBVOLUME_MIN;
		}

		pBuffer->SetVolume(g_fvolume);
	}
}

//=============================================================================
// エフェクト
//=============================================================================
void SetSoundEffect(LPDIRECTSOUNDBUFFER8 pBuffer, int flag, int effectNo)
{
	DWORD status;

	if (pBuffer != NULL)
	{
		pBuffer->GetStatus(&status);

		if (status & DSBSTATUS_PLAYING)
		{
			pBuffer->Stop();

			// エフェクトを記述
			DSEFFECTDESC dsEffect;

			// エフェクトの初期化(削除)
			pBuffer->SetFX(NULL, NULL, NULL);

			// エフェクトの変更処理
			if (effectNo != NULL_SOUND_EFFECT)
			{
				memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
				dsEffect.dwSize = sizeof(DSEFFECTDESC);
				dsEffect.dwFlags = 0;
				dsEffect.guidDSFXClass = GetSoundEffectID(effectNo);

				// エフェクトを設定
				pBuffer->SetFX(1, &dsEffect, &dwResults);

				switch (dwResults)
				{
				case DSFXR_LOCHARDWARE:
					OutputDebugString("Effect was placed in hardware.");
					break;
				case DSFXR_LOCSOFTWARE:
					OutputDebugString("Effect was placed in software.");
					break;
				case DSFXR_UNALLOCATED:
					OutputDebugString("Effect is not yet allocated to hardware or software.");
					break;
				}
			}

			pBuffer->Play(0, 0, flag);

		}
	}
}

//=============================================================================
// 再生カーソルと書き込みカーソルの位置を取得
//=============================================================================
DWORD GetSoundCurrentPosition(LPDIRECTSOUNDBUFFER8 pBuffer, int type)
{
	DWORD PlayCursor = 0;
	DWORD WriteCursor = 0;
	DWORD ReturnCusor = 0;

	if (pBuffer != NULL)
	{
		pBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor);

		if (type == GET_PLAY)
		{
			ReturnCusor = PlayCursor;
		}

		else if (type == GET_WRITE)
		{
			ReturnCusor = WriteCursor;
		}
	}

	return ReturnCusor;
}

//=============================================================================
// 再生位置の設定(前進・後退)
//=============================================================================
void SetSoundPosition(LPDIRECTSOUNDBUFFER8 pBuffer, int type, int flag, long distance)
{
	DWORD status;
	DWORD PlayCursor = 0;
	DWORD WriteCursor = 0;
	bool play = false;

	if (pBuffer != NULL)
	{
		// 再生状態と再生位置を取得する
		{
			pBuffer->GetStatus(&status);
			if (status & DSBSTATUS_PLAYING)
			{
				pBuffer->Stop();
				play = true;
			}
			pBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor);
		}

		// 前進
		if (type == SET_FORWARD)
		{
			PlayCursor += POS_UNIT;
		}

		// 後退
		else if (type == SET_REWIND)
		{
			PlayCursor -= POS_UNIT;
		}

		else if (type = SET_DISTANCE)
		{
			PlayCursor = distance;
		}

		// オーバフロー防止
		if (PlayCursor > g_soundSize)
		{
			PlayCursor = g_soundSize;
		}

		// 位置設定
		pBuffer->SetCurrentPosition(PlayCursor);

		if (play == true)
		{
			pBuffer->Play(0, 0, flag);
		}
	}
}

//=============================================================================
// リスナーの位置を設定
//=============================================================================
void SetListenerPos(D3DXVECTOR3 pos)
{
	pLisBuffer->SetPosition(pos.x, pos.y, pos.z, DS3D_IMMEDIATE);
}

//=============================================================================
// リスナーの向きを設定
//=============================================================================
void SetListenerRot(D3DXVECTOR3 pos)
{
	pLisBuffer->SetOrientation(pos.x, pos.y, pos.z, 0, 1, 0, DS3D_IMMEDIATE);
}

//=============================================================================
// 周波数を設定
//=============================================================================
void SetSoundFrequency(LPDIRECTSOUNDBUFFER8 pBuffer,int freq)
{
	if (pBuffer != NULL)
	{
		pBuffer->SetFrequency((DWORD)freq);
	}
}

//=============================================================================
// サイズを取得
//=============================================================================
DWORD GetSoundSize(void)
{
	return g_soundSize;
}

//=============================================================================
// 音のパスを取得
//=============================================================================
char *GetSoundPath(void)
{
	return soundPath;
}

//=============================================================================
// ファイル名を取得
//=============================================================================
char *GetSoundName(int no)
{
	return &findSound.cFileName[no];
}

//=============================================================================
// 初期周波数を取得
//=============================================================================
int GetSoundInitFrequency(void)
{
	return initFrequency;
}

//=============================================================================
// 初期パスを取得
//=============================================================================
char *GetOldPath(void)
{
	return oldPath;
}
