//=============================================================================
//
// �����o�[�u���� [reverb.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _REVERB_H_
#define _REVERB_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �����o�[�u�{�[�^��(�I��)
#define	TEXTURE_BUTTON_ON_REVERB			_T("data/TEXTURE/3D/reverb.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_BUTTON_ON_POS				D3DXVECTOR3(1130.0f,686.5f,0.0f)
#define REVERB_BUTTON_ON_SIZE_X				(150.0f)
#define REVERB_BUTTON_ON_SIZE_Y				(33.5f)
// �����o�[�u�{�[�^��(�I�t)
#define	TEXTURE_BUTTON_OFF_REVERB			_T("data/TEXTURE/3D/reverbOff.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_BUTTON_OFF_POS				D3DXVECTOR3(1130.0f,619.5f,0.0f)
#define REVERB_BUTTON_OFF_SIZE_X			(150.0f)
#define REVERB_BUTTON_OFF_SIZE_Y			(33.5f)

// �����o�[�u�w�i(0��)
#define BACKGROUND0_REVERB_POS				D3DXVECTOR3(10.0f,-680.0f,0.0f)
#define BACKGROUND0_STOP_POS_Y				(10)
#define BACKGROUND0_REVERB_SIZE_X			(600.0f)
#define BACKGROUND0_REVERB_SIZE_Y			(680.0f)
// �����o�[�u�w�i(1��)
#define BACKGROUND1_REVERB_POS				D3DXVECTOR3(1280.0f,10,0.0f)
#define BACKGROUND1_STOP_POS_X				(870)
#define BACKGROUND1_REVERB_SIZE_X			(400.0f)
#define BACKGROUND1_REVERB_SIZE_Y			(400.0f)

// �����o�[�u�̖߂�{�^��
#define	TEXTURE_REVERB_EXIT_BUTTON			_T("data/TEXTURE/3D/exit.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_EXIT_BUTTON_POS				D3DXVECTOR3(720.0f,720.5f,0.0f)
#define REVERB_EXIT_BUTTON_STOP_POS_Y		(705)
#define REVERB_EXIT_BUTTON_SIZE_X			(150.0f)
#define REVERB_EXIT_BUTTON_SIZE_Y			(30.0f)

// �f�t�H���g�����o�[�u�̃X�E�B�b�`
#define	TEXTURE_REVERB_DEFAULT_SWITCH		_T("data/TEXTURE/3D/defaultReverb.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_DEFAULT_SWITCH_POS			D3DXVECTOR3(1480.0f,100.0f,0.0f)
#define REVERB_DEFAULT_SWITCH_STOP_POS_X	(1070)
#define REVERB_DEFAULT_SWITCH_SIZE_X		(150.0f)
#define REVERB_DEFAULT_SWITCH_SIZE_Y		(50.0f)

// �f�t�H���g�����o�[�u�̃{�^��(��)
#define	TEXTURE_REVERB_BUTTON_LEFT			_T("data/TEXTURE/3D/left.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_BUTTON_LEFT_POS				D3DXVECTOR3(1385.0f,300.0f,0.0f)
#define REVERB_BUTTON_LEFT_STOP_POS_X		(975.0f)
#define REVERB_BUTTON_LEFT_SIZE_X			(50.0f)
#define REVERB_BUTTON_LEFT_SIZE_Y			(50.0f)

// �f�t�H���g�����o�[�u�̃{�^��(�E)
#define	TEXTURE_REVERB_BUTTON_RIGHT			_T("data/TEXTURE/3D/right.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define REVERB_BUTTON_RIGHT_POS				D3DXVECTOR3(1595.0f,300.0f,0.0f)
#define REVERB_BUTTON_RIGHT_STOP_POS_X		(1185.0f)
#define REVERB_BUTTON_RIGHT_SIZE_X			(50.0f)
#define REVERB_BUTTON_RIGHT_SIZE_Y			(50.0f)

// �w�i�̈ړ����x
#define	BACKGROUND_MOVE_SPEED				(15.0f)
// �w�i�̐F
#define BACKGROUND_COLOR					D3DXCOLOR(0.0f,0.0f,0.0f,0.1f)

// �f�t�H���g�����o�[�u
// �ő吔
#define REVERB_DEFAULT_MAX					(29)

// �ݒ�p�t�H���g
// �ő吔
#define REVERB_SETTING_FONT_MAX				(12)

// �P��
#define REVERB_ROOM_UNIT					(10)
#define REVERB_ROOMHF_UNIT					(10)
#define REVERB_ROOMROLLOFFFACTOR_UNIT		(0.001f)
#define REVERB_DECAYTIME_UNIT				(0.001f)
#define REVERB_FECAYHFRATIO_UNIT			(0.001f)
#define REVERB_REFLECTIONS_UNIT				(10)
#define REVERB_REFLECTIONSDELAY_UNIT		(0.0001f)
#define REVERB_REVERB_UNIT					(10)
#define REVERB_REVERBDELAY_UNIT				(0.0001f)
#define REVERB_DIFFUSION_UNIT				(1.0f)
#define REVERB_FENSITY_UNIT					(1.0f)
#define REVERB_HFREFERENCE_UNIT				(10.0f)

// �t�H���g
// �t�H���g���
#define REVERB_FONT_TYPE_MAX				(2)
// �t�H���g�T�C�Y
#define REVERB_FONT_SIZE_X					(15)
#define REVERB_FONT_SIZE_Y					(30)
#define REVERB_FONT_INTERVAL				(28)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~���[�W�b�N�v���C���[�\����
{
	LPD3DXFONT	font;
	D3DXCOLOR	color;

}REVERB_CONTROL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitReverb(int InitType);	// ����������
void UninitReverb(void);			// �I������
void UpdateReverb(HWND hWnd);		// �X�V����
void DrawReverb(void);				// �`�揈��

#endif