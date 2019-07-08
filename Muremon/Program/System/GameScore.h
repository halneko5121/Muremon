#pragma once
/******************************************************************
 *	@file	GameScore.h
  *	@brief	スコア
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class GameScore
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	GameScore();

	/**
	 * @brief	デストラクタ
	 */
	~GameScore();

	/**
	 * @brief	インスタンスの取得
	 */
	static GameScore*		getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void				create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void				destroy();

	/**
	 * @brief	スコアの設定
	 */
	void					setScore(int score);

	/**
	 * @brief	スコアの取得
	 */
	int						getScore() const;

	/**
	 * @brief	スコアの加算
	 */
	void					addScore(int add_score);

	/**
	 * @brief	スコアの減算
	 */
	void					mulScore(int mul_score);

private:
	static GameScore*		mInstance;		// インスタンス
	int						mScore;			// スコア
};

static GameScore* GetGameScore() { return GameScore::getInstance(); }