//=============================================================================
// < Amateur Tools�v���O���� >
// �����o�[�u�̏��� [reverb.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "monoSpeaker.h"
#include "playerButton.h"
#include "reverb.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//-----------�`�揈��
void DrawReverbButton(void);			// �����o�[�u�̃{�^��
void DrawReverbBackground(void);		// �����o�[�u�̔w�i
void DrawReverbExitButton(void);		// �����o�[�u�̖߂�{�^��
void DrawReverbDefaultSwitch(void);		// �f�t�H���g�̊����o�[�u�̃X�E�B�b�`
void DrawSettingFont(void);				// �����o�[�u�̐ݒ�p�t�H���g
void DrawSwitchButton(void);			// �f�t�H���g�����o�[�u�̃{�^��

//-----------�X�V����
//----�����蔻��
void ReverButtonCollider(HWND hWnd);	// �����o�[�u�̃{�^������
//----�����o�[�u
void SetReverb(LPDIRECTSOUNDBUFFER8 pBuffer, int reverbType);	// �����o�[�u�̐ݒ�
//----�ړ�����
void SetReverbBackgroundMove(void);		// �����o�[�u�̔w�i�ړ�����
//----�߂�{�^��
void SetReverbExitButton(HWND hWnd);	// �����o�[�u�̖߂�{�^������
//----�f�t�H���g�X�E�B�b�`
void SetReverbDefaultSwitch(HWND hWnd);	// �����o�[�u�̃X�E�B�b�`����
//----�F�E�I������
void SetSelectColor(void);				// �����o�[�u�̐F�ƑI������
//----�l�̏���
void SetCustomReverb(void);				// �����o�[�u�̒l����
//----�����o�[�u�ԍ�
void SetDefaultReverbNum(HWND hWnd);	// �����o�[�u�ԍ�����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
DSFXI3DL2Reverb reverbWk;				// �����o�[�u�̍\����

TEXTURE			reverbButtonOn;			// �����o�[�u�̃{�^��(�I��)
TEXTURE			reverbButtonOff;		// �����o�[�u�̃{�^��(�I�t)
TEXTURE			reverbBackground00;		// �����o�[�u�̔w�i(0��)
TEXTURE			reverbBackground01;		// �����o�[�u�̔w�i(1��)
TEXTURE			reverbExitButton;		// �����o�[�u�̖߂�{�^��
TEXTURE			reverbDefaultSwitch;	// �f�t�H���g�����o�[�u�̃X�E�B�b�`
TEXTURE			reverbLeftButton;		// �f�t�H���g�����o�[�u�̃{�^��(��)
TEXTURE			reverbRightButton;		// �f�t�H���g�����o�[�u�̃{�^��(�E)

LPD3DXFONT		reverDefaultFont;		// �f�t�H���g�̊����o�[�u�̃t�H���g

int				reverSelect;			// �I��

bool			defaultReverb;			// �f�t�H���g�����o�[�u�̃X�E�B�b�`
bool			reverbSwitch;			// �����o�[�u�̃X�E�B�b�`

