#pragma once
/******************************************************************
 *	@file	UtilGame.h
 *	@brief	ゲーム関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Rect;
class ActorBase;

namespace UtilGame
{
	// ゲームモード
	void				setGameModeRefresh();
	void				setGameModeNormal();
	bool				isGameModeRefresh();
	bool				isGameModeNormal();

	// スコア関連
	void				setScore(int score);
	int					getScore();
	void				addScore(int add_score);
	void				mulScore(int mul_score);

	// その他
	float				getGroundPosY();
	bool				isScreenOut(const ActorBase& owner);
	bool				isScreenOutWithoutLeft(const ActorBase& owner);
}