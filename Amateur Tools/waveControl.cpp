//=============================================================================
// < Amateur Tools�v���O���� >
// �g�ϊ��̃R���g���[������ [waveControl.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "playerControl.h"
#include "waveControl.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �T�E���h�ǂݍ���
void LoadMonoData(MONO_DATA *monoData);		// ���m�f�[�^�̓ǂݍ���

// �g�`�o��
void OutputWaveGnuplot(void);				// GNUPLOT�̏o��(�g�`)

// �`�揈��
void DrawWaveButton(void);					// GNUPLOT�̏o�̓{�^��(�g�`)

// ��ʑJ��
void SetWaveStage(void);					// ��ʑJ��
				
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
WIN32_FIND_DATA		findGnuplot;			// �t�@�C�����
MONO_DATA			mono_data;				// ���m�f�[�^
char				gnuplotPath[MAX_PATH];	// �t�@�C���̃p�X
int					gnuplotType;			// �g�̎��

TEXTURE				waveButton;			// GNUPLOT�̏o�̓{�^��(�g�`)

float				waveAlpha;			// �{�^���F��alpha�l

//=============================================================================
// GNUPLOT�̓ǂݍ���
//=============================================================================
bool OpenGnuplot(HWND hWnd)
{
	OPENFILENAME ofn;

	gnuplotPath[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));		//�\���̂�0�ŃN���A
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrInitialDir = "C:\\gnuplot\\bin";	// �e�X�g�pPC��GNUPLOT�p�X( �Ȃ��Ă����v @_@ )
	ofn.lpstrFilter = "gnuplot(*.exe)\0*.exe\0\0";
	ofn.lpstrFile = gnuplotPath;
	ofn.nMaxFile = sizeof(gnuplotPath);
	ofn.lpstrDefExt = "exe";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// �t�@�C���������o��
	FindFirstFile(ofn.lpstrFile, &findGnuplot);

	return TRUE;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT InitWaveControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WAVE,					// �t�@�C���̖��O
		&waveButton.texture);			// �ǂݍ��ރ������[

	}

	// �F�̏�����
	waveButton.col	= NO_SELECT_COLOR;

	// �g�̎�� 
	gnuplotType = WAVE_NOTHING;

	// ���_���̓ǂݍ���
	MakeVtxCenterData(waveButton.vertexWk, WAVE_POS, WAVE_SIZE_X, WAVE_SIZE_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWaveControl(void)
{
	if (waveButton.texture != NULL)
	{// �e�N�X�`���̊J��	
		waveButton.texture->Release();
		waveButton.texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWaveControl(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();
	char lpMsgBuf[CHAR_MAX] = "GNUPLOT�̃p�X���擾�ł��܂���";	// �G���[���b�Z�[�W

	// �g�`
	if (gnuplotType == WAVE_NOTHING)
	{
		if (CheckHitBB(GetMousePos(hWnd), WAVE_POS, CURSOR_SIZE, D3DXVECTOR2(WAVE_SIZE_X * 2, WAVE_SIZE_Y * 2)))
		{
			waveButton.col = SELECT_COLOR;

			if (IsMouseLeftTriggered() == true)
			{
				gnuplotType = WAVE_WAVE;

				if (!OpenGnuplot(hWnd))
				{
					// �G���[���b�Z�[�W
					MessageBox(hWnd, (LPCTSTR)lpMsgBuf, _TEXT("�G���["), MB_OK | MB_ICONINFORMATION);

					// �������[�v�ɂȂ�Ȃ��悤��
					gnuplotType = WAVE_NOTHING;
				}

				// �ꎞ��~
				StopSound(song->soundBuffer);

				// �o��
				OutputWaveGnuplot();

				// �������[�v�ɂȂ�Ȃ��悤��
				gnuplotType = WAVE_NOTHING;
			}
		}

		else
		{
			waveButton.col = NO_SELECT_COLOR;
		}
	}

	// ��ʑJ��
	SetWaveStage();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWaveControl(void)
{
	DrawWaveButton();	// �g�`
}

//=============================================================================
// �`�揈��(GNUPLOT�̏o�̓{�^��----�g�`)
//=============================================================================
void DrawWaveButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, waveButton.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(waveButton.vertexWk, waveButton.col);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &waveButton.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���m�f�[�^�̓ǂݍ���
//=============================================================================
void LoadMonoData(MONO_DATA *monoData)
{
	FILE  *soundFile;				// �t�@�C���ǂݍ��ݗp
	char  riffID[4];				// RIFF�w�b�_
	long  riffSize;					// RIFF�ȍ~�̃t�@�C���T�C�Y
	char  riffType[4];				// RIFF�̎��(WAVE�w�b�_)
	char  fmtID[4];					// �t�H�[�}�b�g�̒�`
	long  fmtSize;					// fmt �`�����N�̃o�C�g��
	short fmtFormatID;				// �t�H�[�}�b�gID
	short fmtChannel;				// �`�����l����
	long  fmtSamplesPerSec;			// �T���v�����O���[�g(Hz)
	long  fmtBytesPerSec;			// �f�[�^���x (Byte/sec)
	short fmtBlockSize;				// �u���b�N�T�C�Y (Byte/sample�~�`�����l����)
	short fmtBitsPerSample;			// �T���v��������̃r�b�g�� (bit/sample)	
	char  dataID[4];				// data �`�����N 	
	long  dataSize;					// �g�`�f�[�^�̃o�C�g��
	short soundData;				// ���̃f�[�^

	// �t�@�C���̓ǂݍ���
	soundFile = fopen(GetSoundPath(), "rb");
	fread(riffID, 1, 4, soundFile);
	fread(&riffSize, 4, 1, soundFile);
	fread(riffType, 1, 4, soundFile);
	fread(fmtID, 1, 4, soundFile);
	fread(&fmtSize, 4, 1, soundFile);
	fread(&fmtFormatID, 2, 1, soundFile);
	fread(&fmtChannel, 2, 1, soundFile);
	fread(&fmtSamplesPerSec, 4, 1, soundFile);
	fread(&fmtBytesPerSec, 4, 1, soundFile);
	fread(&fmtBlockSize, 2, 1, soundFile);
	fread(&fmtBitsPerSample, 2, 1, soundFile);
	fread(dataID, 1, 4, soundFile);
	fread(&dataSize, 4, 1, soundFile);

	monoData->sf			= fmtSamplesPerSec;
	monoData->precision		= fmtBitsPerSample;
	monoData->length		= dataSize / HALF;
	monoData->soundData		= (double *)calloc(monoData->length, sizeof(double));

	// �f�[�^���擾
	for (int i = 0; i < monoData->length; i++)
	{
		fread(&soundData, 2, 1, soundFile);
		monoData->soundData[i] = (double)soundData / WAVE_16_BIT_MAX;
	}

	// �t�@�C�������
	fclose(soundFile);
}

//=============================================================================
// �g�` (GNUPLOT)
// �c��:����(? �U��(? �d��(? ���̑傫��(? 
// ����:����(�o�C�g)
//=============================================================================
void OutputWaveGnuplot(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	FILE *gnuplot;				// GNUPLOT
	double max;					// �ő�l
	double min;					// �ŏ��l
	double x, y;				// GNUPLOT���̍��W
	char savePath[MAX_PATH];	// PNG��ۑ�����ꏊ

	// �p�X�ƃR�}���h������
	strcat(gnuplotPath, GNUPLOT_PRESIST);

	// �Z�[�u�p�X�Ə����p�X������
	strcpy(savePath, GetOldPath());
	
	// �Z�[�u�p�X�ƃZ�[�u�t�H���_�p�X������
	strcat(savePath, SAVE_PATH);

	// ���m�f�[�^�̓ǂݍ���
	LoadMonoData(&mono_data);

	// �ő�l�ƍŏ��l
	min = max = mono_data.soundData[0];
	for (int i = 0; i < mono_data.length; i++)
	{
		if (mono_data.soundData[i] < min) min = mono_data.soundData[i];
		if (mono_data.soundData[i] > max) max = mono_data.soundData[i];
	}

	// �O���t
	gnuplot = _popen(gnuplotPath, "w");										// GNUPLOT���������݃��[�h�ŊJ��
	fprintf(gnuplot, "set title \"wave \" \n");								// �^�C�g���̐ݒ�
	fprintf(gnuplot, "set xrange [0:%d]\n", mono_data.length);				// x�͈̔�
	fprintf(gnuplot, "set yrange [%f:%f]\n", min, max);						// y�͈̔�
	fprintf(gnuplot, "set terminal png\n");									// �摜�o�͂̏���
	fprintf(gnuplot, "set term png size 1000,500\n");						// �摜�̃T�C�Y
	fprintf(gnuplot, "plot '-' with lines linetype 1 title \"wave\"\n");	// �v���b�g

	for (int i = 0; i < mono_data.length; i++)
	{
		x = i;
		y = mono_data.soundData[i];
		fprintf(gnuplot, "%f\t%f\n", x, y);
	}
	fprintf(gnuplot, "e\n");

	fprintf(gnuplot, "set output '%s\\\\Wave.png'\n", savePath);	
	fprintf(gnuplot, "replot '%s\\\\Data.txt'using 1:2 w l title 'OutputData' lw 2\n", savePath); 	// �e�L�X�g�f�[�^�̃v���b�g	
	fprintf(gnuplot, "set output\n");

	// GNUPLOT�̉�ʂ����
	_pclose(gnuplot);

	// ���
	free(mono_data.soundData);

	// �Z�[�u�p�X�ƃt�@�C����������
	strcat(savePath, "\\Wave.png");

	// �e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
	savePath,							// �t�@�C���̖��O
	&waveButton.texture);				// �ǂݍ��ރ������[

}

//=============================================================================
// ��ʑJ��
//=============================================================================
void SetWaveStage(void)
{
	// �v���C���[
	if (GetKeyboardTrigger(DIK_1))
	{
		SetStage(STAGE_PLAYER);
	}

	// 3D
	else if (GetKeyboardTrigger(DIK_3))
	{
		SetStage(STAGE_3D);
	}
}
