//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=============================================================================
// マクロ定義
//=============================================================================
// チュートリアル画面
#define	TEXTURE_TUTORIAL_SCREEN		_T("data/TEXTURE/tutorialScreen.jpg")	// 読み込むテクスチャファイル名


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorial(int InitType);	// 初期化処理
void UninitTutorial(void);			// 終了処理
void UpdateTutorial(void);			// 更新処理
void DrawTutorial(void);			// 描画処理

#endif