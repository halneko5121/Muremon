#include "ActorBoss.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"

namespace
{
	//�{�X�̃R���g���[���^�C�v
	enum BOSS_CONTROLTYPE
	{
		REFRESH_TYPE,	//�������胂�[�h
		NORMAL_TYPE,	//�m�[�}�����[�h
	};

	enum BOSS_FADE
	{
		F_BOSS_ACTION,		//�ړ��A�_���[�W
		F_BOSS_FALL,		//��
		F_BOSS_END,			//�A���t�@�l�G���h
	};

	enum NO_FONT
	{
		NF_FADE_IN,
		NF_USUALLY,
		NF_FADE_OUT,
	};

	enum BOSS_MODE
	{
		M_BOSS_MOVE,		//�ړ�
		M_BOSS_DAMEGE,		//�_���[�W
		M_BOSS_USUALLY,		//�{�X��~
		M_BOSS_FALL,		//��
	};

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_Move,			// �ړ�
		cState_Damage,			// �_���[�W
		cState_Stop,			// �����~�܂�
		cState_Dead,			// ���S
		cState_DeadFade,		// ���S�i�t�F�[�h�j
		cState_End,				// �I��
		cState_Revival,			// ����
		cState_Count
	};
}

// �{�X�֘A
#define BOSS_INITIAL_LIFE			(3000)	//�{�X�̏������C�t
#define BOSS_GROW_LIFE				(1000)	//�{�X�����񂾎��������Ă������C�t
#define BOSS_ALPHA_FALL				(5)		//�{�X���ł������̃A���t�@���l
#define BOSS_APPEARANCE_POSITION	(950)	//�{�X�̏o�����S�ʒu
#define BOSS_REFRESH_X_STOP			(550)	//�X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
#define BOSS_STABILITY_Y			(350)	//�{�XY�ʒu�̌Œ�
#define BOSS_DAMAGE_COUNT			(50)	//�{�X���U��������H��������ɒɂ���\��
#define BOSS_FALL_TIME				(60)

#define DAMAGE_RAND					(5)

#define NO_FONT						(25)

#define NO_POSITION_X				(150.f)
#define NO_POSITION_Y				(150.f)

#define BOSS_MOVECOUNT				(3)

ActorBoss::ActorBoss(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mLife(BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount))
	, mMaxLife(BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount))
	, mMoveX(BOSS_APPEARANCE_POSITION)
	, mMoveY(BOSS_STABILITY_Y)
	, mHitCount(0)
	, mIsWin(false)
	, mSpeedX(1)

	, mState()
	, mLvCount(0)
	, mDamageTime(0)
	, mAlphaCount(0)
	, mAlpha(255)
	, mFadeOutTime(0)
	, mRectData(R_BOSS_MOVE1)
	, mNoFontAlpha(0)
	, mNoDrawTime(0)
	, mNoFadeFlag(NF_FADE_IN)
	, mMoveAnimeTime(0)
	, mMoveAnime(0)
	, mDamageX(0)
	, mDamageY(0)
	, mEffectFont(0)
	, mEffectFontMove(false)
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorBoss, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorBoss, mState, Move,			cState_Move);
	REGIST_STATE_FUNC2(ActorBoss, mState, Damage,		cState_Damage);
	REGIST_STATE_FUNC2(ActorBoss, mState, Stop,			cState_Stop);
	REGIST_STATE_FUNC2(ActorBoss, mState, Dead,			cState_Dead);
	REGIST_STATE_FUNC2(ActorBoss, mState, DeadFade,		cState_DeadFade);
	REGIST_STATE_FUNC2(ActorBoss, mState, Revival,		cState_Revival);
	REGIST_STATE_FUNC2(ActorBoss, mState, End,			cState_End);
	mState.changeState(cState_Idle);
}

ActorBoss::~ActorBoss()
{
}

void ActorBoss::initImple()
{
	mState.changeState(cState_Move);
}

void
ActorBoss::runImple()
{
}

void
ActorBoss::updateImple(POS_CC<float> boss_cc)
{
	mState.executeState();

	// �{�X�̈ړ��A�j���[�V�����R���g���[��
	if (mMoveAnimeTime % 16 == 15)
	{
		mMoveAnime++;
	}

	//���C�t���O�ɂȂ������̃R���g���[��
	if (mLife < 0) mLife = 0;
	if (mLife == 0)
	{
		mState.changeStateIfDiff(cState_Dead);
	}
	// �K��񐔂̃_���[�W�R���g���[��
	else if (mHitCount == BOSS_DAMAGE_COUNT)
	{
		mState.changeState(cState_Damage);
	}
}

