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
	 * @brief	���y�f�[�^�ǂݍ���
	 * @param	file_name	�t�@�C����
	 * @return	true:����   false:���s
	 */
	bool					load(LPTSTR file_name);

	/**
	 * @brief	�����X�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void					playOnce(int id);

	/**
	 * @brief	���[�v�Đ�
	 * @param	id		�T�E���h��ID
	 */
	void					playLoop(int id);

	/**
	 * @brief	�ꎞ��~
	 * @param	id			�T�E���h��ID
	 */
	void					pause(int id);

	/**
	 * @brief	��~
	 * @param	id			�T�E���h��ID
	 */
	void					stop(int id);

	/**
	 * @brief	�w��ID�̃T�E���h���Đ�����
	 */
	bool					isPlaying(int id) const;

	/**
	 * @brief	�{�����[���ݒ�
	 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
	 * @param	id			�T�E���h��ID
	 */
	void					setVolume(int volume, int id);

private:
	/**
	 * @brief	�R���X�g���N�^
	 */
	explicit DirectSound();

	/**
	 * @brief	�f�X�g���N�^
	 */
	virtual ~DirectSound();

	/**
	 * @brief	���y�f�[�^�ǂݍ��݁��o�^
	 * @param	file_name	�t�@�C����
	 * @param	id			�o�^����T�E���h��ID
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					loadAndRegist(LPTSTR file_name, int id);

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
	HRESULT					createSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const int id);

	/**
	 * @brief	�Đ�
	 * @param	loop	���[�v���邩
	 * @param	id		�T�E���h��ID
	 */
	void					playImple(bool loop, int id);

	/**
	 * @brief	��~
	 * @param	is_pouse	�ꎞ��~��
	 * @param	id			�T�E���h��ID
	 */
	void					stopImple(bool is_pouse, int id);

private:
	enum { MAX_SOUND = 20 };								// �ǂݍ��߂�T�E���h�̍ő吔

private:
	static DirectSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// �v���C�}���[�o�b�t�@
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// �Z�J���_���o�b�t�@
	int						mMaxSound;
};

static DirectSound* getDirectSound() { return DirectSound::getInstance(); }