// �����o�[�u�̐ݒ�p�t�H���g�\����
REVERB_CONTROL	reverSetting[REVERB_SETTING_FONT_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitReverb(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		reverbBackground00.texture	= NULL;
		reverbBackground01.texture	= NULL;

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_ON_REVERB,				// �t�@�C���̖��O
		&reverbButtonOn.texture);				// �ǂݍ��ރ������[
		
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_OFF_REVERB,				// �t�@�C���̖��O
		&reverbButtonOff.texture);				// �ǂݍ��ރ������[
		
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_REVERB_EXIT_BUTTON,				// �t�@�C���̖��O
		&reverbExitButton.texture);				// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_REVERB_DEFAULT_SWITCH,			// �t�@�C���̖��O
		&reverbDefaultSwitch.texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_REVERB_BUTTON_LEFT,				// �t�@�C���̖��O
		&reverbLeftButton.texture);				// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_REVERB_BUTTON_RIGHT,			// �t�@�C���̖��O
		&reverbRightButton.texture);			// �ǂݍ��ރ������[

		for (int i = 0; i < REVERB_SETTING_FONT_MAX; i++)
		{
			// ���\���p�t�H���g��ݒ�
			D3DXCreateFont(pDevice, (UINT)REVERB_FONT_SIZE_Y, (INT)REVERB_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &reverSetting[i].font);
		}

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)(REVERB_FONT_SIZE_Y*1.5), (INT)(REVERB_FONT_SIZE_X*1.5), 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &reverDefaultFont);

	}

	{	// ���W�̏�����
		reverbButtonOn.pos		= REVERB_BUTTON_ON_POS;
		reverbButtonOff.pos		= REVERB_BUTTON_OFF_POS;
		reverbBackground00.pos	= BACKGROUND0_REVERB_POS;
		reverbBackground01.pos	= BACKGROUND1_REVERB_POS;
		reverbExitButton.pos	= REVERB_EXIT_BUTTON_POS;
		reverbDefaultSwitch.pos	= REVERB_DEFAULT_SWITCH_POS;
		reverbLeftButton.pos	= REVERB_BUTTON_LEFT_POS;
		reverbRightButton.pos	= REVERB_BUTTON_RIGHT_POS;
	}

	{	// ���̏�����
		reverSelect		= 0;
		reverbSwitch	= false;
		defaultReverb	= false;
	}

	{	// �����o�[�u�̏�����
		reverbWk.lRoom					= DSFX_I3DL2REVERB_ROOM_DEFAULT;
		reverbWk.lRoomHF				= DSFX_I3DL2REVERB_ROOMHF_DEFAULT;
		reverbWk.flRoomRolloffFactor	= DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_DEFAULT;
		reverbWk.flDecayTime			= DSFX_I3DL2REVERB_DECAYTIME_DEFAULT;
		reverbWk.flDecayHFRatio			= DSFX_I3DL2REVERB_DECAYHFRATIO_DEFAULT;
		reverbWk.lReflections			= DSFX_I3DL2REVERB_REFLECTIONS_DEFAULT;
		reverbWk.flReflectionsDelay		= DSFX_I3DL2REVERB_REFLECTIONSDELAY_DEFAULT;
		reverbWk.lReverb				= DSFX_I3DL2REVERB_REVERB_DEFAULT;
		reverbWk.flReverbDelay			= DSFX_I3DL2REVERB_REVERBDELAY_DEFAULT;
		reverbWk.flDiffusion			= DSFX_I3DL2REVERB_DIFFUSION_DEFAULT;
		reverbWk.flDensity				= DSFX_I3DL2REVERB_DENSITY_DEFAULT;
		reverbWk.flHFReference			= DSFX_I3DL2REVERB_HFREFERENCE_DEFAULT;
	}

	// ���_���̓ǂݍ���
	MakeVtx4PointData(reverbBackground00.vertexWk, reverbBackground00.pos, BACKGROUND0_REVERB_SIZE_X, BACKGROUND0_REVERB_SIZE_Y);
	MakeVtx4PointData(reverbBackground01.vertexWk, reverbBackground01.pos, BACKGROUND1_REVERB_SIZE_X, BACKGROUND1_REVERB_SIZE_Y);
	MakeVtx4PointData(reverbExitButton.vertexWk, reverbExitButton.pos, REVERB_EXIT_BUTTON_SIZE_X, REVERB_EXIT_BUTTON_SIZE_Y);
	MakeVtxCenterData(reverbButtonOn.vertexWk, reverbButtonOn.pos, REVERB_BUTTON_ON_SIZE_X, REVERB_BUTTON_ON_SIZE_Y);
	MakeVtxCenterData(reverbButtonOff.vertexWk, reverbButtonOff.pos, REVERB_BUTTON_OFF_SIZE_X, REVERB_BUTTON_OFF_SIZE_Y);
	MakeVtxCenterData(reverbDefaultSwitch.vertexWk, reverbDefaultSwitch.pos, REVERB_DEFAULT_SWITCH_SIZE_X, REVERB_DEFAULT_SWITCH_SIZE_Y);
	MakeVtxCenterData(reverbLeftButton.vertexWk, reverbLeftButton.pos, REVERB_BUTTON_LEFT_SIZE_X, REVERB_BUTTON_LEFT_SIZE_Y);
	MakeVtxCenterData(reverbRightButton.vertexWk, reverbRightButton.pos, REVERB_BUTTON_RIGHT_SIZE_X, REVERB_BUTTON_RIGHT_SIZE_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitReverb(void)
{
	if (reverbButtonOn.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbButtonOn.texture->Release();
		reverbButtonOn.texture = NULL;
	}

	if (reverbButtonOff.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbButtonOff.texture->Release();
		reverbButtonOff.texture = NULL;
	}

	if (reverbBackground00.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbBackground00.texture->Release();
		reverbBackground00.texture = NULL;
	}

	if (reverbBackground01.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbBackground01.texture->Release();
		reverbBackground01.texture = NULL;
	}

	if (reverbExitButton.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbExitButton.texture->Release();
		reverbExitButton.texture = NULL;
	}

	if (reverbDefaultSwitch.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbDefaultSwitch.texture->Release();
		reverbDefaultSwitch.texture = NULL;
	}

	if (reverbLeftButton.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbLeftButton.texture->Release();
		reverbLeftButton.texture = NULL;
	}

	if (reverbRightButton.texture != NULL)
	{// �e�N�X�`���̊J��	  
		reverbRightButton.texture->Release();
		reverbRightButton.texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReverb(HWND hWnd)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// �����o�[�u�̃X�e�[�W
	if (GetStage() == STAGE_REVERB)
	{
		// �w�i�̈ړ�����
		SetReverbBackgroundMove();
		
		// �߂�{�^���̏���
		SetReverbExitButton(hWnd);

		// �����o�[�u�̐F�ƑI������
		SetSelectColor();

		// �����o�[�u�̒l����
		SetCustomReverb();

		// �����o�[�u�̃X�E�B�b�`����
		SetReverbDefaultSwitch(hWnd);

		if (defaultReverb)
		{
			// �����o�[�u�ԍ�����
			SetDefaultReverbNum(hWnd);
		}
	}

	else
	{
		// �����o�[�u�̏���
		ReverButtonCollider(hWnd);
	}

	if (!reverbSwitch)
	{
		reverSelect = 0;
		defaultReverb = false;
		SetSoundEffect(monoSpeaker->soundBuffer, E_DS8_FLAG_LOOP, 0);
	}
}

//=============================================================================
// �����o�[�u�̖߂�{�^������
//=============================================================================
void SetReverbExitButton(HWND hWnd)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// �ړ�����
	if (reverbExitButton.pos.y >= REVERB_EXIT_BUTTON_STOP_POS_Y)
	{
		reverbExitButton.pos.y -= BACKGROUND_MOVE_SPEED;
	}

	// �߂�{�^���̓����蔻��
	if (CheckHitBB(GetMousePos(hWnd), reverbExitButton.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_EXIT_BUTTON_SIZE_X, REVERB_EXIT_BUTTON_SIZE_Y)))
	{
		SetAllDiffuseData(reverbExitButton.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			{	// ���W�̏�����
				reverbButtonOn.pos = REVERB_BUTTON_ON_POS;
				reverbBackground00.pos = BACKGROUND0_REVERB_POS;
				reverbBackground01.pos = BACKGROUND1_REVERB_POS;
				reverbExitButton.pos = REVERB_EXIT_BUTTON_POS;
				reverbDefaultSwitch.pos = REVERB_DEFAULT_SWITCH_POS;
				reverbLeftButton.pos = REVERB_BUTTON_LEFT_POS;
				reverbRightButton.pos = REVERB_BUTTON_RIGHT_POS;
			}
			SetReverb(monoSpeaker->soundBuffer, monoSpeaker->reverb);
			SetStage(STAGE_3D);
		}
	}

	else
	{
		SetAllDiffuseData(reverbExitButton.vertexWk, BUTTON_NORMAL_COLOR);
	}
}

