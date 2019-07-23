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
	virtual ~GameInfoMgr();

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

	/**
	 * @brief	�e��L�[���͐��̏��
	 */
	void					setWeakAtkCount(int count);
	int						getWeakAtkCount() const;

	void					setMediumAtkCount(int count);
	int						getMediumAtkCount() const;

	void					setStrongAtkCount(int count);
	int						getStrongAtkCount() const;

	// �Q�[�����[�h
	void					setGameModeRefresh();
	void					setGameModeNormal();
	bool					isGameModeRefresh() const;
	bool					isGameModeNormal() const;

	// �U���͒ቺ
	void					setBadStatusAtkLv(int lv);
	int						getBadStatusAtkLv() const;

private:
	static GameInfoMgr*		mInstance;			// �C���X�^���X
	GameScore*				mScore;				// �X�R�A
	int						mGameMode;			// ���[�h
	int						mWeakAtkCount;		// ��U���i�ɂ��܂�j���s������
	int						mMediumAtkCount;	// ���U���i�g���낤�j���s������
	int						mStrongAtkCount;	// ���U���i�̂��ہj���s������
	int						mBadStatusAtkLv;	// �U���͒ቺ��LV�@@todo: �����ŊǗ��͈Ⴄ�C������
};

static GameInfoMgr* getGameInfoMgr() { return GameInfoMgr::getInstance(); }