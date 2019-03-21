//=============================================================================
// < Amateur Tools�v���O���� >
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/3D/woodField.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define FIELD_MAX	(4)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pD3DTextureField;			// �e�N�X�`���ǂݍ��ݏꏊ

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 g_pD3DIdxBuffField;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX g_mtxWorldField;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 g_posField;							// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 g_rotField;							// �|���S���̉�]�p
	int g_nNumBlockXField, g_nNumBlockZField;		// �u���b�N��
	int g_nNumVertexField;							// �����_��	
	int g_nNumVertexIndexField;						// ���C���f�b�N�X��
	int g_nNumPolygonField;							// ���|���S����
	float g_fBlockSizeXField, g_fBlockSizeZField;	// �u���b�N�T�C�Y

} MESH_FIELD;

MESH_FIELD fieldWk[FIELD_MAX];
int g_nNumMeshField = 0;								// ���b�V���n�ʂ̐�

//=============================================================================
// ����������
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

	// �|�C���^�[������
	pMesh = &fieldWk[g_nNumMeshField];
	g_nNumMeshField++;

	// �|���S���\���ʒu�̒��S���W��ݒ�
	pMesh->g_posField = pos;

	pMesh->g_rotField = rot;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&g_pD3DTextureField);	// �ǂݍ��ރ������[

	// �u���b�N���̐ݒ�
	pMesh->g_nNumBlockXField = nNumBlockX;
	pMesh->g_nNumBlockZField = nNumBlockZ;

	// ���_���̐ݒ�
	pMesh->g_nNumVertexField = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// �C���f�b�N�X���̐ݒ�
	pMesh->g_nNumVertexIndexField = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// �|���S�����̐ݒ�
	pMesh->g_nNumPolygonField = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;

	// �u���b�N�T�C�Y�̐ݒ�
	pMesh->g_fBlockSizeXField = fBlockSizeX;
	pMesh->g_fBlockSizeZField = fBlockSizeZ;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * pMesh->g_nNumVertexField,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&pMesh->g_pD3DVtxBuffField,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * pMesh->g_nNumVertexIndexField,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
												D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&pMesh->g_pD3DIdxBuffField,				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
#if 0
		const float texSizeX = 1.0f / g_nNumBlockX;
		const float texSizeZ = 1.0f / g_nNumBlockZ;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pMesh->g_pD3DVtxBuffField->Lock( 0, 0, (void**)&pVtx, 0 );

		for(int nCntVtxZ = 0; nCntVtxZ < (pMesh->g_nNumBlockZField + 1); nCntVtxZ++)
		{
			for(int nCntVtxX = 0; nCntVtxX < (pMesh->g_nNumBlockXField + 1); nCntVtxX++)
			{

				// ���_���W�̐ݒ�
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.x = -(pMesh->g_nNumBlockXField / 2.0f) * pMesh->g_fBlockSizeXField + nCntVtxX * pMesh->g_fBlockSizeXField;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.y = 0 /*rand() % 100*/;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].vtx.z = (pMesh->g_nNumBlockZField / 2.0f) * pMesh->g_fBlockSizeZField - nCntVtxZ * pMesh->g_fBlockSizeZField;

				// �@���̐ݒ�
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				if (g_nNumMeshField >= 2)
				{
					// ���ˌ��̐ݒ�
					pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
				}

				else
				{
					// ���ˌ��̐ݒ�
					pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}

				// �e�N�X�`�����W�̐ݒ�
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
				pVtx[nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pMesh->g_pD3DVtxBuffField->Unlock();
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pMesh->g_pD3DIdxBuffField->Lock( 0, 0, (void**)&pIdx, 0 );

		int nCntIdx = 0;
		for(int nCntVtxZ = 0; nCntVtxZ < pMesh->g_nNumBlockZField; nCntVtxZ++)
		{
			if(nCntVtxZ > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
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
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				pIdx[nCntIdx] = nCntVtxZ * (pMesh->g_nNumBlockXField + 1) + pMesh->g_nNumBlockXField;
				nCntIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		pMesh->g_pD3DIdxBuffField->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	MESH_FIELD *pMesh;

	for (int nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &fieldWk[g_nNumMeshField];

		if (pMesh->g_pD3DVtxBuffField)
		{// ���_�o�b�t�@�̊J��
			pMesh->g_pD3DVtxBuffField->Release();
			pMesh->g_pD3DVtxBuffField = NULL;
		}

		if (pMesh->g_pD3DIdxBuffField)
		{// �C���f�b�N�X�o�b�t�@�̊J��
			pMesh->g_pD3DIdxBuffField->Release();
			pMesh->g_pD3DIdxBuffField = NULL;
		}
	}

	if(g_pD3DTextureField)
	{// �e�N�X�`���̊J��
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;
	MESH_FIELD *pMesh;

	for (int nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &fieldWk[nCntMeshField];

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pMesh->g_mtxWorldField);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pMesh->g_rotField.y, pMesh->g_rotField.x, pMesh->g_rotField.z);
		D3DXMatrixMultiply(&pMesh->g_mtxWorldField, &pMesh->g_mtxWorldField, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pMesh->g_posField.x, pMesh->g_posField.y, pMesh->g_posField.z);
		D3DXMatrixMultiply(&pMesh->g_mtxWorldField, &pMesh->g_mtxWorldField, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pMesh->g_mtxWorldField);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, pMesh->g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetIndices(pMesh->g_pD3DIdxBuffField);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureField);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pMesh->g_nNumVertexField, 0, pMesh->g_nNumPolygonField);
	}
}