//=============================================================================
// �����o�[�u�̃X�E�B�b�`����
//=============================================================================
void SetReverbDefaultSwitch(HWND hWnd)
{
	// �ړ�����
	if (reverbDefaultSwitch.pos.x >= REVERB_DEFAULT_SWITCH_STOP_POS_X)
	{
		reverbDefaultSwitch.pos.x -= BACKGROUND_MOVE_SPEED;
	}

	if (reverbLeftButton.pos.x >= REVERB_BUTTON_LEFT_STOP_POS_X)
	{
		reverbLeftButton.pos.x -= BACKGROUND_MOVE_SPEED;
	}

	if (reverbRightButton.pos.x >= REVERB_BUTTON_RIGHT_STOP_POS_X)
	{
		reverbRightButton.pos.x -= BACKGROUND_MOVE_SPEED;
	}

	// �߂�{�^���̓����蔻��
	if (CheckHitBB(GetMousePos(hWnd), reverbDefaultSwitch.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_DEFAULT_SWITCH_SIZE_X, REVERB_DEFAULT_SWITCH_SIZE_Y)))
	{
		SetAllDiffuseData(reverbDefaultSwitch.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			{// �X�E�B�b�`
				if (defaultReverb)
				{
					defaultReverb = false;
				}

				else if (!defaultReverb)
				{
					defaultReverb = true;
				}

				SetAllDiffuseData(reverbDefaultSwitch.vertexWk, BUTTON_NORMAL_COLOR);
			}
		}
	}

	else
	{
		if (defaultReverb)
		{
			SetAllDiffuseData(reverbDefaultSwitch.vertexWk, BUTTON_PRESS_COLOR);
		}

		else if (!defaultReverb)
		{
			SetAllDiffuseData(reverbDefaultSwitch.vertexWk, BUTTON_NORMAL_COLOR);
		}
	}

}

