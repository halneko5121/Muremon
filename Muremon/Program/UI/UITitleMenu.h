#pragma once
/******************************************************************
 *	@file	UITitleMenu.h
 *	@brief	タイトルメニューUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/StateMachine.h"

class Texture;
class Vertex;

class UITitleMenu
{
public:
	UITitleMenu();
	~UITitleMenu();
	void	Init(Texture* texture, Vertex* vertex);
	void	Update();
	void	Draw();
	int		CurrentSelectIndex();

private:
	// ステート関数
	void stateEnterIdle();
	void stateExeIdle();

	void stateEnterTop();
	void stateExeTop();

	void stateEnterMenuSelect();
	void stateExeMenuSelect();

	void stateEnterGameSelect();
	void stateExeGameSelect();

private:
	StateMachine<UITitleMenu>	mState;					// ステート
	Texture*					mTexture;
	Vertex*						mVertex;
	D3DXVECTOR2					mCursorPos;
	int							mCurrentMenuItem;		// カーソルが選択しているものを判別。
	int							mAlphaZPush;
	int							mTimeCount;				// ロゴのタイムカウント
	int							mCursorAnime;			// カーソルアニメーション
	int							mDispItem;				// グラフィックの変化を知らせる。
	bool						mIsZPush;
};