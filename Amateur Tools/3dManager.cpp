//=============================================================================
// < Amateur Tools�v���O���� >
// 3D�̃}�l�[�W���[���� [3dManager.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "light.h"
#include "sound.h"
#include "camera.h"
#include "listener.h"
#include "reverb.h"
#include "monoSpeaker.h"
#include "3dMapManager.h"
#include "3dManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//------------�`�揈��
void Draw3dDebugFont(HWND hWnd);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
#ifdef _DEBUG
LPD3DXFONT		g_pD3DX3dDebugFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT Init3dManager(int InitType)
{
	// ���C�g
	InitLight();

	// �J����
	InitCamera();

	// �}�b�v
	Init3dMapManager(InitType);

	// ���X�i�[
	InitListener();

	// �����o�[�u
	InitReverb(InitType);

#ifdef _DEBUG
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(GetDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DX3dDebugFont);
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit3dManager(void)
{
	// ���C�g
	UninitLight();

	// �J����
	UninitCamera();
	
	// �}�b�v
	Uninit3dMapManager();

	// �����o�[�u
	UninitReverb();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update3dManager(HWND hWnd)
{
	// ���C�g
	UpdateLight();

	// �J����
	UpdateCamera();

	// �}�b�v
	Update3dMapManager();

	// ���X�i�[
	UpdateListener();

	// �����o�[�u
	UpdateReverb(hWnd);
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw3dManager(HWND hWnd)
{
	// �J����
	SetCamera();

	// �}�b�v
	Draw3dMapManager();

	// �����o�[�u
	DrawReverb();

#ifdef _DEBUG
	// �f�o�b�O�\��
	Draw3dDebugFont(hWnd);
#endif
}

#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�\������
//=============================================================================
void Draw3dDebugFont(HWND hWnd)
{
	MONO_SPEAKER *monoSpeaker = GetMonoSpeaker();
	LISTENER *listener = GetListener();
	CAMERA *camera = GetCamera();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[CHAR_MAX];

	// ���X�i�[���W
	rect.top += 20;
	sprintf(str, _T("Listener pos:%f,%f,%f"), listener->pos.x, listener->pos.y, listener->pos.z);
	g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ���X�i�[��]
	rect.top += 20;
	sprintf(str, _T("Listener rot:%f,%f,%f"), listener->rot.x, listener->rot.y, listener->rot.z);
	g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ��
	rect.top += 20;
	sprintf(str, _T("Ear rot:%f,%f,%f"), listener->earRot.x, listener->earRot.y, listener->earRot.z);
	g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �J�������W
	rect.top += 20;
	sprintf(str, _T("Camera pos:%f,%f,%f"), camera->EyePos.x, camera->EyePos.y, camera->EyePos.z);
	g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));	

	// �����o�[�u
	rect.top += 20;
	switch (monoSpeaker->reverb)
	{
	case DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT:
		sprintf(str, _T("DEFAULT"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC:
		sprintf(str, _T("GENERIC"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL:
		sprintf(str, _T("PADDEDCELL"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM:
		sprintf(str, _T("ROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM:
		sprintf(str, _T("BATHROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM:
		sprintf(str, _T("LIVINGROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM:
		sprintf(str, _T("STONEROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM:
		sprintf(str, _T("AUDITORIUM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL:
		sprintf(str, _T("CONCERTHALL"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE:
		sprintf(str, _T("CAVE"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA:
		sprintf(str, _T("ARENA"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR:
		sprintf(str, _T("HANGAR"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY:
		sprintf(str, _T("CARPETEDHALLWAY"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY:
		sprintf(str, _T("HALLWAY"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR:
		sprintf(str, _T("STONECORRIDOR"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY:
		sprintf(str, _T("ALLEY"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST:
		sprintf(str, _T("FOREST"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_CITY:
		sprintf(str, _T("CITY"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS:
		sprintf(str, _T("MOUNTAINS"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY:
		sprintf(str, _T("QUARRY"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN:
		sprintf(str, _T("PLAIN"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT:
		sprintf(str, _T("PARKINGLOT"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE:
		sprintf(str, _T("SEWERPIPE"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER:
		sprintf(str, _T("UNDERWATER"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM:
		sprintf(str, _T("SMALLROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM:
		sprintf(str, _T("MEDIUMROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM:
		sprintf(str, _T("LARGEROOM"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL:
		sprintf(str, _T("MEDIUMHALL"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL:
		sprintf(str, _T("LARGEHALL"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	case DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE:
		sprintf(str, _T("PLATE"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	default:
		sprintf(str, _T("error"));
		g_pD3DX3dDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		break;
	}
}
#endif