int
ActorBoss::setAnimetion(int max_animetion, int anime_count, int rect_num)
{
	return anime_count;
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

/**
 * @brief ���S���Ă��邩�H
 */
bool
ActorBoss::isDead() const
{
	return (mState.isEqual(cState_Dead));
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
ActorBoss::stateEnterIdle()
{
}
void
ActorBoss::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Move
 */
void
ActorBoss::stateEnterMove()
{
}
void
ActorBoss::stateMove()
{
	// ���t���[�������Ɉړ�
	if (mState.getStateCount() % BOSS_MOVECOUNT == 0)
	{ 
		mMoveX--;
	}
	mMoveAnimeTime++;

	mRectData = R_BOSS_MOVE1 + mMoveAnime % 2;
	if (UtilGame::isGameModeRefresh())
	{
		if (mMoveX == BOSS_REFRESH_X_STOP)
		{
			mState.changeState(cState_Stop);
			return;
		}
	}
	else
	{
		if (mMoveX <= BOSS_WIN_POSITOIN)
		{
			mState.changeState(cState_End);
			return;
		}
	}
}

/**
 * @brief �X�e�[�g:Damage
 */
void
ActorBoss::stateEnterDamage()
{
	mDamageX = rand() % DAMAGE_RAND;
	mDamageY = rand() % DAMAGE_RAND;
	mHitCount = 0;
}
void
ActorBoss::stateDamage()
{
	mRectData = R_BOSS_DAMAGE;
	mDamageTime++;
	if (mDamageTime == 60)
	{
		mDamageX = 0;
		mDamageY = 0;
		if (UtilGame::isGameModeRefresh())
		{
			if (mMoveX == BOSS_REFRESH_X_STOP)
			{
				mDamageTime = 0;
				mState.changeState(cState_Stop);
				return;
			}
			else
			{
				mDamageTime = 0;
				mState.changeState(cState_Move);
				return;
			}
		}
		else
		{
			mDamageTime = 0;
			mState.changeState(cState_Move);
			return;
		}
	}

}

/**
 * @brief �X�e�[�g:Stop
 */
void
ActorBoss::stateEnterStop()
{
	mRectData = R_BOSS_USUALLY;
}
void
ActorBoss::stateStop()
{
}

/**
 * @brief �X�e�[�g:Dead
 */
void
ActorBoss::stateEnterDead()
{
	mRectData = R_BOSS_FALL;
}
void
ActorBoss::stateDead()
{
	mFadeOutTime++;
	mEffectFontMove = true;

	if (mFadeOutTime == BOSS_FALL_TIME)
	{
		UtilSound::playOnce(S_DEAD);
	}
	else if (mFadeOutTime > BOSS_FALL_TIME)
	{
		if (mAlphaCount++ > 1)
		{
			mAlpha -= BOSS_ALPHA_FALL;
			mAlphaCount = 0;
		}
		if (mAlpha < 0)
		{
			mAlpha = 0;
			mAlphaCount = 0;
		}

		if (mAlpha == 0)
		{
			mAlpha = 0;
			mAlphaCount = 0;
			mState.changeState(cState_Revival);
			return;
		}
	}

	if (mEffectFontMove)
	{
		mEffectFont++;
		if (mEffectFont > NO_FONT) {
			mEffectFontMove = false;
			mEffectFont = NO_FONT;
		}
	}

	//�uNo�`�v�̃t�F�[�h�C���A�E�g
	switch (mNoFadeFlag)
	{
	case NF_FADE_IN:
		mNoFontAlpha += 5;
		if (mNoFontAlpha >= 255)
		{
			mNoFontAlpha = 255;
			mNoFadeFlag = NF_USUALLY;
		}
		break;
	case NF_USUALLY:
		mNoFontAlpha = 255;
		mNoDrawTime++;
		if (mNoDrawTime >= 60)
		{
			mNoFadeFlag = NF_FADE_OUT;
		}
		break;
	case NF_FADE_OUT:
		mNoFontAlpha -= 5;
		if (mNoFontAlpha <= 0)
		{
			mNoFontAlpha = 0;
		}
		break;
	}

}

/**
 * @brief �X�e�[�g:DeadFade
 */
void
ActorBoss::stateEnterDeadFade()
{
}
void
ActorBoss::stateDeadFade()
{
}

/**
 * @brief �X�e�[�g:Revival
 */
void
ActorBoss::stateEnterRevival()
{
	if (mLvCount < 7)
	{
		mLvCount++;
	}
	else mLvCount = 7;

	// ���Z�b�g
	mAlphaCount = 0;
	mHitCount = 0;
	mAlpha = 255;
	mFadeOutTime = 0;
	mDamageTime = 0;
	mRectData = R_BOSS_MOVE1;
	mMoveX = BOSS_APPEARANCE_POSITION;
	mIsWin = false;
	mNoFontAlpha = 0;
	mNoDrawTime = 0;
	mNoFadeFlag = NF_FADE_IN;
	mMoveAnime = 0;
	mMoveAnimeTime = 0;
	mSpeedX = 1;
	mDamageX = 0;
	mDamageY = 0;
	mEffectFont = 0;
	mEffectFontMove = false;
	mLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount);
	mMaxLife = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * mLvCount);
}
void
ActorBoss::stateRevival()
{
	mState.changeState(cState_Move);
}

/**
 * @brief �X�e�[�g:End
 */
void
ActorBoss::stateEnterEnd()
{
	mIsWin = true;
}
void
ActorBoss::stateEnd()
{
}