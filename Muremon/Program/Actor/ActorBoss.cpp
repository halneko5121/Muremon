#include "ActorBoss.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

//�{�X�̃R���g���[���^�C�v
enum BOSS_CONTROLTYPE
{
	REFRESH_TYPE,	//�������胂�[�h
	NORMAL_TYPE,	//�m�[�}�����[�h
};

// �{�X�֘A
#define BOSS_INITIAL_LIFE			(3000)	//�{�X�̏������C�t
#define BOSS_GROW_LIFE				(1000)	//�{�X�����񂾎��������Ă������C�t
#define BOSS_ALPHA_APPEAR			(20)	//�{�X���o���������̃A���t�@���l
#define BOSS_ALPHA_FALL				(5)		//�{�X���ł������̃A���t�@���l
#define BOSS_APPEARANCE_POSITION	(950)	//�{�X�̏o�����S�ʒu
#define BOSS_REFRESH_X_STOP			(550)	//�X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
#define BOSS_STABILITY_Y			(350)	//�{�XY�ʒu�̌Œ�
#define BOSS_DAMAGE_COUNT			(50)	//�{�X���U��������H��������ɒɂ���\��
#define BOSS_DAMAGE_TIME_DRAW		(60)	//�{�X�̒ɂ���\������
#define BOSS_FALL_TIME				(60)
#define BOSS_SPPEAR_TIME			(60)	//�{�X���t�F�[�h�A�E�g���鎞��
#define BOSS_NO_DRAWTIME			(120)	//NO��`�悷�鎞��

#define DAMAGE_RAND					(5)

#define NO_FONT						(25)

#define NO_POSITION_X				(150.f)
#define NO_POSITION_Y				(150.f)

#define BOSS_MOVECOUNT				(3)

#define HIT_EFFECT_X				(100)
#define HIT_FFFECT_Y				(450)
#define MISSION_CLEAR_SCORE			(50000)	//�~�b�V�����N���A���Z�X�R�A
#define BOSS_KO_SCORE				(10000)

ActorBoss::ActorBoss(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
{
	//�{�X
	mIsDeath=false;

	mAlphaCount=0;

	mMoveCount=0;
	
	mIsRevival=false;

	mHitCount=0;

	mIsDamage = false;

	mMode=M_BOSS_MOVE;
	
	mAlpha=255;
		
	mFadeOutTime=0;
	
	mDamageTime=0;
	
	mRectData=R_BOSS_MOVE1;

	mLvCount = 0;

	mLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount); 

	mMaxLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount); 

	mMoveX=BOSS_APPEARANCE_POSITION;
	mMoveY=BOSS_STABILITY_Y;
	mMoveCount=0;
	mIsMove=true;

	mIsWin=false;

	mNoFontAlpha=0;
	mNoDrawTime=0;
	mNoFadeFlag=NF_FADE_IN;

	mMoveAnime = 0;
	
	mMoveAnimeTime = 0;

	mSpeedX = 1;

	mDamageX = 0;

	mDamageY = 0;

	mEffectFont = 0;

	mEffectFontMove = false;
}

ActorBoss::~ActorBoss()
{
}

void ActorBoss::initImple()
{
	//�{�X
	mAlphaCount=0;

	mMoveCount=0;
	
	mIsRevival=false;

	mHitCount=0;

	mMode=M_BOSS_MOVE;
	
	mAlpha=255;
		
	mFadeOutTime=0;
	
	mIsDamage = false;

	mDamageTime=0;
	
	mRectData=R_BOSS_MOVE1;

	mMoveX=BOSS_APPEARANCE_POSITION;
	
	mMoveCount=0;

	mIsMove=true;

	mIsWin=false;

	mNoFontAlpha=0;
	mNoDrawTime=0;
	mNoFadeFlag=NF_FADE_IN;

	mMoveAnime = 0;
	
	mMoveAnimeTime = 0;

	mSpeedX = 1;

	mDamageX = 0;

	mDamageY = 0;

	mEffectFont = 0;

	mEffectFontMove = false;

	mLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount); 

	mMaxLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount); 

	mIsRevival=false;

	mIsDeath=false;
}

void
ActorBoss::runImple()
{
}


void
ActorBoss::updateImple(POS_CC<float> boss_cc)
{
}

int
ActorBoss::setAnimetion(int max_animetion, int anime_count, int rect_num)
{
	return anime_count;
}

