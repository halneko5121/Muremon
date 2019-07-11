#pragma once

#include "Program/DefineGame.h"
#include "Program/Actor/ActorBase.h"

class Vertex;
class Texture;

class ActorBoss : public ActorBase
{
public:
	ActorBoss();
	~ActorBoss();

	void		init() override;
	void		runImple() override;
	void		update(POS_CC<float> boss_cc, bool boss_death) override;
	void		draw() override;
	void		deathControl() override;
	int			setAnimetion(int max_animetion, int anime_count, int rect_num) override;

	void		control(int play_mode);
	void		fallDraw();
	void		drawEffectFont();

public:
	float		mLife;
	float		mMaxLife;
	float		mMoveX;
	float		mMoveY;
	int			mHitCount;
	bool		mIsDeath;		// ボスが死亡した時のフラグ
	bool		mIsWin;
	int			mSpeedX;

private:
	Texture*	mTexture;
	Vertex*		mVertex;
	float		mLvCount;
	int			mDamageTime;
	int			mMode;
	int			mAlphaCount;	// ボスのアルファカウント
	int			mPlayMode;
	bool		mIsDamage;
	bool		mIsRevival;

	int			mAlpha;
	int			mFadeOutTime;
	int			mRectData;

	int			mNoFontAlpha;
	int			mNoDrawTime;
	int			mNoFadeFlag;

	int			mMoveCount;
	bool		mIsMove;
	int			mMoveAnimeTime;
	unsigned int mMoveAnime;
	int			mDamageX;
	int			mDamageY;
	bool		mEffectFontMove;
	float		mEffectFont;
};