//=============================================================================
// �����o�[�u�w�i�̈ړ�����
//=============================================================================
void SetReverbBackgroundMove(void)
{
	if (reverbBackground00.pos.y <= BACKGROUND0_STOP_POS_Y)
	{
		reverbBackground00.pos.y += BACKGROUND_MOVE_SPEED;
	}

	if (reverbBackground01.pos.x >= BACKGROUND1_STOP_POS_X)
	{
		reverbBackground01.pos.x -= BACKGROUND_MOVE_SPEED;
	}
}

//=============================================================================
// �����o�[�u�̃{�^������
//=============================================================================
void ReverButtonCollider(HWND hWnd)
{
	// �����o�[�u(�I��)
	if (CheckHitBB(GetMousePos(hWnd), reverbButtonOn.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_BUTTON_ON_SIZE_X, REVERB_BUTTON_ON_SIZE_Y)))
	{
		SetAllDiffuseData(reverbButtonOn.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			reverbSwitch = true;
			SetStage(STAGE_REVERB);
		}
	}

	else
	{
		SetAllDiffuseData(reverbButtonOn.vertexWk, BUTTON_NORMAL_COLOR);
	}

	// �����o�[�u(�I�t)
	if (CheckHitBB(GetMousePos(hWnd), reverbButtonOff.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_BUTTON_OFF_SIZE_X, REVERB_BUTTON_OFF_SIZE_Y)))
	{
		SetAllDiffuseData(reverbButtonOff.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			reverbSwitch = false;
		}
	}

	else
	{
		SetAllDiffuseData(reverbButtonOff.vertexWk, BUTTON_NORMAL_COLOR);
	}
}

//=============================================================================
// �����o�[�u�̐F�ƑI������
//=============================================================================
void SetSelectColor(void)
{
	if (GetKeyboardRepeat(DIK_UP))
	{
		reverSelect--;
		if (reverSelect < 0)
		{
			reverSelect = REVERB_SETTING_FONT_MAX-1;
		}
	}

	else if (GetKeyboardRepeat(DIK_DOWN))
	{
		reverSelect++;
		if (reverSelect >= REVERB_SETTING_FONT_MAX)
		{
			reverSelect = 0;
		}
	}

	for (int i = 0; i < REVERB_SETTING_FONT_MAX; i++)
	{
		reverSetting[i].color = BUTTON_NORMAL_COLOR;
	}

	reverSetting[reverSelect].color = BUTTON_PRESS_COLOR;
}

