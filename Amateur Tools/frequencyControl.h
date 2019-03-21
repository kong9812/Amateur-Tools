//=============================================================================
//
// ���g���̃R���g���[������ [frequencyControl.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _FREQUENCY_CONTROL_
#define _FREQUENCY_CONTROL_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �w�i
#define FREQUENCY_CONTROL_BG_POS			D3DXVECTOR3(1010.0f,380.0f,0.0f)
#define FREQUENCY_CONTROL_BG_COLOR			D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define FREQUENCY_CONTROL_BG_SIZE_X			(260)
#define FREQUENCY_CONTROL_BG_SIZE_Y			(180)

// ���g��
#define FREQUENCY_NUM_POS					D3DXVECTOR2(1030.0f,400.0f)
#define FREQUENCY_NUM_COLOR					D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define FREQUENCY_NUM_FONT_SIZE_X			(20)
#define FREQUENCY_NUM_FONT_SIZE_Y			(40)

// �w���p�̃e�N�X�`��
#define	TEXTURE_KEY_SHIFT_UP				_T("data/TEXTURE/Button/ShiftUp.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_KEY_SHIFT_DOWN				_T("data/TEXTURE/Button/ShiftDown.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define KEY_SHIFT_UP_POS					D3DXVECTOR3(1060.0f,455.0f,0.0f)
#define KEY_SHIFT_DOWN_POS					D3DXVECTOR3(1060.0f,515.0f,0.0f)
#define KEY_SHIFT_SIZE_X					(140.0f)
#define KEY_SHIFT_SIZE_Y					(40.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~���[�W�b�N�v���C���[�\����
{
	LPD3DXFONT	font;
	D3DXCOLOR	color;

}FREQUENCYFONT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFrequencyControl(int InitType);		// ������
void UninitFrequencyControl(void);				// �I��
void DrawFrequencyControl(void);				// �`��

#endif