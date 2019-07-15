#pragma once
/******************************************************************
 *	@file	UIRefreshGame.h
 *	@brief	リフレッシュゲームUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Texture;
class Vertex;
class ActorBoss;

class UIRefreshGame
{
public:
	UIRefreshGame();
	~UIRefreshGame();
	void				init();
	void				update();
	void				draw(const ActorBoss& boss);

private:
	void				drawKeyCount();
	void				drawHpGauge(const ActorBoss& boss);

private:
	Texture*			mTexture;				// テクスチャ
	Vertex*				mVertex;				// バーテックス
};