#include "ActorBoss.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	const float cInitLife = 3000.0f;	// �{�X�̏������C�t
	const float cAddLife = 1000.0f;		// �{�X�����񂾎��������Ă������C�t
	const int cDeadAlpha = 5;			// �{�X���ł������̃A���t�@���l
	const int cAppearPosX = 950;		// �{�X�̏o�����S�ʒu
	const int cRefreshStopX = 550;		// �X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
	const int cDamageHitCount = 50;		// �{�X���U��������H��������ɒɂ���\��
	const int cDeadSeTime = 60;
	const int cDamagePosRand = 5;
	const int cMoveInterval = 3;
	const Vector2f cActorSize = { 300.0f, 380.0f };

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

ActorBoss::ActorBoss(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mLife(cInitLife)
	, mMaxLife(cInitLife)
	, mLvCount(0)
	, mHitCount(0)
	, mMoveAnime(0)
	, mDamageX(0)
	, mDamageY(0)
{
	mRectNum = R_BOSS_MOVE1;
	mSpeed = 1;
	mNowPos = Vector2f(cAppearPosX, UtilGame::getGroundPosY() + 20.0f);

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

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
ActorBoss::updateImple()
{
	mState.executeState();

	// ���C�t���O�ɂȂ������̃R���g���[��
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
ActorBoss::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_BOSS);
	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawCB(Vector2f(mNowPos.x + mDamageX, mNowPos.y + mDamageY), mRectNum);
}

/**
 * �Փˎ��̏���
 */
void ActorBoss::hit(const Vector2f& hit_pos, float damage)
{
	EffectParam param(mTexture, mVertex, hit_pos);
	GetEffectMgr()->createEffect(cEffectId_HitEffect1, param);
	mHitCount++;
	mLife -= damage;
	if (mLife < 0) mLife = 0;
}

/**
 * @brief ���S���Ă��邩�H
 */
bool
ActorBoss::isDead() const
{
	return (mState.isEqual(cState_Dead));
}

/**
 * @brief ���C�t�̉�
 */
void
ActorBoss::recoveryLife()
{
	mLife = mMaxLife;
}

/**
 * @brief ���C�t���O��
 */
void
ActorBoss::setDead()
{
	mLife = 0;
}

/**
 * @brief ���C�t�̎c�ʂ��p�[�Z���e�[�W��
 */
float
ActorBoss::getLifeRate() const
{
	return (mLife / mMaxLife);
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
		mNowPos.x -= mSpeed;
		mRect.updateCenterPosCenter(mNowPos);
	}

	// �{�X�̈ړ��A�j���[�V�����R���g���[��
	if (mState.getStateCount() % 16 == 15)
	{
		mMoveAnime++;
	}
	mRectNum = R_BOSS_MOVE1 + mMoveAnime % 2;

	if (UtilGame::isGameModeRefresh())
	{
		if (mNowPos.x == cRefreshStopX)
		{
			mState.changeState(cState_Stop);
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
	mRectNum = R_BOSS_DAMAGE;
}
void
ActorBoss::stateDamage()
{
	if (mState.getStateCount() == 60)
	{
		mDamageX = 0;
		mDamageY = 0;
		if (UtilGame::isGameModeRefresh())
		{
			if (mNowPos.x == cRefreshStopX)
			{
				mState.changeState(cState_Stop);
				return;
			}
			else
			{
				mState.changeState(cState_Move);
				return;
			}
		}
		else
		{
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
	mRectNum = R_BOSS_USUALLY;
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
	mRectNum = R_BOSS_FALL;

	EffectParam param(mTexture, mVertex, mNowPos);
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
	mRectNum = R_BOSS_MOVE1;
	mNowPos.x = cAppearPosX;
	mMoveAnime = 0;
	mSpeed = 1;
	mDamageX = 0;
	mDamageY = 0;
	mMaxLife = cInitLife + (cAddLife * mLvCount);
	mLife = mMaxLife;
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
}
void
ActorBoss::stateEnd()
{
}