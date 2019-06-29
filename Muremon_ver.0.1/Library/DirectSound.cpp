//---------------------------------------------
//
//      �T�E���h�̐ݒ�
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#include "DirectSound.h"

C_DSound::C_DSound()
{
	maxSou = 0;
}

//DirectSound�̏�����
bool C_DSound::InitDSound(HWND hWnd)
{
	//IDirectSound8�C���^�[�t�F�C�X�̎擾
	if(FAILED(DirectSoundCreate8(NULL,&pDSound, NULL)))
	{
		return false;
	}
	//�������x���̐ݒ�
	if(FAILED(pDSound->SetCooperativeLevel(hWnd,DSSCL_PRIORITY)))
	{
		return false;
	}
	//�v���C�}���o�b�t�@�̍쐬
	if(!CreatePriBuffer())
	{
		return false;
	}

	return true;
}

//�J������
void C_DSound::UnInitDSound()
{
	for(short i = 0 ; i < (short)maxSou ; i++)
	{
		SoundStop(true, i);
		SAFE_RELEASE(pDSBuffer[i]);
	}
	SAFE_RELEASE(pDSPrimary);
	SAFE_RELEASE(pDSound);
}

//���y�f�[�^�ǂݍ���
bool C_DSound::LoadSoundData(LPTSTR FileName)
{
	FILE *fp;					//�t�@�C���|�C���^
	char countFile[128];		//�J�E���g+�ǂݍ��ݗp
	fopen_s(&fp, FileName,"r");	//�t�@�C���I�[�v��

	//�G���[����
	if(fp == NULL){
		MessageBox(NULL,TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	//�t�@�C���̒��g���J�E���g
	while(fscanf_s(fp,"%s\n",countFile,sizeof(countFile)) != EOF)
	{
		maxSou++;	//�t�@�C�������J�E���g
	}

	//�ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp,0,SEEK_SET);

	//�ǂݍ��ݏ���
	for(int i = 0;i < maxSou;i++){
		fscanf_s(fp,"%s\n",countFile,sizeof(countFile));
		LoadSound(countFile,i);
	}

	//�G���[����
	if(fclose(fp)){
		MessageBox(NULL,TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}
	return true;
}

//���y�f�[�^�ǂݍ���
HRESULT C_DSound::LoadSound(LPTSTR pFileName, short ID)
{
	if(ID >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("�o�^���悤�Ƃ��Ă���h�c���傫�����܂�"), NULL, MB_OK);
		return E_FAIL;
	}

	HMMIO			hmmio = NULL;
	MMCKINFO		ckInfo;
	WAVEFORMATEX	wfex;

	//WAVE�t�@�C�����̃w�b�_���̊m�F�Ɠǂݍ���
	hmmio = mmioOpen(pFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

	//RIFF�t�@�C���̃`�����N�̐擪�ɐi��
	if(mmioDescend(hmmio, &ckInfo, NULL, 0) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("�`�����N�ւ̐i�����s[RIFF]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//�`�����N�̌���
	if(ckInfo.ckid != FOURCC_RIFF || ckInfo.fccType != mmioFOURCC('W','A','V','E'))
	{
		MessageBox(NULL,TEXT("�����ł��܂���ł���[RIFF][WAVE]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//�t�H�[�}�b�g�`�����N�̌���
	ckInfo.ckid = mmioFOURCC('f','m','t',' ');
	if(mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("�����ł��܂���ł���[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//�t�H�[�}�b�g�̓ǂݍ���
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	if(mmioRead(hmmio, (HPSTR)&wfex, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))
	{
		MessageBox(NULL,TEXT("�ǂݍ��ݎ��s[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//�`�����N����ޏo
	if(mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("�`�����N����̑ޏo�Ɏ��s���܂���[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//�f�[�^�`�����N�̌���
	ckInfo.ckid = mmioFOURCC('d','a','t','a');
	if(mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("�����ł��܂���ł���[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//�f�[�^�̓ǂݍ���
	char	*lpBuffer = new char[ckInfo.cksize];
	if(mmioRead(hmmio, lpBuffer, ckInfo.cksize) != (LONG)ckInfo.cksize)
	{
		MessageBox(NULL,TEXT("�ǂݍ��ݎ��s[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		SAFE_DELETE_ARRAY(lpBuffer);		//�O�̂���
		return E_FAIL;
	}
	//�`�����N����ޏo
	if(mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("�`�����N����̑ޏo�Ɏ��s���܂���[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		SAFE_DELETE_ARRAY(lpBuffer);		//�O�̂���
		return E_FAIL;
	}
	if(FAILED(CreateSecBuffer(wfex, lpBuffer, ckInfo.cksize, ID)))
	{
		MessageBox(NULL,TEXT("�Z�J���_���o�b�t�@�쐬���s"),TEXT("DSound"),MB_OK);
		return E_FAIL;
	}
	//WAVE�t�@�C�������
	mmioClose(hmmio, 0);

	return S_OK;
}

//���y�Đ�
void C_DSound::SoundPlay(bool loop, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}
	if(SoundPlayCheck(ID))
	{
		return;
	}

	if(pDSBuffer[ID])
	{
		pDSBuffer[ID]->Play(0, 0, DSBPLAY_LOOPING & loop);
	}
}

//���y��~
void C_DSound::SoundStop(bool ResetFlg, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}

	if(pDSBuffer[ID])
	{
		pDSBuffer[ID]->Stop();
		if(ResetFlg)
		{
			//�ŏ��ɖ߂�
			pDSBuffer[ID]->SetCurrentPosition(0);
		}
	}
}

//���y�̍Đ���Ԃ̊m�F
bool C_DSound::SoundPlayCheck(short ID)
{
	if(ID >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("�h�c���傫�����܂�"), NULL, MB_OK);
		return false;
	}
	if(!pDSBuffer[ID])
	{
		return false;
	}

	DWORD state;
	pDSBuffer[ID]->GetStatus(&state);

	return (state & DSBSTATUS_PLAYING);
}

//�{�����[���`�F���W
void C_DSound::VolumeChange(short volume, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}
	if(!pDSBuffer[ID])
	{
		return;
	}

	if(volume > 0)
	{
		volume = DSBVOLUME_MAX;
	}
	else if(volume < -10000)
	{
		volume = DSBVOLUME_MIN;
	}
	pDSBuffer[ID]->SetVolume(volume);
}

//�v���C�}���o�b�t�@�쐬
bool C_DSound::CreatePriBuffer()
{
	//DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	//�v���C�}���o�b�t�@���w��
	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= 0;
	dsbd.lpwfxFormat	= NULL;
	//�o�b�t�@�̍쐬
	if(FAILED(pDSound->CreateSoundBuffer(&dsbd, &pDSPrimary, NULL)))
	{
		MessageBox(NULL,TEXT("�o�b�t�@�쐬�Ɏ��s"),TEXT("DSound"),MB_OK);
		return false;
	}
	//�v���C�}���o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag		= WAVE_FORMAT_PCM;		//WAVE�t�H�[�}�b�g�̎��
	wfex.nChannels		= CHANNELS;				//�`�����l����			�X�e���I
	wfex.nSamplesPerSec	= SAMPLESPERSEC;		//�T���v�����O���[�g	44.1kHz
	wfex.wBitsPerSample	= BITSPERSAMPLE;		//16�r�b�g
	wfex.nBlockAlign	= (wfex.nChannels * wfex.wBitsPerSample) / 8;		//�u���b�N�E�A���C�����g(�o�C�g������̃r�b�g��)
	wfex.nAvgBytesPerSec= wfex.nSamplesPerSec * wfex.nBlockAlign;			//�P�b�Ԃɓ]������o�C�g��
	
	if(FAILED(pDSPrimary->SetFormat(&wfex)))
	{
		MessageBox(NULL,TEXT("�t�H�[�}�b�g�ݒ莸�s"),TEXT("DSound"),MB_OK);
		return false;
	}
	return true;
}

//�Z�J���_���o�b�t�@�쐬
HRESULT C_DSound::CreateSecBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short ID)
{
	HRESULT				hr;
	DSBUFFERDESC		dsbd;
	LPDIRECTSOUNDBUFFER	pDSBuf;

	//DSBUFFERDESC�\���̂̐ݒ�
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize			= sizeof(dsbd);
	dsbd.dwFlags		= DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
	dsbd.dwBufferBytes	= dwBufferSize;
	dsbd.guid3DAlgorithm= DS3DALG_DEFAULT;
	dsbd.lpwfxFormat	= &wfex;

	//�Z�J���_���o�b�t�@�쐬
	if(SUCCEEDED(hr = pDSound->CreateSoundBuffer(&dsbd, &pDSBuf, NULL)))
	{
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSBuffer[ID]);
		pDSBuf->Release();

		void* lpData;
		DWORD dwSize;
		pDSBuffer[ID]->Lock(0, dwBufferSize, &lpData, &dwSize, NULL, NULL, 0);
		memcpy(lpData, lpBuffer, dwSize);
		pDSBuffer[ID]->Unlock(lpData, dwSize, NULL, 0);
	}
	SAFE_DELETE_ARRAY(lpBuffer);

	return hr;
}
