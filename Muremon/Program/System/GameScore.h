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
	int						mScore;		// �X�R�A
};