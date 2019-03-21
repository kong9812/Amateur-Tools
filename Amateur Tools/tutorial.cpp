//=============================================================================
// < Amateur Tools�v���O���� >
// �`���[�g���A������ [tutorial.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "tutorial.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
TEXTURE			tutorialScreen;		// �`���[�g���A�����


//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitTutorial(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL_SCREEN,					// �t�@�C���̖��O
		&tutorialScreen.texture);					// �ǂݍ��ރ������[
	}

	{
		tutorialScreen.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ʒu
	}

	// ���_�t�H�[�}�b�g
	MakeVtx4PointData(tutorialScreen.vertexWk, tutorialScreen.pos, SCREEN_WIDTH, SCREEN_HEIGHT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	if (tutorialScreen.texture != NULL)
	{// �e�N�X�`���̊J��
		tutorialScreen.texture->Release();
		tutorialScreen.texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	// ENTER�L�[����������i��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetStage(STAGE_PLAYER);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, tutorialScreen.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tutorialScreen.vertexWk, sizeof(VERTEX_2D));

}


