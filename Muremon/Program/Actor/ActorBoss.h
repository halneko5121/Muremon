#pragma once

#include "Program/DefineGame.h"

class Vertex;
class Texture;

class ActorBoss
{
public:
	ActorBoss();
	~ActorBoss();

	void impleInit();
	void control(int play_mode);
	void draw();
	void fallDraw();

public:
	float		mLife;
	float		mMaxLife;
	float		mMoveX;
	float		mMoveY;
	int			mHitCount;
	bool		mIsDeath;		// �{�X�����S�������̃t���O
	bool		mIsWin;
	int			mSpeedX;

private:
	Texture*	mTexture;
	Vertex*		mVertex;
	float		mLvCount;
	int			mDamageTime;
	int			mMode;
	int			mAlphaCount;	// �{�X�̃A���t�@�J�E���g
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
