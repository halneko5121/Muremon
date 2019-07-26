/******************************************************************
 *	@file	ActorBoss.cpp
 *	@brief	�{�X�̋���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorBoss.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace
{
	const float cInitLife = 3000.0f;	// �{�X�̏������C�t
	const float cAddLife = 1000.0f;		// �{�X�����񂾎��������Ă������C�t
	const int cDeadAlpha = 5;			// �{�X���ł������̃A���t�@���l
	const int cAppearPosX = 950;		// �{�X�̏o�����S�ʒu
	const int cRefreshStopX = 550;		// �X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
	const int cDamageHitCount = 50;		// �{�X���U��������H��������ɒɂ���\��
	const int cDeadSeTime = 60;
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
	, mCollision(nullptr)
	, mAnimation(nullptr)
	, mLife(cInitLife)
	, mMaxLife(cInitLife)
	, mLvCount(0)
	, mHitCount(0)
{
	mAnimation = new Animation(R_BOSS_MOVE1, R_BOSS_MOVE2, 5);
	mCollision = new Collision(this, &ActorBoss::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Enemy);

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
	APP_SAFE_DELETE(mAnimation);
	APP_SAFE_DELETE(mCollision);
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

void
ActorBoss::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_BOSS);
	UtilGraphics::setVertexColor(mVertex, mAlpha, 255, 255, 255);
	UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
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

/**
 * @brief �Փ˂����ۂɓ����Ă���
 */
void
ActorBoss::hitResponce(const HitParam& param)
{
	// �G�t�F�N�g
	EffectParam effect_param(mTexture, mVertex, param.mHitPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect1, effect_param);
	mHitCount++;

	// �_���[�W�v�Z
	ActorBase* actor = UtilActor::searchActor(param.mActorUniqId);
	APP_POINTER_ASSERT(actor);
	mLife -= UtilBattle::calcAtkPower(*actor);;
	if (mLife < 0) mLife = 0;
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
	mAnimation->startLoop();
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
	mRectNum = mAnimation->update();

	if (UtilGame::isGameModeRefresh())
	{
		if (mNowPos.x <= cRefreshStopX)
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
	mHitCount = 0;
	mRectNum = R_BOSS_DAMAGE;
}
void
ActorBoss::stateDamage()
{
	if (mState.getStateCount() == 60)
	{
		if (UtilGame::isGameModeRefresh())
		{
			if (mNowPos.x <= cRefreshStopX)
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
	getEffectMgr()->createEffect(cEffectId_HitEffect7, param);

	// �R���W�����ݒ�
	mCollision->setEnable(false);
}
void
ActorBoss::stateDead()
{
	if (mState.getStateCount() == cDeadSeTime)
	{
		UtilSound::playOnce(cSoundId_SeBossDead);
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
	mRect.updateCenterPosCenter(mNowPos);
	mSpeed = 1;
	mMaxLife = cInitLife + (cAddLife * mLvCount);
	mLife = mMaxLife;
	mCollision->setEnable(true);
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