#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	アクター管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class ActorMgr
{
public:
	ActorMgr();
	~ActorMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static ActorMgr*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void			create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			destroy();

private:
	static ActorMgr*	mInstance;		// インスタンス
};

static ActorMgr* GetDirectFont() { return ActorMgr::getInstance(); }