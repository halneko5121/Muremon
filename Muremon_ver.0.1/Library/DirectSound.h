//---------------------------------------------
//      �T�E���h�̐ݒ�
//			�쐬��:����
//---------------------------------------------

#ifndef _DIRECTSOUND_H_
#define _DIRECTSOUND_H_

#include <dsound.h>
#include <stdio.h>

#pragma comment (lib,"dsound.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib, "winmm.lib")

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p);		(p) = NULL;} }

#define CHANNELS		2		// �`�����l����
#define SAMPLESPERSEC	44100	// �T���v�����O���[�g
#define BITSPERSAMPLE	16		// �P�T���v��������̃r�b�g��
#define MAX_SOUND       20      // �ǂݍ��߂�T�E���h�̍ő吔

class C_DSound
{
public:
	static C_DSound* GetInstance();
	static void Create();
	static void Destroy();
	
	C_DSound();

	/*===================================================
		DirectSound�̏�����
		����	�E�B���h�E�n���h��
		�߂�l	true	����������
				false	���s
	=====================================================*/
	bool InitDSound(HWND hWnd);

	/*===================================================
		���y�f�[�^�ǂݍ���
		�����P	�t�@�C����
		�߂�l	true	�ǂݍ��ݐ���
				false	���s
	=====================================================*/
	bool LoadSoundData(LPTSTR FileName);

	/*===================================================
		���y�f�[�^�ǂݍ���
		�����P	�t�@�C����
		�����Q	�o�^����T�E���h��ID
		�߂�l	S_OK	�ǂݍ��ݐ���
				E_FAIL	���s
	=====================================================*/
	HRESULT LoadSound(LPTSTR pFileName, short ID);

	/*===================================================
		���y�Đ�
		�����P	���[�v���邩(true = ���[�v����Afalse = �P�x�����Đ�)
		�����Q	�T�E���h��ID
	=====================================================*/
	void SoundPlay(bool loop, short ID);

	/*===================================================
		���y��~
		�����P	���S��~��(true = ���S��~�Afalse = �ꎞ��~)
		�����Q	�T�E���h��ID
	=====================================================*/
	void SoundStop(bool ResetFlg, short ID);

	/*===================================================
		���y�̍Đ���Ԃ̊m�F
		����	�T�E���h��ID
		�߂�l	true	�Đ���
				false	��~��
	=====================================================*/
	bool SoundPlayCheck(short ID);

	/*===================================================
		�{�����[���`�F���W
		�����P	�ύX�������{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
		�����Q	�T�E���h��ID
	=====================================================*/
	void VolumeChange(short volume, short ID);

	/*===================================================
		�v���C�}���o�b�t�@�̍쐬
		�߂�l	true	�쐬����
				false	���s
	=====================================================*/
	bool CreatePriBuffer();

	/*===================================================
		�Z�J���_���o�b�t�@�̍쐬
		�����P	WAVE�t�@�C���̃t�H�[�}�b�g
		�����Q	�o�b�t�@
		�����R	�o�b�t�@�T�C�Y
		�����S	�T�E���h��ID
		�߂�l	S_OK	�쐬����
				E_FAIL	���s
	=====================================================*/
	HRESULT CreateSecBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short ID);

	/*===================================================
		�J������
	=====================================================*/
	void UnInitDSound();

private:
	static C_DSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// �v���C�}���[�o�b�t�@
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// �Z�J���_���o�b�t�@
	int						mMaxSound;
};

static C_DSound* GetDirectSound() { return C_DSound::GetInstance(); }

#endif//_DIRECTSOUND_H_