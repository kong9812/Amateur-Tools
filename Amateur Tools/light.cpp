//=============================================================================
// < Amateur Tools�v���O���� >
// ���f������ [light.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_LIGHT			(5)	// ���C�g�̐�

#define LIGHT00_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT01_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT02_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT03_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define LIGHT04_DIFFUSE		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)

#define LIGHT00_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT01_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT02_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT03_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)
#define LIGHT04_AMBIENT		D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f)

#define LIGHT00_DIRECTON	D3DXVECTOR3(-1.0f, -1.0f, 1.0f)
#define LIGHT01_DIRECTON	D3DXVECTOR3(-1.0f, -1.0f, -1.0f)
#define LIGHT02_DIRECTON	D3DXVECTOR3(1.0f, -1.0f, 1.0f)
#define LIGHT03_DIRECTON	D3DXVECTOR3(1.0f, -1.0f, -1.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetLight(int no, _D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXCOLOR ambient, D3DXVECTOR3 dir);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9			g_aLight[NUM_LIGHT];		// ���C�g���


//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	SetLight(0, D3DLIGHT_DIRECTIONAL, LIGHT00_DIFFUSE, LIGHT00_AMBIENT, LIGHT00_DIRECTON);
	SetLight(1, D3DLIGHT_DIRECTIONAL, LIGHT01_DIFFUSE, LIGHT01_AMBIENT, LIGHT01_DIRECTON);
	SetLight(2, D3DLIGHT_DIRECTIONAL, LIGHT02_DIFFUSE, LIGHT02_AMBIENT, LIGHT02_DIRECTON);
	SetLight(3, D3DLIGHT_DIRECTIONAL, LIGHT03_DIFFUSE, LIGHT03_AMBIENT, LIGHT03_DIRECTON);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g��ݒ肷��
//=============================================================================
void SetLight(int no, _D3DLIGHTTYPE type, D3DXCOLOR diffuse, D3DXCOLOR ambient, D3DXVECTOR3 dir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂��ŃN���A����
	ZeroMemory(&g_aLight[no], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	g_aLight[no].Type = type;

	// ���C�g�̊g�U���̐ݒ�
	g_aLight[no].Diffuse = diffuse;

	// ���C�g�̊����̐ݒ�
	g_aLight[no].Ambient = ambient;

	// ���C�g�̕����̐ݒ�
	vecDir = dir;
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[no].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(no, &g_aLight[no]);

	// ���C�g���g�p�g�p��Ԃ�
	pDevice->LightEnable(no, TRUE);

}


//=============================================================================
// �I������
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLight(void)
{

}

