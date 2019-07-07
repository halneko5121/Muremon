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
	void	init(LPDIRECT3DDEVICE9 device);
	void	update();
	void	draw();

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
	void	stateEnterIdle();
	void	stateExeIdle();

	void	stateEnterTop();
	void	stateExeTop();

	void	stateEnterMenuSelect();
	void	stateExeMenuSelect();

	void	stateEnterGameSelect();
	void	stateExeGameSelect();

private:
	StateMachine<UITitleMenu>	mState;					// ステート
	Texture*					mTexture;				// テクスチャ
	Vertex*						mVertex;				// バーテックス
	LPDIRECT3DDEVICE9			mDevice;				// デバイス
	D3DXVECTOR2					mCursorPos;				// カーソル位置
	int							mCurrentMenuItem;		// カーソルが選択しているものを判別。
	int							mAlphaZPush;			// Zpush 用のアルファ
	int							mTimeCount;				// ロゴのタイムカウント
	int							mCursorAnime;			// カーソルアニメーション
	bool						mIsZPush;
};