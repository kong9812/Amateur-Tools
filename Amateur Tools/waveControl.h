//=============================================================================
//
// �g�ϊ��̃R���g���[������ [waveControl.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _WAVE_CONTROL_H_
#define _WAVE_CONTROL_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �g�`
#define TEXTURE_WAVE			_T("data/TEXTURE/waveButton/waveButton.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define WAVE_POS				D3DXVECTOR3(640.0f, 410.0f, 0.0f)
#define WAVE_SIZE_X				(500.0f)
#define WAVE_SIZE_Y				(150.0f)

// GNUPLOT�̎c���R�}���h
#define GNUPLOT_PRESIST			" -persist"

// �����p�X����Z�[�u�t�H���_�܂ł̃p�X
#define SAVE_PATH				"\\data\\GNUPLOT"

// �F
#define SELECT_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,0.5f)
#define NO_SELECT_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
// �I�[�o�[�t���[�h�~(16bit�����t���ŕ\���ł���͈�)
#define WAVE_16_BIT_MAX			(32768.0)

//*****************************************************************************
// �萔��`
//*****************************************************************************
enum WAVE_TYPE
{	// �g�̎�ޗp�t���O
	WAVE_NOTHING,	// �������
	WAVE_WAVE,		// �g
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct			// ���f�[�^�̕��͗p�\����(���m)
{
	int sf;				// Sampling frequency(�T���v�����O���g��)
	int precision;		// Quantization precision(�ʎq�����x) �P��:bits
	int length;			// ����
	double *soundData;	// �T�E���h�f�[�^
} MONO_DATA;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitWaveControl(int InitType);	// ����������
void UninitWaveControl(void);			// �I������
void UpdateWaveControl(HWND hWnd);		// �X�V����
void DrawWaveControl(void);				// �`�揈��



#endif