//=============================================================================
// �����o�[�u�̒l����
//=============================================================================
void SetCustomReverb(void)
{
	switch (reverSelect)
	{
	case 0:
		// lRoom
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.lRoom -= REVERB_ROOM_UNIT;
			if (reverbWk.lRoom <= DSFX_I3DL2REVERB_ROOM_MIN)
			{
				reverbWk.lRoom = DSFX_I3DL2REVERB_ROOM_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.lRoom += REVERB_ROOM_UNIT;
			if (reverbWk.lRoom >= DSFX_I3DL2REVERB_ROOM_MAX)
			{
				reverbWk.lRoom = DSFX_I3DL2REVERB_ROOM_MAX;
			}
		}
		break;
	case 1:
		// lRoomHF
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.lRoomHF -= REVERB_ROOMHF_UNIT;
			if (reverbWk.lRoomHF <= DSFX_I3DL2REVERB_ROOMHF_MIN)
			{
				reverbWk.lRoomHF = DSFX_I3DL2REVERB_ROOMHF_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.lRoomHF += REVERB_ROOMHF_UNIT;
			if (reverbWk.lRoomHF >= DSFX_I3DL2REVERB_ROOMHF_MAX)
			{
				reverbWk.lRoomHF = DSFX_I3DL2REVERB_ROOMHF_MAX;
			}
		}
		break;
	case 2:
		// flRoomRolloffFactor
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flRoomRolloffFactor -= REVERB_ROOMROLLOFFFACTOR_UNIT;
			if (reverbWk.flRoomRolloffFactor <= DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MIN)
			{
				reverbWk.flRoomRolloffFactor = DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flRoomRolloffFactor += REVERB_ROOMROLLOFFFACTOR_UNIT;
			if (reverbWk.flRoomRolloffFactor >= DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MAX)
			{
				reverbWk.flRoomRolloffFactor = DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MAX;
			}
		}
		break;
	case 3:
		// flDecayTime
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flDecayTime -= REVERB_DECAYTIME_UNIT;
			if (reverbWk.flDecayTime <= DSFX_I3DL2REVERB_DECAYTIME_MIN)
			{
				reverbWk.flDecayTime = DSFX_I3DL2REVERB_DECAYTIME_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flDecayTime += REVERB_DECAYTIME_UNIT;
			if (reverbWk.flDecayTime >= DSFX_I3DL2REVERB_DECAYTIME_MAX)
			{
				reverbWk.flDecayTime = DSFX_I3DL2REVERB_DECAYTIME_MAX;
			}
		}
		break;
	case 4:
		// flDecayHFRatio
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flDecayHFRatio -= REVERB_FECAYHFRATIO_UNIT;
			if (reverbWk.flDecayHFRatio <= DSFX_I3DL2REVERB_DECAYHFRATIO_MIN)
			{
				reverbWk.flDecayHFRatio = DSFX_I3DL2REVERB_DECAYHFRATIO_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flDecayHFRatio += REVERB_FECAYHFRATIO_UNIT;
			if (reverbWk.flDecayHFRatio >= DSFX_I3DL2REVERB_DECAYHFRATIO_MAX)
			{
				reverbWk.flDecayHFRatio = DSFX_I3DL2REVERB_DECAYHFRATIO_MAX;
			}
		}
		break;
	case 5:
		// lReflections
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.lReflections -= REVERB_REFLECTIONS_UNIT;
			if (reverbWk.lReflections <= DSFX_I3DL2REVERB_REFLECTIONS_MIN)
			{
				reverbWk.lReflections = DSFX_I3DL2REVERB_REFLECTIONS_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.lReflections += REVERB_REFLECTIONS_UNIT;
			if (reverbWk.lReflections >= DSFX_I3DL2REVERB_REFLECTIONS_MAX)
			{
				reverbWk.lReflections = DSFX_I3DL2REVERB_REFLECTIONS_MAX;
			}
		}
		break;
	case 6:
		// flReflectionsDelay
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flReflectionsDelay -= REVERB_REFLECTIONSDELAY_UNIT;
			if (reverbWk.flReflectionsDelay <= DSFX_I3DL2REVERB_REFLECTIONSDELAY_MIN)
			{
				reverbWk.flReflectionsDelay = DSFX_I3DL2REVERB_REFLECTIONSDELAY_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flReflectionsDelay += REVERB_REFLECTIONSDELAY_UNIT;
			if (reverbWk.flReflectionsDelay >= DSFX_I3DL2REVERB_REFLECTIONSDELAY_MAX)
			{
				reverbWk.flReflectionsDelay = DSFX_I3DL2REVERB_REFLECTIONSDELAY_MAX;
			}
		}
		break;
	case 7:
		// lReverb
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.lReverb -= REVERB_REVERB_UNIT;
			if (reverbWk.lReverb <= DSFX_I3DL2REVERB_REVERB_MIN)
			{
				reverbWk.lReverb = DSFX_I3DL2REVERB_REVERB_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.lReverb += REVERB_REVERB_UNIT;
			if (reverbWk.lReverb >= DSFX_I3DL2REVERB_REVERB_MAX)
			{
				reverbWk.lReverb = DSFX_I3DL2REVERB_REVERB_MAX;
			}
		}
		break;
	case 8:
		// flReverbDelay
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flReverbDelay -= REVERB_REVERBDELAY_UNIT;
			if (reverbWk.flReverbDelay <= DSFX_I3DL2REVERB_REVERBDELAY_MIN)
			{
				reverbWk.flReverbDelay = DSFX_I3DL2REVERB_REVERBDELAY_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flReverbDelay += REVERB_REVERBDELAY_UNIT;
			if (reverbWk.flReverbDelay >= DSFX_I3DL2REVERB_REVERBDELAY_MAX)
			{
				reverbWk.flReverbDelay = DSFX_I3DL2REVERB_REVERBDELAY_MAX;
			}
		}
		break;
	case 9:
		// flDiffusion
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flDiffusion -= REVERB_DIFFUSION_UNIT;
			if (reverbWk.flDiffusion <= DSFX_I3DL2REVERB_DIFFUSION_MIN)
			{
				reverbWk.flDiffusion = DSFX_I3DL2REVERB_DIFFUSION_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flDiffusion += REVERB_DIFFUSION_UNIT;
			if (reverbWk.flDiffusion >= DSFX_I3DL2REVERB_DIFFUSION_MAX)
			{
				reverbWk.flDiffusion = DSFX_I3DL2REVERB_DIFFUSION_MAX;
			}
		}
		break;
	case 10:
		// flDensity
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flDensity -= REVERB_FENSITY_UNIT;
			if (reverbWk.flDensity <= DSFX_I3DL2REVERB_DENSITY_MIN)
			{
				reverbWk.flDensity = DSFX_I3DL2REVERB_DENSITY_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flDensity += REVERB_FENSITY_UNIT;
			if (reverbWk.flDensity >= DSFX_I3DL2REVERB_DENSITY_MAX)
			{
				reverbWk.flDensity = DSFX_I3DL2REVERB_DENSITY_MAX;
			}
		}
		break;
	case 11:
		// flHFReference
		if (GetKeyboardRepeat(DIK_LEFT))
		{
			reverbWk.flHFReference -= REVERB_HFREFERENCE_UNIT;
			if (reverbWk.flHFReference <= DSFX_I3DL2REVERB_HFREFERENCE_MIN)
			{
				reverbWk.flHFReference = DSFX_I3DL2REVERB_HFREFERENCE_MIN;
			}
		}
		else if (GetKeyboardRepeat(DIK_RIGHT))
		{
			reverbWk.flHFReference += REVERB_HFREFERENCE_UNIT;
			if (reverbWk.flHFReference >= DSFX_I3DL2REVERB_HFREFERENCE_MAX)
			{
				reverbWk.flHFReference = DSFX_I3DL2REVERB_HFREFERENCE_MAX;
			}
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// �����o�[�u�̐ݒ�
//=============================================================================
void SetReverb(LPDIRECTSOUNDBUFFER8 pBuffer, int reverbType)
{
	DWORD status = NULL;
	DWORD dwResults = NULL;
	IDirectSoundFXI3DL2Reverb8* pI3DL2Reverb;
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	if (pBuffer != NULL)
	{
		pBuffer->GetStatus(&status);

		if (status & DSBSTATUS_PLAYING)
		{
			pBuffer->Stop();

			// �G�t�F�N�g���L�q
			DSEFFECTDESC dsEffect;

			// �G�t�F�N�g�̏�����(�폜)
			pBuffer->SetFX(NULL, NULL, NULL);

			// �G�t�F�N�g�̕ύX����
			memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
			dsEffect.dwSize = sizeof(DSEFFECTDESC);
			dsEffect.dwFlags = 0;
			dsEffect.guidDSFXClass = GUID_DSFX_STANDARD_I3DL2REVERB;

			// �G�t�F�N�g��ݒ�
			pBuffer->SetFX(1, &dsEffect, &dwResults);

			pBuffer->GetObjectInPath(GUID_DSFX_STANDARD_I3DL2REVERB,
				0, IID_IDirectSoundFXI3DL2Reverb8, (VOID**)&pI3DL2Reverb);

			//���o�[�u�̕i����ݒ肷��
			if (FAILED(pI3DL2Reverb->SetQuality(DSFX_I3DL2REVERB_QUALITY_MAX)))
			{
				MessageBox(0, "�ō��i���ɃZ�b�g�o���܂���ł���", "�G���[", MB_OK);
				if (FAILED(pI3DL2Reverb->SetQuality(DSFX_I3DL2REVERB_QUALITY_DEFAULT)))
				{
					MessageBox(0, "�W���i���ɂ��Z�b�g�o���܂���ł���", "�G���[", MB_OK);
					if (FAILED(pI3DL2Reverb->SetQuality(DSFX_I3DL2REVERB_QUALITY_MIN)))
					{
						MessageBox(0, "�Œ�i���ł����s���܂���", "�G���[", MB_OK);
					}
					MessageBox(0, "�Œ�i���ɃZ�b�g���܂���", "�G���[", MB_OK);
				}
			}

			//�G�t�F�N�g�p�����[�^�[���Z�b�g
			if (defaultReverb)
			{
				if (FAILED(pI3DL2Reverb->SetPreset(monoSpeaker->reverb)))
				{
					pI3DL2Reverb->Release();
				}
			}
			else if (!defaultReverb)
			{
				if (FAILED(pI3DL2Reverb->SetAllParameters(&reverbWk)))
				{
					pI3DL2Reverb->Release();
				}
			}
			pI3DL2Reverb->Release();

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
			default:
				break;
			}
			pBuffer->Play(0, 0, E_DS8_FLAG_LOOP);
		}
	}
}

//=============================================================================
// �����o�[�u�ԍ�����
//=============================================================================
void SetDefaultReverbNum(HWND hWnd)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	// �߂�{�^���̓����蔻��
	if (CheckHitBB(GetMousePos(hWnd), reverbLeftButton.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_BUTTON_LEFT_SIZE_X, REVERB_BUTTON_LEFT_SIZE_Y)))
	{
		SetAllDiffuseData(reverbLeftButton.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			{
				monoSpeaker->reverb--;
				if (monoSpeaker->reverb < DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT)
				{
					monoSpeaker->reverb = DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE;
				}

				SetAllDiffuseData(reverbLeftButton.vertexWk, BUTTON_NORMAL_COLOR);
			}
		}
	}

	else
	{
		SetAllDiffuseData(reverbLeftButton.vertexWk, BUTTON_NORMAL_COLOR);
	}

	// �߂�{�^���̓����蔻��
	if (CheckHitBB(GetMousePos(hWnd), reverbRightButton.pos, CURSOR_SIZE, D3DXVECTOR2(REVERB_BUTTON_RIGHT_SIZE_X, REVERB_BUTTON_RIGHT_SIZE_Y)))
	{
		SetAllDiffuseData(reverbRightButton.vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			{
				monoSpeaker->reverb++;
				if (monoSpeaker->reverb > DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE)
				{
					monoSpeaker->reverb = DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT;
				}

				SetAllDiffuseData(reverbRightButton.vertexWk, BUTTON_NORMAL_COLOR);
			}
		}
	}

	else
	{
		SetAllDiffuseData(reverbRightButton.vertexWk, BUTTON_NORMAL_COLOR);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawReverb(void)
{
	// �����o�[�u�X�e�[�W
	if (GetStage() == STAGE_REVERB)
	{
		// �����o�[�u�̃X�e�[�W�w�i
		DrawReverbBackground();

		// �����o�[�u�̖߂�{�^��
		DrawReverbExitButton();

		// �f�t�H���g�̊����o�[�u�̃X�E�B�b�`
		DrawReverbDefaultSwitch();

		// �ݒ�p�t�H���g
		DrawSettingFont();

		// �f�t�H���g�����o�[�u�̃{�^��
		DrawSwitchButton();
	}

	else
	{
		// �����o�[�u�̃{�^��
		DrawReverbButton();

	}
}

//=============================================================================
// �`�揈��(�����o�[�u)
//=============================================================================
void DrawReverbButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbButtonOn.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbButtonOn.vertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbButtonOff.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbButtonOff.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�����o�[�u�̃X�e�[�W�w�i)
//=============================================================================
void DrawReverbBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbBackground00.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(reverbBackground00.vertexWk, BACKGROUND_COLOR);

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(reverbBackground00.vertexWk, reverbBackground00.pos, BACKGROUND0_REVERB_SIZE_X, BACKGROUND0_REVERB_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbBackground00.vertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbBackground01.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(reverbBackground01.vertexWk, BACKGROUND_COLOR);

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(reverbBackground01.vertexWk, reverbBackground01.pos, BACKGROUND1_REVERB_SIZE_X, BACKGROUND1_REVERB_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbBackground01.vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// �`�揈��(�����o�[�u�̖߂�{�^��)
//=============================================================================
void DrawReverbExitButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbExitButton.texture);

	// ���_���W�̐ݒ�(���_���)
	SetVtxCenterData(reverbExitButton.vertexWk, reverbExitButton.pos, REVERB_EXIT_BUTTON_SIZE_X, REVERB_EXIT_BUTTON_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbExitButton.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�f�t�H���g�̊����o�[�u�̃X�E�B�b�`)
//=============================================================================
void DrawReverbDefaultSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbDefaultSwitch.texture);

	// ���_���W�̐ݒ�(���_���)
	SetVtxCenterData(reverbDefaultSwitch.vertexWk, reverbDefaultSwitch.pos, REVERB_DEFAULT_SWITCH_SIZE_X, REVERB_DEFAULT_SWITCH_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbDefaultSwitch.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �����o�[�u�̐ݒ�p�t�H���g
//=============================================================================
void DrawSettingFont(void)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();

	RECT rect[REVERB_FONT_TYPE_MAX];
	rect[0] = { (LONG)(reverbBackground00.pos.x), (LONG)(reverbBackground00.pos.y),SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[REVERB_FONT_TYPE_MAX][256];

	// �J�X�^�������o�[�u
	for (int i = 0; i < REVERB_SETTING_FONT_MAX; i++)
	{
		switch (i)
		{
		case 0:
			// lRoom
			sprintf(str[0], _T("��ԃG�t�F�N�g�̌���:%ld mB"), reverbWk.lRoom);
			break;
		case 1:
			// lRoomHF
			sprintf(str[0], _T("�����g����ԃG�t�F�N�g�̌���:%ld mB"), reverbWk.lRoomHF);
			break;
		case 2:
			// flRoomRolloffFactor
			sprintf(str[0], _T("���˂����M���̃��[���I�t�W��:%f"), reverbWk.flRoomRolloffFactor);
			break;
		case 3:
			// flDecayTime
			sprintf(str[0], _T("��������:%f �b"), reverbWk.flDecayTime);
			break;
		case 4:
			// flDecayHFRatio
			sprintf(str[0], _T("�����g���̌������Ԃ̔䗦:%f"), reverbWk.flDecayHFRatio);
			break;
		case 5:
			// lReflections
			sprintf(str[0], _T("�������˂̌���:%ld mB"), reverbWk.lReflections);
			break;
		case 6:
			// flReflectionsDelay
			sprintf(str[0], _T("�������˂̒x������:%f �b"), reverbWk.flReflectionsDelay);
			break;
		case 7:
			// lReverb
			sprintf(str[0], _T("������o�[�u�̌���:%ld mB"), reverbWk.lReverb);
			break;
		case 8:
			// flReverbDelay
			sprintf(str[0], _T("�������˂ƌ�����o�[�u�Ԃ̐�������:%f �b"), reverbWk.flReverbDelay);
			break;
		case 9:
			// flDiffusion
			sprintf(str[0], _T("������o�[�u�����̃G�R�[���x:%f %%"), reverbWk.flDiffusion);
			break;
		case 10:
			// flDensity
			sprintf(str[0], _T("������o�[�u�����̃��[�_�����x:%f %%"), reverbWk.flDensity);
			break;
		case 11:
			// flHFReference
			sprintf(str[0], _T("�Q�ƍ����g��:%f Hz"), reverbWk.flHFReference);
			break;
		default:
			break;
		}

		// �`��
		reverSetting[i].font->DrawText(NULL, str[0], -1, &rect[0], DT_LEFT, reverSetting[i].color);

		// �G�t�F�N�g�t�H���g�̍��WY = (�G�t�F�N�g�ԍ� * �t�H���g�̍���) + �t�H���g�̊Ԋu
		rect[0].top += (REVERB_FONT_SIZE_Y + REVERB_FONT_INTERVAL);
	}

	// �f�t�H���g�����o�[�u
	if (defaultReverb)
	{
		rect[1] = { (LONG)(reverbBackground01.pos.x + REVERB_FONT_INTERVAL*2),
			(LONG)(reverbBackground01.pos.y + REVERB_DEFAULT_SWITCH_SIZE_X),SCREEN_WIDTH , SCREEN_HEIGHT };

		switch (monoSpeaker->reverb)
		{
		case DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT:
			sprintf(str[1], _T("DEFAULT"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC:
			sprintf(str[1], _T("GENERIC"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL:
			sprintf(str[1], _T("PADDEDCELL"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM:
			sprintf(str[1], _T("ROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM:
			sprintf(str[1], _T("BATHROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM:
			sprintf(str[1], _T("LIVINGROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM:
			sprintf(str[1], _T("STONEROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM:
			sprintf(str[1], _T("AUDITORIUM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL:
			sprintf(str[1], _T("CONCERTHALL"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE:
			sprintf(str[1], _T("CAVE"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA:
			sprintf(str[1], _T("ARENA"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR:
			sprintf(str[1], _T("HANGAR"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY:
			sprintf(str[1], _T("CARPETEDHALLWAY"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY:
			sprintf(str[1], _T("HALLWAY"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR:
			sprintf(str[1], _T("STONECORRIDOR"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY:
			sprintf(str[1], _T("ALLEY"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST:
			sprintf(str[1], _T("FOREST"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_CITY:
			sprintf(str[1], _T("CITY"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS:
			sprintf(str[1], _T("MOUNTAINS"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY:
			sprintf(str[1], _T("QUARRY"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN:
			sprintf(str[1], _T("PLAIN"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT:
			sprintf(str[1], _T("PARKINGLOT"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE:
			sprintf(str[1], _T("SEWERPIPE"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER:
			sprintf(str[1], _T("UNDERWATER"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM:
			sprintf(str[1], _T("SMALLROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM:
			sprintf(str[1], _T("MEDIUMROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM:
			sprintf(str[1], _T("LARGEROOM"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL:
			sprintf(str[1], _T("MEDIUMHALL"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL:
			sprintf(str[1], _T("LARGEHALL"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		case DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE:
			sprintf(str[1], _T("PLATE"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		default:
			sprintf(str[1], _T("error"));
			reverDefaultFont->DrawText(NULL, str[1], -1, &rect[1], DT_LEFT, BUTTON_PRESS_COLOR);
			break;
		}
	}
}

//=============================================================================
// �`�揈��(�f�t�H���g�����o�[�u�̃{�^��)
//=============================================================================
void DrawSwitchButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbLeftButton.texture);

	// ���_���W�̐ݒ�(���_���)
	SetVtxCenterData(reverbLeftButton.vertexWk, reverbLeftButton.pos, REVERB_BUTTON_LEFT_SIZE_X, REVERB_BUTTON_LEFT_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbLeftButton.vertexWk, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, reverbRightButton.texture);

	// ���_���W�̐ݒ�(���_���)
	SetVtxCenterData(reverbRightButton.vertexWk, reverbRightButton.pos, REVERB_BUTTON_RIGHT_SIZE_X, REVERB_BUTTON_RIGHT_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &reverbRightButton.vertexWk, sizeof(VERTEX_2D));
}

