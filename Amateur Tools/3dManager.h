//=============================================================================
//
// 3D�̃}�l�[�W���[���� [3dManager.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _3D_MANAGER_H_
#define _3D_MANAGER_H_


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================





//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init3dManager(int InitType);	// ����������
void Uninit3dManager(void);				// �I������
void Update3dManager(HWND hWnd);		// �X�V����
void Draw3dManager(HWND hWnd);			// �`�揈��

#endif