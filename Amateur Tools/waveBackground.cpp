//=============================================================================
// < Amateur Tools�v���O���� >
// �g�̔w�i���� [waveBackground.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "waveBackground.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TEXTURE				waveBackground;	// �w�i

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWaveBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WAVE_BACKGROUND,						// �t�@�C���̖��O
		&waveBackground.texture);					// �ǂݍ��ރ������[
	}

	// ���_�t�H�[�}�b�g(���쌠�錾)
	MakeVtx4PointData(waveBackground.vertexWk, waveBackground.pos, SCREEN_WIDTH, SCREEN_HEIGHT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWaveBackground(void)
{
	if (waveBackground.texture != NULL)
	{// �e�N�X�`���̊J��
		waveBackground.texture->Release();
		waveBackground.texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWaveBackground(void)
{
	// ���ɂȂ� :D
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWaveBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, waveBackground.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, waveBackground.vertexWk, sizeof(VERTEX_2D));
}
