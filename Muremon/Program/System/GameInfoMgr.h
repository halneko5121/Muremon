#pragma once
/******************************************************************
 *	@file	GameInfoMgr.h
  *	@brief	ゲーム情報を管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class GameScore;

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
	 * @brief	スコアクラスの取得
	 */
	GameScore*				getGameScore() const;

private:
	static GameInfoMgr*		mInstance;		// インスタンス
	GameScore*				mScore;			// スコア
};

static GameInfoMgr* GetGameInfoMgr() { return GameInfoMgr::getInstance(); }