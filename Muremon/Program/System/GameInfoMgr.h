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
	virtual ~GameInfoMgr();

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

	/**
	 * @brief	各種キー入力数の情報
	 */
	void					setWeakAtkCount(int count);
	int						getWeakAtkCount() const;

	void					setMediumAtkCount(int count);
	int						getMediumAtkCount() const;

	void					setStrongAtkCount(int count);
	int						getStrongAtkCount() const;

	// ゲームモード
	void					setGameModeRefresh();
	void					setGameModeNormal();
	bool					isGameModeRefresh() const;
	bool					isGameModeNormal() const;

	// 攻撃力低下
	void					setBadStatusAtkLv(int lv);
	int						getBadStatusAtkLv() const;

private:
	static GameInfoMgr*		mInstance;			// インスタンス
	GameScore*				mScore;				// スコア
	int						mGameMode;			// モード
	int						mWeakAtkCount;		// 弱攻撃（にくまん）を行った回数
	int						mMediumAtkCount;	// 中攻撃（吉たろう）を行った回数
	int						mStrongAtkCount;	// 強攻撃（のっぽ）を行った回数
	int						mBadStatusAtkLv;	// 攻撃力低下のLV　@todo: ここで管理は違う気がする
};

static GameInfoMgr* getGameInfoMgr() { return GameInfoMgr::getInstance(); }