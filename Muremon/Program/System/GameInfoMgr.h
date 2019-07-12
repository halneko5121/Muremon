#pragma once
/******************************************************************
 *	@file	GameInfoMgr.h
  *	@brief	�Q�[�������Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class GameScore;

class GameInfoMgr
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	GameInfoMgr();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~GameInfoMgr();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static GameInfoMgr*		getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				destroy();

	/**
	 * @brief	�X�R�A�N���X�̎擾
	 */
	GameScore*				getGameScore() const;

private:
	static GameInfoMgr*		mInstance;		// �C���X�^���X
	GameScore*				mScore;			// �X�R�A
};

static GameInfoMgr* GetGameInfoMgr() { return GameInfoMgr::getInstance(); }