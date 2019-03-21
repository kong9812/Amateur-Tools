//=============================================================================
// < Amateur Toolsプログラム >
// メッシュ地面の処理 [meshfield.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/3D/woodField.jpg"		// 読み込むテクスチャファイル名

#define FIELD_MAX	(4)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pD3DTextureField;			// テクスチャ読み込み場所

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9 g_pD3DIdxBuffField;		// インデックスバッファインターフェースへのポインタ

	D3DXMATRIX g_mtxWorldField;						// ワールドマトリックス
	D3DXVECTOR3 g_posField;							// ポリゴン表示位置の中心座標
	D3DXVECTOR3 g_rotField;							// ポリゴンの回転角
	int g_nNumBlockXField, g_nNumBlockZField;		// ブロック数
	int g_nNumVertexField;							// 総頂点数	
	int g_nNumVertexIndexField;						// 総インデックス数
	int g_nNumPolygonField;							// 総ポリゴン数
	float g_fBlockSizeXField, g_fBlockSizeZField;	// ブロックサイズ

} MESH_FIELD;

MESH_FIELD fieldWk[FIELD_MAX];
int g_nNumMeshField = 0;								// メッシュ地面の数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
							int nNumBlockX, int nNumBlockZ, float fBlockSizeX, float fBlockSizeZ)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESH_FIELD *pMesh;

	if (g_nNumMeshField >= FIELD_MAX)
	{
		return E_FAIL;
	}

	// ポインター初期化
	pMesh = &fieldWk[g_nNumMeshField];
	g_nNumMeshField++;

	// ポリゴン表示位置の中心座標を設定
	pMesh->g_posField = pos;

	pMesh->g_rotField = rot;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTextureField);	// 読み込むメモリー

	// ブロック数の設定
	pMesh->g_nNumBlockXField = nNumBlockX;
	pMesh->g_nNumBlockZField = nNumBlockZ;

	// 頂点数の設定
	pMesh->g_nNumVertexField = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数の設定
	pMesh->g_nNumVertexIndexField = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// ポリゴン数の設定
	pMesh->g_nNumPolygonField = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;

	// ブロックサイズの設定
	pMesh->g_fBlockSizeXField = fBlockSizeX;
	pMesh->g_fBlockSizeZField = fBlockSizeZ;

	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * pMesh->g_nNumVertexField,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												FVF_VERTEX_3D,						// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&pMesh->g_pD3DVtxBuffField,			// 頂点バッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
    if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * pMesh->g_nNumVertexIndexField,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												D3DFMT_INDEX16,						// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&pMesh->g_pD3DIdxBuffField,				// インデックスバッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
#if 0
		const float texSizeX = 1.0f / g_nNumBlockX;
		const float texSizeZ = 1.0f / g_nNumBlockZ;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pMesh->g_pD3DVtxBuffField->Lock( 0, 0, (void**)&pVtx, 0 );

		for(int nCntVtxZ = 0; nCntVtxZ < (pMesh->g_nNumBlockZField + 1); nCntVtxZ++)
		{
			for(int nCntVtxX = 0; nCntVtxX < (pMesh->g_nNumBlockXField + 1); nCntVtxX++)
			{

				// 頂点座標の設定
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.x = -(pMesh->g_nNumBlockXField / 2.0f) * pMesh->g_fBlockSizeXField + nCntVtxX * pMesh->g_fBlockSizeXField;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.y = 0 /*rand() % 100*/;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.z = (pMesh->g_nNumBlockZField / 2.0f) * pMesh->g_fBlockSizeZField - nCntVtxZ * pMesh->g_fBlockSizeZField;

				// 法線の設定
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				if (g_nNumMeshField >= 2)
				{
					// 反射光の設定
					pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
				}

				else
				{
					// 反射光の設定
					pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				// テクスチャ座標の設定
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
			}
		}

		// 頂点データをアンロックする
		pMesh->g_pD3DVtxBuffField->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		pMesh->g_pD3DIdxBuffField->Lock( 0, 0, (void**)&pIdx, 0 );

		int nCntIdx = 0;
		for(int nCntVtxZ = 0; nCntVtxZ < pMesh->g_nNumBlockZField; nCntVtxZ++)
		{
			if(nCntVtxZ > 0)
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = (nCntVtxZ + 1) * (pMesh->g_nNumBlockXField + 1);
				nCntIdx++;
			}

			for(int nCntVtxX = 0; nCntVtxX < (pMesh->g_nNumBlockXField + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (nCntVtxZ + 1) * (pMesh->g_nNumBlockXField + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX;
				nCntIdx++;
			}

			if(nCntVtxZ < (pMesh->g_nNumBlockZField - 1))
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + pMesh->g_nNumBlockXField;
				nCntIdx++;
			}
		}

		// インデックスデータをアンロックする
		pMesh->g_pD3DIdxBuffField->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	MESH_FIELD *pMesh;

	for (int nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &fieldWk[g_nNumMeshField];

		if (pMesh->g_pD3DVtxBuffField)
		{// 頂点バッファの開放
			pMesh->g_pD3DVtxBuffField->Release();
			pMesh->g_pD3DVtxBuffField = NULL;
		}

		if (pMesh->g_pD3DIdxBuffField)
		{// インデックスバッファの開放
			pMesh->g_pD3DIdxBuffField->Release();
			pMesh->g_pD3DIdxBuffField = NULL;
		}
	}

	if(g_pD3DTextureField)
	{// テクスチャの開放
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;
	MESH_FIELD *pMesh;

	for (int nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &fieldWk[nCntMeshField];

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&pMesh->g_mtxWorldField);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pMesh->g_rotField.y, pMesh->g_rotField.x, pMesh->g_rotField.z);
		D3DXMatrixMultiply(&pMesh->g_mtxWorldField, &pMesh->g_mtxWorldField, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pMesh->g_posField.x, pMesh->g_posField.y, pMesh->g_posField.z);
		D3DXMatrixMultiply(&pMesh->g_mtxWorldField, &pMesh->g_mtxWorldField, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pMesh->g_mtxWorldField);

		// 頂点バッファをレンダリングパイプラインに設定
		pDevice->SetStreamSource(0, pMesh->g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// インデックスバッファをレンダリングパイプラインに設定
		pDevice->SetIndices(pMesh->g_pD3DIdxBuffField);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureField);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pMesh->g_nNumVertexField, 0, pMesh->g_nNumPolygonField);
	}
}
