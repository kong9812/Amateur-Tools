//=============================================================================
// < Amateur Tools�v���O���� >
// �v���C���[�̃}�l�[�W���[���� [playerManager.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "soundEffect.h"
#include "frequencyControl.h"
#include "playerControl.h"
#include "playerButton.h"
#include "effectControl.h"
#include "playerBackground.h"
#include "playerManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//------------�`�揈��
void DrawPlayerDebugFont(HWND hWnd);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
#ifdef _DEBUG
LPD3DXFONT				g_pD3DXPlayerDebugFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitPlayerManager(int InitType)
{
	// �v���C���[�̔w�i
	InitPlayerBackground(InitType);

	// �v���C���[�̃R���g���[��
	InitPlayerControl(InitType);

	// �v���C���[�̃{�^��
	InitPlayerButton(InitType);

	// �G�t�F�N�g�̃R���g���[��
	InitEffectControl(InitType);

	// ���g���̃R���g���[��
	InitFrequencyControl(InitType);

#ifdef _DEBUG
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(GetDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXPlayerDebugFont);
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerManager(void)
{
	// �v���C���[�̔w�i
	UninitPlayerBackground();

	// �v���C���[�̃R���g���[��
	UninitPlayerControl();

	// �v���C���[�̃{�^��
	UninitPlayerButton();

	// �G�t�F�N�g�̃R���g���[��
	UninitEffectControl();

	// ���g���̃R���g���[��
	UninitFrequencyControl();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerManager(HWND hWnd)
{
	// �v���C���[�̔w�i
	UpdatePlayerBackground();
	
	// �v���C���[�̃R���g���[��
	UpdatePlayerControl(hWnd);
	
	// �v���C���[�̃{�^��
	UpdatePlayerButton(hWnd);
	
	// �G�t�F�N�g�̃R���g���[��
	UpdateEffectControl(hWnd);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerManager(HWND hWnd)
{
	// �v���C���[�̔w�i
	DrawPlayerBackground();
	
	// �v���C���[�̃R���g���[��
	DrawPlayerControl();
	
	// �v���C���[�̃{�^��
	DrawPlayerButton();
	
	// �G�t�F�N�g�̃R���g���[��
	DrawEffectControl();

	// ���g���̃R���g���[��
	DrawFrequencyControl();

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawPlayerDebugFont(hWnd);
#endif
}

#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�\������
//=============================================================================
void DrawPlayerDebugFont(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[CHAR_MAX];

	// sound effect
	rect.top = 20;				// �����̍���(FPS�̉�)
	switch (song->effectNo)
	{
	case NULL_SOUND_EFFECT:
		sprintf(str, _T("NULL �G�t�F�N�g�Ȃ�"));
		break;
	case WATER_SOUND_EFFECT:
		sprintf(str, _T("GARGLE �K�[�O��"));
		break;
	case CHORUS_SOUND_EFFECT:
		sprintf(str, _T("CHORUS �R�[���X"));
		break;
	case FLANGER_SOUND_EFFECT:
		sprintf(str, _T("FLANGER �t�����W"));
		break;
	case ECHO_SOUND_EFFECT:
		sprintf(str, _T("ECHO �G�R�["));
		break;
	case DISTORTION_SOUND_EFFECT:
		sprintf(str, _T("DISTORTION �f�B�X�g�[�V����"));
		break;
	case COMPRESSOR_SOUND_EFFECT:
		sprintf(str, _T("COMPRESSOR �R���v���b�T�["));
		break;
	case PARAMEQ_SOUND_EFFECT:
		sprintf(str, _T("PARAMEQ �p�����g���b�N �C�R���C�U�["));
		break;
	case I3DL2REVERB_SOUND_EFFECT:
		sprintf(str, _T("I3DL2REVERB �����o�[�u"));
		break;
	case WAVES_REVERB_SOUND_EFFECT:
		sprintf(str, _T("WAVES_REVERB Wave �c��"));
		break;
	default:
		break;
	}
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0xff, 0xff));

	// sound_pos
	rect.top += 20;
	sprintf(str, _T("pos:%f%%"), song->playPos);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// frequency
	rect.top += 20;
	sprintf(str, _T("frequency:%d"), song->frequency);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// db
	rect.top += 20;
	sprintf(str, _T("db:%ld"), song->balanceVolume);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �Ȗ�
	rect.top += 20;
	sprintf(str, _T("name:%s"), GetSoundPath());
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �}�E�X���W
	rect.top += 20;
	sprintf(str, _T("mousePos:%f,%f"), (float)GetMousePos(hWnd).x, (float)GetMousePos(hWnd).y);
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �}�E�XPress���W
	rect.top += 20;
	sprintf(str, _T("mousePressPos:%f"), (float)GetMouseX());
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// GetCurrentPosition-------write
	rect.top += 20;
	sprintf(str, _T("write:%f"), (float)GetSoundCurrentPosition(song->soundBuffer, GET_WRITE));
	g_pD3DXPlayerDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif
