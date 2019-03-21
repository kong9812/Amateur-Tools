//=============================================================================
// < Amateur Tools�v���O���� >
// 3D�}�b�v�̃}�l�[�W���[���� [3dMapManager.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "meshfield.h"
#include "meshwall.h"
#include "monoSpeaker.h"
#include "3dMapManager.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************


//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT Init3dMapManager(int InitType)
{
	{	// �n��(01)
		InitMeshField	
		(FIELD_01_POS,							// ���W
		FIELD_01_ROT,							// ��]
		FIELD_01_X_MAX, FIELD_01_Z_MAX,			// �u���b�N��(X,Z)
		FILED_01_SIZE_X, FILED_01_SIZE_Z);		// �u���b�N�T�C�Y(X,Z)
	}

	{	// ��(�O)
		InitMeshWall						
		(WALL_01_POS,							// ���W
		WALL_01_ROT,							// ��]
		WALL_01_COLOR,							// �F
		WALL_01_X_MAX, WALL_01_Y_MAX, 			// �u���b�N��(X,Y)
		WALL_01_SIZE_X, WALL_01_SIZE_Y);		// �u���b�N�T�C�Y(X,Y)
	}

	{	// ��(��)
		InitMeshWall
		(WALL_02_POS,							// ���W
		WALL_02_ROT,							// ��]
		WALL_02_COLOR,							// �F
		WALL_02_X_MAX, WALL_02_Y_MAX, 			// �u���b�N��(X,Y)
		WALL_02_SIZE_X, WALL_02_SIZE_Y);		// �u���b�N�T�C�Y(X,Y)
	}

	{	// ��(��)
		InitMeshWall
		(WALL_03_POS,							// ���W
		WALL_03_ROT,							// ��]
		WALL_03_COLOR,							// �F
		WALL_03_X_MAX, WALL_03_Y_MAX, 			// �u���b�N��(X,Y)
		WALL_03_SIZE_X, WALL_03_SIZE_Y);		// �u���b�N�T�C�Y(X,Y)
	}

	{	// ��(��)
		InitMeshWall
		(WALL_04_POS,							// ���W
		WALL_04_ROT,							// ��]
		WALL_04_COLOR,							// �F
		WALL_04_X_MAX, WALL_04_Y_MAX, 			// �u���b�N��(X,Y)
		WALL_04_SIZE_X, WALL_04_SIZE_Y);		// �u���b�N�T�C�Y(X,Y)
	}

	// ���m�����X�s�[�J�[
	InitMonoSpeaker(InitType);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit3dMapManager(void)
{
	{	// �n��
		UninitMeshField();
	}

	{	// ��
		UninitMeshWall();
	}

	// ���m�����X�s�[�J�[
	UninitMonoSpeaker();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update3dMapManager(void)
{
	{	// �n��
		UpdateMeshField();
	}

	{	// ��
		UpdateMeshWall();
	}

	// ���m�����X�s�[�J�[
	UpdateMonoSpeaker();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw3dMapManager(void)
{
	{	// �n��
		DrawMeshField();
	}

	{	// ��
		DrawMeshWall();
	}

	// ���m�����X�s�[�J�[
	DrawMonoSpeaker();
}
