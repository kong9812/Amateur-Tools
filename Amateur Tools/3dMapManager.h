//=============================================================================
//
// �}�b�v�̃}�l�[�W���[���� [3dMapManager.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _3D_MAP_MANAGER_H_
#define _3D_MAP_MANAGER_H_


//=============================================================================
// �}�N����`
//=============================================================================
// �n��(01)
#define FIELD_01_POS		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// ���W
#define FIELD_01_ROT		D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// ��]
#define FIELD_01_X_MAX		(4)									// �u���b�N�̐�(X)
#define FIELD_01_Z_MAX		(4)									// �u���b�N�̐�(Z)
#define FILED_01_SIZE_X		(100.0f)							// �u���b�N�̃T�C�Y(X)
#define FILED_01_SIZE_Z		(100.0f)							// �u���b�N�̃T�C�Y(Z)

// ��(�O)
#define WALL_01_POS			D3DXVECTOR3(0.0f, 0.0f, 200.0f)		// ���W
#define WALL_01_ROT			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// ��]
#define WALL_01_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// �F
#define WALL_01_X_MAX		(40)								// �u���b�N�̐�(X)
#define WALL_01_Y_MAX		(5)									// �u���b�N�̐�(Y)
#define WALL_01_SIZE_X		(10.0f)								// �u���b�N�̃T�C�Y(X)
#define WALL_01_SIZE_Y		(10.0f)								// �u���b�N�̃T�C�Y(Y)

// ��(��)
#define WALL_02_POS			D3DXVECTOR3(0.0f, 0.0f, -200.0f)	// ���W
#define WALL_02_ROT			D3DXVECTOR3(0.0f, 0.0f, 0.0f)		// ��]
#define WALL_02_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// �F
#define WALL_02_X_MAX		(40)								// �u���b�N�̐�(X)
#define WALL_02_Y_MAX		(5)									// �u���b�N�̐�(Y)
#define WALL_02_SIZE_X		(10.0f)								// �u���b�N�̃T�C�Y(X)
#define WALL_02_SIZE_Y		(10.0f)								// �u���b�N�̃T�C�Y(Y)

// ��(��)
#define WALL_03_POS			D3DXVECTOR3(-200.0f, 0.0f, 0.0f)	// ���W
#define WALL_03_ROT			D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f)	// ��]
#define WALL_03_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// �F
#define WALL_03_X_MAX		(40)								// �u���b�N�̐�(X)
#define WALL_03_Y_MAX		(5)									// �u���b�N�̐�(Y)
#define WALL_03_SIZE_X		(10.0f)								// �u���b�N�̃T�C�Y(X)
#define WALL_03_SIZE_Y		(10.0f)								// �u���b�N�̃T�C�Y(Y)

// ��(�E)
#define WALL_04_POS			D3DXVECTOR3(200.0f, 0.0f, 0.0f)		// ���W
#define WALL_04_ROT			D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f)	// ��]
#define WALL_04_COLOR		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// �F
#define WALL_04_X_MAX		(40)								// �u���b�N�̐�(X)
#define WALL_04_Y_MAX		(5)									// �u���b�N�̐�(Y)
#define WALL_04_SIZE_X		(10.0f)								// �u���b�N�̃T�C�Y(X)
#define WALL_04_SIZE_Y		(10.0f)								// �u���b�N�̃T�C�Y(Y)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init3dMapManager(int InitType);	// ����������
void Uninit3dMapManager(void);			// �I������
void Update3dMapManager(void);			// �X�V����
void Draw3dMapManager(void);			// �`�揈��

#endif