//=============================================================================
// < Amateur Tools�v���O���� >
// ���m�����X�s�[�J�[�̏��� [monoSpeaker.cpp]
// Author : �� �F��
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
// �v���g�^�C�v�錾
//*****************************************************************************
void Set3DStage(void);			// ��ʑJ��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT			objectMonoSpeaker;	// 3D�I�u�W�F�N�g
MONO_SPEAKER	monoSpeakerWk;		// ���m�����X�s�[�J�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMonoSpeaker(int initType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	if (initType == FIRST_INIT)
	{
		// �I�u�W�F�N�g�̏�����
		objectMonoSpeaker.Texture = NULL;
		objectMonoSpeaker.Mesh = NULL;
		objectMonoSpeaker.BuffMat = NULL;
		objectMonoSpeaker.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(
			MONO_SPEAKER_MODEL,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
			D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
			pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
			NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			&objectMonoSpeaker.BuffMat,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
			&objectMonoSpeaker.NumMat,	// D3DXMATERIAL�\���̂̐�
			&objectMonoSpeaker.Mesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}
	}

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	monoSpeaker->pos = MONO_SPEAKER_POS;
	monoSpeaker->rot = D3DXVECTOR3(0.0f, -D3DX_PI / HALF, 0.0f);
	monoSpeaker->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	monoSpeaker->reverb = DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMonoSpeaker(void)
{
	if (objectMonoSpeaker.Texture != NULL)
	{// �e�N�X�`���̊J��
		objectMonoSpeaker.Texture->Release();
		objectMonoSpeaker.Texture = NULL;
	}

	if (objectMonoSpeaker.Mesh != NULL)
	{// ���b�V���̊J��
		objectMonoSpeaker.Mesh->Release();
		objectMonoSpeaker.Mesh = NULL;
	}

	if (objectMonoSpeaker.BuffMat != NULL)
	{// �}�e���A���̊J��
		objectMonoSpeaker.BuffMat->Release();
		objectMonoSpeaker.BuffMat = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonoSpeaker(void)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	if (monoSpeaker->soundBuffer == NULL)
	{// ����ǂݍ���
		monoSpeaker->soundBuffer = LoadSound(SOUND_3D);
		// �Đ�
		PlaySound(monoSpeaker->soundBuffer, E_DS8_FLAG_LOOP);
	}

	if (!IsPlaying(monoSpeaker->soundBuffer))
	{
		// �Đ�
		PlaySound(monoSpeaker->soundBuffer, E_DS8_FLAG_LOOP);
	}	

	// ��ʑJ��
	Set3DStage();
}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonoSpeaker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	DRAW_TOOL MonoSpeakerTool;
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&objectMonoSpeaker.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&MonoSpeakerTool.mtxScl, monoSpeaker->scl.x, monoSpeaker->scl.y, monoSpeaker->scl.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&MonoSpeakerTool.mtxRot, monoSpeaker->rot.y, monoSpeaker->rot.x, monoSpeaker->rot.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&MonoSpeakerTool.mtxTranslate, monoSpeaker->pos.x, monoSpeaker->pos.y, monoSpeaker->pos.z);
	D3DXMatrixMultiply(&objectMonoSpeaker.mtxWorld, &objectMonoSpeaker.mtxWorld, &MonoSpeakerTool.mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &objectMonoSpeaker.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&MonoSpeakerTool.matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾(���ɖ߂����߂�BackUp)
	MonoSpeakerTool.pD3DXMat = (D3DXMATERIAL*)objectMonoSpeaker.BuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)objectMonoSpeaker.NumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&MonoSpeakerTool.pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, objectMonoSpeaker.Texture);

		// �`��
		objectMonoSpeaker.Mesh->DrawSubset(nCntMat);
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&MonoSpeakerTool.matDef);

}

//=============================================================================
// ���m�����X�s�[�J�[�̏����擾
//=============================================================================
MONO_SPEAKER *GetMonoSpeaker(void)
{
	return&monoSpeakerWk;
}

//=============================================================================
// ��ʑJ��
//=============================================================================
void Set3DStage(void)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// �v���C���[
	if (GetKeyboardTrigger(DIK_1))
	{
		StopSound(monoSpeaker->soundBuffer);
		SetStage(STAGE_PLAYER);
	}

	// �g�`
	else if (GetKeyboardTrigger(DIK_2))
	{
		StopSound(monoSpeaker->soundBuffer);
		SetStage(STAGE_WAVE);
	}
}
