#include "ActorBoss.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	// �{�X�֘A
	const int cInitLife = 3000;			// �{�X�̏������C�t
	const int cAddLife = 1000;			// �{�X�����񂾎��������Ă������C�t
	const int cDeadAlpha = 5;			// �{�X���ł������̃A���t�@���l
	const int cAppearPosX = 950;		// �{�X�̏o�����S�ʒu
	const int cAppearPosY = 350;		// �{�XY�ʒu�̌Œ�
	const int cRefreshStopX = 550;		// �X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
	const int cDamageHitCount = 50;		// �{�X���U��������H��������ɒɂ���\��
	const int cDeadSeTime = 60;
	const int cDamagePosRand = 5;
	const int cMoveInterval = 3;

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

ActorBoss::ActorBoss(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mLife(cInitLife + (cAddLife * mLvCount))
	, mMaxLife(cInitLife + (cAddLife * mLvCount))
	, mMoveX(cAppearPosX)
	, mMoveY(cAppearPosY)
	, mHitCount(0)
	, mIsWin(false)
	, mSpeedX(1)

	, mState()
	, mLvCount(0)
	, mDamageTime(0)
	, mAlpha(255)
	, mRectData(R_BOSS_MOVE1)
	, mMoveAnimeTime(0)
	, mMoveAnime(0)
	, mDamageX(0)
	, mDamageY(0)
	, mHitPos(0.0f)
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
	else if (mHitCount == cDamageHitCount)
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

/**
 * �Փˎ��̏���
 */
void ActorBoss::hit(const float& hit_pos, int damage)
{
	EffectParam param(mTexture, mVertex, POS_CC<float>(mMoveX, hit_pos));
	GetEffectMgr()->createEffect(cEffectId_HitEffect1, param);
	mHitPos = hit_pos;
	mHitCount++;
	mLife -= damage;
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
	if (mState.getStateCount() % cMoveInterval == 0)
	{ 
		mMoveX--;
	}
	mMoveAnimeTime++;

	mRectData = R_BOSS_MOVE1 + mMoveAnime % 2;
	if (UtilGame::isGameModeRefresh())
	{
		if (mMoveX == cRefreshStopX)
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
	mDamageX = rand() % cDamagePosRand;
	mDamageY = rand() % cDamagePosRand;
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
			if (mMoveX == cRefreshStopX)
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

	EffectParam param(mTexture, mVertex, POS_CC<float>(mMoveX, mMoveY));
	GetEffectMgr()->createEffect(cEffectId_HitEffect7, param);
}
void
ActorBoss::stateDead()
{
	if (mState.getStateCount() == cDeadSeTime)
	{
		UtilSound::playOnce(S_DEAD);
	}
	else if (cDeadSeTime < mState.getStateCount())
	{
		mAlpha -= cDeadAlpha;
		if (mAlpha < 0) mAlpha = 0;
		if (mAlpha == 0)
		{
			mState.changeState(cState_Revival);
			return;
		}
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
	mHitCount = 0;
	mAlpha = 255;
	mDamageTime = 0;
	mRectData = R_BOSS_MOVE1;
	mMoveX = cAppearPosX;
	mIsWin = false;
	mMoveAnime = 0;
	mMoveAnimeTime = 0;
	mSpeedX = 1;
	mDamageX = 0;
	mDamageY = 0;
	mLife = cInitLife + (cAddLife * mLvCount);
	mMaxLife = cInitLife + (cAddLife * mLvCount);
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