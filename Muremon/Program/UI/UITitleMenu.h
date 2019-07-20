#pragma once
/******************************************************************
 *	@file	UITitleMenu.h
 *	@brief	タイトルメニューUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"

class Texture;
class Vertex;

class UITitleMenu
{
public:
	UITitleMenu();
	~UITitleMenu();
	void	init();
	void	update();
	void	draw() const;

	// メニューセレクト
	bool	isDecideMenuSelectGame() const;
	bool	isDecideMenuSelectRanking() const;
	bool	isDecideMenuSelectExit() const;

	// ゲームセレクト
	bool	isDecideGameSelectRefresh() const;
	bool	isDecideGameSelectNormal() const;
	bool	isDecideGameSelectTutorial() const;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Top);
	DECLAR_STATE_FUNC2(MenuSelect);
	DECLAR_STATE_FUNC2(GameSelect);

private:
	StateMachine				mState;					// ステート
	Texture*					mTexture;				// テクスチャ
	Vertex*						mVertex;				// バーテックス
	Vector2f					mCursorPos;				// カーソル位置
	int							mCurrentMenuItem;		// カーソルが選択しているものを判別。
	int							mAlphaZPush;			// Zpush 用のアルファ
	int							mTimeCount;				// ロゴのタイムカウント
	int							mCursorAnime;			// カーソルアニメーション
	bool						mIsZPush;
};