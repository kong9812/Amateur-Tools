//=============================================================================
// < SoundPlayer�v���O���� >
// ���m�����X�s�[�J�[�̏��� [monoSpeaker.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _MONO_SPEAKER_H_
#define _MONO_SPEAKER_H_

#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���m�����X�s�[�J�[
#define	MONO_SPEAKER_MODEL		"data/MODEL/monoSpeaker/monoSpeaker.x"	// �ǂݍ��ރ��f����
#define MONO_SPEAKER_POS		D3DXVECTOR3(0.0f, 0.0f, 100.0f)			// ���W
#define MONO_SPEAKER_ROT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// ��]
#define MONO_SPEAKER_SCL		D3DXVECTOR3(1.0f, 1.0f, 1.0f)			// �X�P�[��
#define MONO_SPEAKER_SIZE		(10)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// ���m�����X�s�[�J�[�\����
{
	LPDIRECTSOUNDBUFFER8	soundBuffer;	// �T�E���h�o�b�t�@
	D3DXVECTOR3				pos;			// ���f���̈ʒu
	D3DXVECTOR3				rot;			// ���f���̌���(��])
	D3DXVECTOR3				scl;			// ���f���̑傫��(�X�P�[��)

	int						reverb;			// �����o�[�u

}MONO_SPEAKER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMonoSpeaker(int initType);
void UninitMonoSpeaker(void);
void UpdateMonoSpeaker(void);
void DrawMonoSpeaker(void);

MONO_SPEAKER *GetMonoSpeaker(void);

#endif 