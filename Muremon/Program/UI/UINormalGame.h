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
	void				draw(const float& mission_guage, const int& time) const;

private:
	void				drawMissionGuage(const float& mission_guage) const;
	void				drawScore() const;
	void				drawTime(const int& time) const;

private:
	Texture*			mTexture;				// テクスチャ
	Vertex*				mVertex;				// バーテックス
	UIRefreshGame*		mUIRefreshGame;			// リフレッシュゲームUI
};