#pragma once
/******************************************************************
 *	@file	GameScore.h
  *	@brief	�X�R�A
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class GameScore
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	GameScore();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~GameScore();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static GameScore*		getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				destroy();

	/**
	 * @brief	�X�R�A�̐ݒ�
	 */
	void					setScore(int score);

	/**
	 * @brief	�X�R�A�̎擾
	 */
	int						getScore() const;

	/**
	 * @brief	�X�R�A�̉��Z
	 */
	void					addScore(int add_score);

	/**
	 * @brief	�X�R�A�̌��Z
	 */
	void					mulScore(int mul_score);

private:
	static GameScore*		mInstance;		// �C���X�^���X
	int						mScore;			// �X�R�A
};

static GameScore* GetGameScore() { return GameScore::getInstance(); }