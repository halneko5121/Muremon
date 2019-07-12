#pragma once
/******************************************************************
 *	@file	GameInfoMgr.h
  *	@brief	ゲーム情報を管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class GameInfoMgr
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	GameInfoMgr();

	/**
	 * @brief	デストラクタ
	 */
	~GameInfoMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static GameInfoMgr*		getInstance();

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
	static GameInfoMgr*		mInstance;		// インスタンス
};

static GameInfoMgr* GetGameInfoMgr() { return GameInfoMgr::getInstance(); }