void ActorBoss::control(int play_mode)
{
	//�{�X�̈ړ��R���g���[��
	if(mIsMove)
	{
		mMoveCount++;
		mMoveAnimeTime++;
	}

	//�{�X�̈ړ����x����
	if(mMoveCount>=BOSS_MOVECOUNT)
	{
		mMoveX-=1;
		mMoveCount=0;
		if(play_mode==PLAY_REFRESH)
		{
			if(mMoveX<=BOSS_REFRESH_X_STOP)
			{
				mMoveX=BOSS_REFRESH_X_STOP;
				mIsMove=false;
			}
		}else{
			if(mMoveX<=BOSS_WIN_POSITOIN)
			{
				mMoveX=BOSS_WIN_POSITOIN;
				mIsMove=false;
				mIsWin=true;
			}
		}
	}
	
	//�{�X�̈ړ��A�j���[�V�����R���g���[��
	if(mMoveAnimeTime % 16 ==15)
	{
		mMoveAnime++;
	}

	//�{�X�̈ړ��X�g�b�v�R���g���[��
	//�K��񐔂̃_���[�W�R���g���[��
	if(mHitCount==BOSS_DAMAGE_COUNT)
	{
		mIsMove = false;
		mIsDamage=true;
		mHitCount=0;
	}

	//���C�t���O�ɂȂ������̃R���g���[��
	if(mLife<0)
	{
		mLife=0;
	}
	if(mLife==0)
	{
		mIsDeath=true;
		mIsMove=false;
	}
	
	//�{�X�����񂾌�̏�����
	if(mIsRevival)
	{
		if(mLvCount<7)
		{
			mLvCount++;
		}else mLvCount = 7;
		initImple();
	}
	
	if(!mIsDeath)
	{
		//�{�X���_���[�W�H��������̏���
		if(mIsDamage)
		{
			mMode=M_BOSS_DAMEGE;
			mDamageX = rand()% DAMAGE_RAND;
			mDamageY = rand()% DAMAGE_RAND;
		}
	}

	//�{�X���{�X�����񂾎��̃t�F�[�h�A�E�g�V�[��
	if(mIsDeath)
	{
		mMode=M_BOSS_FALL;
		mFadeOutTime++;
		mEffectFontMove = true;
		if(mFadeOutTime>BOSS_FALL_TIME)
		{
			if(mAlphaCount++>1)
			{
				mAlpha-=BOSS_ALPHA_FALL;
				mAlphaCount=0;
			}
			if(mAlpha<0)
			{
				mAlpha=0;
				mAlphaCount=0;
			}

			if(mAlpha==0)
			{
				mAlpha=0;
				mAlphaCount=0;
				mIsRevival=true;
			}
		}

		if(mEffectFontMove)
		{
			mEffectFont++;
			if(mEffectFont>NO_FONT){
			mEffectFontMove=false;
			mEffectFont = NO_FONT;
			}
		}

		if (mFadeOutTime == BOSS_FALL_TIME)
		{
			UtilSound::playOnce(S_DEAD);
		}

		//�uNo�`�v�̃t�F�[�h�C���A�E�g
		switch(mNoFadeFlag)
		{
			case NF_FADE_IN:
				mNoFontAlpha+=5;
				if(mNoFontAlpha>=255)
				{
					mNoFontAlpha=255;
					mNoFadeFlag=NF_USUALLY;
				}
				break;
			case NF_USUALLY:
				mNoFontAlpha=255;
				mNoDrawTime++;
				if(mNoDrawTime>=60)
				{
					mNoFadeFlag=NF_FADE_OUT;
				}
				break;
			case NF_FADE_OUT:
				mNoFontAlpha-=5;
				if(mNoFontAlpha<=0)
				{
					mNoFontAlpha=0;
				}
				break;
		}
	}

	//�{�X�̕`��A���[�h
	switch(mMode)
	{
		case M_BOSS_MOVE:
			mRectData=R_BOSS_MOVE1 + mMoveAnime%2;
			if(play_mode==PLAY_REFRESH)
			{
				if(mMoveX==BOSS_REFRESH_X_STOP)
				{
					mIsMove=false;
					mMode=M_BOSS_USUALLY;
				}
			}
			break;
		case M_BOSS_USUALLY:
			mRectData=R_BOSS_USUALLY;
			break;
		case M_BOSS_DAMEGE:
			mRectData=R_BOSS_DAMAGE;
			mDamageTime++;
			if(mDamageTime==60)
			{
				mIsDamage=false;
				mDamageX = 0;
				mDamageY = 0;
				if(play_mode==PLAY_REFRESH)
				{
					if(mMoveX==BOSS_REFRESH_X_STOP)
					{
						mIsMove=false;
						mMode=M_BOSS_USUALLY;
						mDamageTime=0;
					}else{ 
						mMode=M_BOSS_MOVE;
						mIsMove=true;
						mDamageTime=0;
					}
				}else{
					mMode=M_BOSS_MOVE;
					mIsMove=true;
					mDamageTime=0;
				}
			}
			break;
		case M_BOSS_FALL:
			mRectData=R_BOSS_FALL;
			break;
	}
}

void
ActorBoss::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_BOSS);
	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawF(mMoveX + mDamageX,mMoveY + mDamageY,mRectData);
}

void ActorBoss::fallDraw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mNoFontAlpha,255,255,255);
	mVertex->drawF(mMoveX - NO_POSITION_X - mEffectFont,NO_POSITION_Y - mEffectFont,R_BOSS_EFFECT);
}

void
ActorBoss::drawEffectFont()
{
}
