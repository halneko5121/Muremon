#pragma once 
/******************************************************************
 *	@file	DirectSound.h
 *	@brief	�T�E���h�̊Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include <dsound.h>

#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

class DirectSound
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	DirectSound();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~DirectSound();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static DirectSound* GetInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void Create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void Destroy();

	/**
	 * @brief	������
	 * @param	window_handle    �E�B���h�E�n���h��
	 * @return	true:����   false:���s
	 */
	bool InitDSound(HWND window_handle);

	/**
	 * @brief	�J������
	 */
	void UnInitDSound();

	/**
	 * @brief	���y�f�[�^�ǂݍ���
	 * @param	file_name	�t�@�C����
	 * @return	true:����   false:���s
	 */
	bool LoadSoundData(LPTSTR file_name);

	/**
	 * @brief	���y�f�[�^�ǂݍ���
	 * @param	file_name	�t�@�C����
	 * @param	id			�o�^����T�E���h��ID
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT LoadSound(LPTSTR file_name, short id);

	/**
	 * @brief	�����X�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void SoundPlayOnce(short id);

	/**
	 * @brief	���[�v�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void SoundPlayLoop(short id);

	/**
	 * @brief	�ꎞ��~
	 * @param	id			�T�E���h��ID
	 */
	void SoundPouse(short id);

	/**
	 * @brief	��~
	 * @param	id			�T�E���h��ID
	 */
	void SoundStop(short id);

	/**
	 * @brief	�w��ID�̃T�E���h���Đ�����
	 */
	bool IsPlaySound(short id);

	/**
	 * @brief	�{�����[���ݒ�
	 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
	 * @param	id			�T�E���h��ID
	 */
	void SetVolume(short volume, short id);

private:
	/**
	 * @brief	�v���C�}���o�b�t�@�̍쐬
	 * @return	true:����   false:���s
	 */
	bool CreatePrimaryBuffer();

	/**
	 * @brief	�Z�J���_���o�b�t�@�̍쐬
	 * @param	wfex			WAVE�t�@�C���̃t�H�[�}�b�g
	 * @param	lpBuffer		�o�b�t�@
	 * @param	dwBufferSize	�o�b�t�@�T�C�Y
	 * @param	id				�T�E���hID
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT CreateSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short id);

	/**
	 * @brief	�Đ�
	 * @param	loop	���[�v���邩
	 * @param	id		�T�E���h��ID
	 */
	void SoundPlayImple(bool loop, short id);

	/**
	 * @brief	��~
	 * @param	is_pouse	�ꎞ��~��
	 * @param	id			�T�E���h��ID
	 */
	void SoundStopImple(bool is_pouse, short id);

private:
	enum { MAX_SOUND = 20 };								// �ǂݍ��߂�T�E���h�̍ő吔

private:
	static DirectSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// �v���C�}���[�o�b�t�@
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// �Z�J���_���o�b�t�@
	int						mMaxSound;
};

static DirectSound* GetDirectSound() { return DirectSound::GetInstance(); }