//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=============================================================================
// �}�N����`
//=============================================================================
// �`���[�g���A�����
#define	TEXTURE_TUTORIAL_SCREEN		_T("data/TEXTURE/tutorialScreen.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(int InitType);	// ����������
void UninitTutorial(void);			// �I������
void UpdateTutorial(void);			// �X�V����
void DrawTutorial(void);			// �`�揈��

#endif