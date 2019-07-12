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
	 * @brief	�C���X�^���X�̎擾
	 */
	static DirectSound*		getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				destroy();

	/**
	 * @brief	������
	 * @param	window_handle    �E�B���h�E�n���h��
	 * @return	true:����   false:���s
	 */
	bool					init(HWND window_handle);

	/**
	 * @brief	�J������
	 */
	void					release();

	/**
	 * @brief	���y�f�[�^�ǂݍ���
	 * @param	file_name	�t�@�C����
	 * @return	true:����   false:���s
	 */
	bool					load(LPTSTR file_name);

	/**
	 * @brief	�����X�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void					playOnce(short id);

	/**
	 * @brief	���[�v�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void					playLoop(short id);

	/**
	 * @brief	�ꎞ��~
	 * @param	id			�T�E���h��ID
	 */
	void					pause(short id);

	/**
	 * @brief	��~
	 * @param	id			�T�E���h��ID
	 */
	void					stop(short id);

	/**
	 * @brief	�w��ID�̃T�E���h���Đ�����
	 */
	bool					isPlaying(short id) const;

	/**
	 * @brief	�{�����[���ݒ�
	 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
	 * @param	id			�T�E���h��ID
	 */
	void					setVolume(short volume, short id);

private:
	/**
	 * @brief	�R���X�g���N�^
	 */
	DirectSound();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~DirectSound();

	/**
	 * @brief	���y�f�[�^�ǂݍ��݁��o�^
	 * @param	file_name	�t�@�C����
	 * @param	id			�o�^����T�E���h��ID
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					loadAndRegist(LPTSTR file_name, short id);

	/**
	 * @brief	�v���C�}���o�b�t�@�̍쐬
	 * @return	true:����   false:���s
	 */
	bool					createPrimaryBuffer();

	/**
	 * @brief	�Z�J���_���o�b�t�@�̍쐬
	 * @param	wfex			WAVE�t�@�C���̃t�H�[�}�b�g
	 * @param	lpBuffer		�o�b�t�@
	 * @param	dwBufferSize	�o�b�t�@�T�C�Y
	 * @param	id				�T�E���hID
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					createSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short id);

	/**
	 * @brief	�Đ�
	 * @param	loop	���[�v���邩
	 * @param	id		�T�E���h��ID
	 */
	void					playImple(bool loop, short id);

	/**
	 * @brief	��~
	 * @param	is_pouse	�ꎞ��~��
	 * @param	id			�T�E���h��ID
	 */
	void					stopImple(bool is_pouse, short id);

private:
	enum { MAX_SOUND = 20 };								// �ǂݍ��߂�T�E���h�̍ő吔

private:
	static DirectSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// �v���C�}���[�o�b�t�@
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// �Z�J���_���o�b�t�@
	int						mMaxSound;
};

static DirectSound* GetDirectSound() { return DirectSound::getInstance(); }
