#pragma once
/******************************************************************
 *	@file	UINormalGame.h
 *	@brief	ノーマルゲームUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Texture;
class Vertex;
class ActorBoss;
class UIRefreshGame;

class UINormalGame
{
public:
	UINormalGame();
	~UINormalGame();
	void				init();
	void				update();
	void				draw(const ActorBoss& boss, const float& mission_guage, const int& time);

private:
	void				drawMissionGuage(const float& mission_guage);
	void				drawScore();
	void				drawTime(const int& time);

private:
	Texture*			mTexture;				// テクスチャ
	Vertex*				mVertex;				// バーテックス
	UIRefreshGame*		mUIRefreshGame;			// リフレッシュゲームUI
};