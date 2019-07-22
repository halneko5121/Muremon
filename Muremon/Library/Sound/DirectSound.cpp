/******************************************************************
 *	@file	DirectSound.cpp
 *	@brief	�T�E���h�̊Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "DirectSound.h"

#define CHANNELS		2		// �`�����l����
#define SAMPLESPERSEC	44100	// �T���v�����O���[�g
#define BITSPERSAMPLE	16		// �P�T���v��������̃r�b�g��

DirectSound* DirectSound::mInstance = nullptr;

/**
 * @brief �C���X���^���X�̎擾
 */
DirectSound*
DirectSound::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
DirectSound::create()
{
	mInstance = new DirectSound();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
DirectSound::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	������
 * @param	window_handle    �E�B���h�E�n���h��
 * @return	true:����   false:���s
 */
bool
DirectSound::init(HWND window_handle)
{
	// IDirectSound8�C���^�[�t�F�C�X�̎擾
	if(FAILED(DirectSoundCreate8(NULL,&mDirectSound, NULL)))
	{
		return false;
	}
	// �������x���̐ݒ�
	if(FAILED(mDirectSound->SetCooperativeLevel(window_handle,DSSCL_PRIORITY)))
	{
		return false;
	}
	// �v���C�}���o�b�t�@�̍쐬
	if(!createPrimaryBuffer())
	{
		return false;
	}

	return true;
}

/**
 * @brief	�J������
 */
void
DirectSound::release()
{
	for(int i = 0 ; i < (int)mMaxSound ; i++)
	{
		stop(i);
		SAFE_RELEASE(mSecondaryBuffer[i]);
	}
	SAFE_RELEASE(mPrimaryBuffer);
	SAFE_RELEASE(mDirectSound);
}

/**
 * @brief	���y�f�[�^�ǂݍ���
 * @param	file_name	�t�@�C����
 * @return	true:����   false:���s
 */
bool
DirectSound::load(LPTSTR file_name)
{
	FILE *fp;						// �t�@�C���|�C���^
	char countFile[128];			// �J�E���g+�ǂݍ��ݗp
	fopen_s(&fp, file_name, "r");	// �t�@�C���I�[�v��

	// �G���[����
	if(fp == NULL)
	{
		MessageBox(NULL,TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	// �t�@�C���̒��g���J�E���g
	while(fscanf_s(fp,"%s\n",countFile,sizeof(countFile)) != EOF)
	{
		// �t�@�C�������J�E���g
		mMaxSound++;
	}

	// �ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	// �ǂݍ��ݏ���
	for(int i = 0;i < mMaxSound;i++)
	{
		fscanf_s(fp,"%s\n", countFile, sizeof(countFile));
		loadAndRegist(countFile, i);
	}

	// �G���[����
	if(fclose(fp))
	{
		MessageBox(NULL,TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	return true;
}

/**
 * @brief	�Đ�
 * @param	id		�T�E���h��ID
 */
void
DirectSound::playOnce(int id)
{
	playImple(false, id);
}

/**
 * @brief	���[�v�Đ�
 * @param	id		�T�E���h��ID
 */
void
DirectSound::playLoop(int id)
{
	playImple(true, id);
}

/**
 * @brief	�ꎞ��~
 * @param	id		�T�E���h��ID
 */
void
DirectSound::pause(int id)
{
	stopImple(true, id);
}

/**
 * @brief	��~
 * @param	id		�T�E���h��ID
 */
void
DirectSound::stop(int id)
{
	stopImple(false, id);
}

/**
 * @brief	�w��ID�̃T�E���h���Đ�����
 */
bool
DirectSound::isPlaying(int id) const
{
	if(id >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("ID���傫�����܂�"), NULL, MB_OK);
		return false;
	}
	if(!mSecondaryBuffer[id])
	{
		return false;
	}

	DWORD state;
	mSecondaryBuffer[id]->GetStatus(&state);

	return (state & DSBSTATUS_PLAYING);
}

/**
 * @brief	�{�����[���ݒ�
 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
 * @param	id			�T�E���h��ID
 */
void
DirectSound::setVolume(int volume, int id)
{
	if(id >= MAX_SOUND)
	{
		return;
	}
	if(!mSecondaryBuffer[id])
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
	mSecondaryBuffer[id]->SetVolume(volume);
}

/**
 * @brief	�R���X�g���N�^
 */
DirectSound::DirectSound()
	: mDirectSound(nullptr)
	, mPrimaryBuffer(nullptr)
	, mMaxSound()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
		mSecondaryBuffer[i] = nullptr;
	}
}

/**
 * @brief	�f�X�g���N�^
 */
DirectSound::~DirectSound()
{
}


/**
 * @brief	���y�f�[�^�ǂݍ���
 * @param	file_name	�t�@�C����
 * @param	id			�o�^����T�E���h��ID
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectSound::loadAndRegist(LPTSTR file_name, int id)
{
	if (id >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("�o�^���悤�Ƃ��Ă���ID���傫�����܂�"), NULL, MB_OK);
		return E_FAIL;
	}

	HMMIO			hmmio = NULL;
	MMCKINFO		ckInfo;
	WAVEFORMATEX	wfex;

	// WAVE�t�@�C�����̃w�b�_���̊m�F�Ɠǂݍ���
	hmmio = mmioOpen(file_name, NULL, MMIO_ALLOCBUF | MMIO_READ);

	// RIFF�t�@�C���̃`�����N�̐擪�ɐi��
	if (mmioDescend(hmmio, &ckInfo, NULL, 0) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("�`�����N�ւ̐i�����s[RIFF]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �`�����N�̌���
	if (ckInfo.ckid != FOURCC_RIFF || ckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		MessageBox(NULL, TEXT("�����ł��܂���ł���[RIFF][WAVE]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �t�H�[�}�b�g�`�����N�̌���
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("�����ł��܂���ł���[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �t�H�[�}�b�g�̓ǂݍ���
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	if (mmioRead(hmmio, (HPSTR)&wfex, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))
	{
		MessageBox(NULL, TEXT("�ǂݍ��ݎ��s[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �`�����N����ޏo
	if (mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("�`�����N����̑ޏo�Ɏ��s���܂���[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �f�[�^�`�����N�̌���
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("�����ł��܂���ł���[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// �f�[�^�̓ǂݍ���
	char	*lpBuffer = new char[ckInfo.cksize];
	if (mmioRead(hmmio, lpBuffer, ckInfo.cksize) != (LONG)ckInfo.cksize)
	{
		MessageBox(NULL, TEXT("�ǂݍ��ݎ��s[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		SAFE_DELETE_ARRAY(lpBuffer);		//�O�̂���
		return E_FAIL;
	}

	// �`�����N����ޏo
	if (mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("�`�����N����̑ޏo�Ɏ��s���܂���[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		SAFE_DELETE_ARRAY(lpBuffer);		//�O�̂���
		return E_FAIL;
	}
	if (FAILED(createSecondaryBuffer(wfex, lpBuffer, ckInfo.cksize, id)))
	{
		MessageBox(NULL, TEXT("�Z�J���_���o�b�t�@�쐬���s"), TEXT("DSound"), MB_OK);
		return E_FAIL;
	}

	// WAVE�t�@�C�������
	mmioClose(hmmio, 0);

	return S_OK;
}

/**
 * @brief	�v���C�}���o�b�t�@�̍쐬
 * @return	true:����   false:���s
 */
bool
DirectSound::createPrimaryBuffer()
{
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	// �v���C�}���o�b�t�@���w��
	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= 0;
	dsbd.lpwfxFormat	= NULL;
	// �o�b�t�@�̍쐬
	if(FAILED(mDirectSound->CreateSoundBuffer(&dsbd, &mPrimaryBuffer, NULL)))
	{
		MessageBox(NULL,TEXT("�o�b�t�@�쐬�Ɏ��s"),TEXT("DSound"),MB_OK);
		return false;
	}
	// �v���C�}���o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag		= WAVE_FORMAT_PCM;								// WAVE�t�H�[�}�b�g�̎��
	wfex.nChannels		= CHANNELS;										// �`�����l����			�X�e���I
	wfex.nSamplesPerSec	= SAMPLESPERSEC;								// �T���v�����O���[�g	44.1kHz
	wfex.wBitsPerSample	= BITSPERSAMPLE;								// 16�r�b�g
	wfex.nBlockAlign	= (wfex.nChannels * wfex.wBitsPerSample) / 8;	// �u���b�N�E�A���C�����g(�o�C�g������̃r�b�g��)
	wfex.nAvgBytesPerSec= wfex.nSamplesPerSec * wfex.nBlockAlign;		// �P�b�Ԃɓ]������o�C�g��
	
	if(FAILED(mPrimaryBuffer->SetFormat(&wfex)))
	{
		MessageBox(NULL,TEXT("�t�H�[�}�b�g�ݒ莸�s"),TEXT("DSound"),MB_OK);
		return false;
	}
	return true;
}

/**
 * @brief	�Z�J���_���o�b�t�@�̍쐬
 * @param	wfex			WAVE�t�@�C���̃t�H�[�}�b�g
 * @param	lpBuffer		�o�b�t�@
 * @param	dwBufferSize	�o�b�t�@�T�C�Y
 * @param	id				�T�E���hID
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectSound::createSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const int id)
{
	HRESULT				hr;
	DSBUFFERDESC		dsbd;
	LPDIRECTSOUNDBUFFER	pDSBuf;

	// DSBUFFERDESC�\���̂̐ݒ�
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize			= sizeof(dsbd);
	dsbd.dwFlags		= DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
	dsbd.dwBufferBytes	= dwBufferSize;
	dsbd.guid3DAlgorithm= DS3DALG_DEFAULT;
	dsbd.lpwfxFormat	= &wfex;

	// �Z�J���_���o�b�t�@�쐬
	if(SUCCEEDED(hr = mDirectSound->CreateSoundBuffer(&dsbd, &pDSBuf, NULL)))
	{
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&mSecondaryBuffer[id]);
		pDSBuf->Release();

		void* lpData;
		DWORD dwSize;
		mSecondaryBuffer[id]->Lock(0, dwBufferSize, &lpData, &dwSize, NULL, NULL, 0);
		memcpy(lpData, lpBuffer, dwSize);
		mSecondaryBuffer[id]->Unlock(lpData, dwSize, NULL, 0);
	}
	SAFE_DELETE_ARRAY(lpBuffer);

	return hr;
}

/**
 * @brief	�Đ�
 * @param	loop	���[�v���邩
 * @param	id		�T�E���h��ID
 */
void
DirectSound::playImple(bool loop, int id)
{
	if (id >= MAX_SOUND)
	{
		return;
	}
	if (isPlaying(id))
	{
		return;
	}

	if (mSecondaryBuffer[id])
	{
		mSecondaryBuffer[id]->Play(0, 0, DSBPLAY_LOOPING& loop);
	}
}

/**
 * @brief	��~
 * @param	is_pouse	�ꎞ��~��
 * @param	id			�T�E���h��ID
 */
void
DirectSound::stopImple(bool is_pouse, int id)
{
	if (id >= MAX_SOUND)
	{
		return;
	}

	if (mSecondaryBuffer[id])
	{
		mSecondaryBuffer[id]->Stop();
		if (!is_pouse)
		{
			// �ŏ��ɖ߂�
			mSecondaryBuffer[id]->SetCurrentPosition(0);
		}
	}
}