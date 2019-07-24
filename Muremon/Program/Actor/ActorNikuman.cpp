/******************************************************************
 *	@file	ActorNikuman.cpp
 *	@brief	�ɂ��܂�̋���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "ActorNikuman.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Util/Orbit/OrbitRebound.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace 
{
	const Vector2f cActorSize = { 40.0f, 40.0f };	// �L�����̃T�C�Y

	// �������֌W
	const int cParaRandAcc = 20;					// �����x
	const int cParaRandAccMin = 20;
	const int cParaRandMoveX = -15;					// �ړ���				
	const int cParaRandMoveXMin = -5;

	// �o�E���h�֌W
	const int cDegRand = 30;						// �����_���̕�
	const int cDegRandMin = 180 + 45;				// 75���܂ł̊�

	// �J�n���W
	const int cRandY = 300;
	const int cRandYMin = 0;

	const int cAtkPowerNikuman = 20;				// �ɂ��܂�̍U����
	const int cAddGaugePowerNikuman = 30;			// �ɂ��܂�~�b�V�����Q�[�W������
	const int cAddScoreNikuman = 30;				// �ɂ��܂�X�R�A���Z

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_GroundAtk,		// �n��U��
		cState_SkyAtk,			// �󒆍U��
		cState_GroundDeath,		// ���S�i�n��)
		cState_SkyDeath,		// ���S�i�󒆁j
		cState_End,				// �I��
		cState_Count
	};
}

/**
 * @brief �R���X�g���N�^
 */
ActorNikuman::ActorNikuman(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mCollision(nullptr)
	, mAnimation(nullptr)
	, mOrbitRebound(nullptr)
	, mRandMoveX(0.0f)
{
	mAtkPower = cAtkPowerNikuman;
	mMissionPower = cAddGaugePowerNikuman;
	mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	mAnimation = new Animation(R_NIKU_G_ATK1, R_NIKU_G_ATK4, 10);
	mOrbitRebound = new OrbitRebound(0.0f, mSpeed);
	mCollision = new Collision(this, &ActorNikuman::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Pleyer);

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNikuman, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorNikuman, mState, GroundAtk,		cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNikuman, mState, SkyAtk,		cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNikuman, mState, GroundDeath,	cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorNikuman, mState, SkyDeath,		cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorNikuman, mState, End,			cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief �f�X�g���N�^
 */
ActorNikuman::~ActorNikuman(void)
{
	APP_SAFE_DELETE(mCollision);
	APP_SAFE_DELETE(mAnimation);
	APP_SAFE_DELETE(mOrbitRebound);
}

/**
 * @brief ������
 */
void
ActorNikuman::initImple()								
{
}

/**
 * ���s
 */
void
ActorNikuman::runImple()
{
	mCollision->setEnable(true);

	if (mIsAtk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mIsAtk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief �X�V
 */
void
ActorNikuman::updateImple()
{
	mState.executeState();
}

/**
 * @brief �`�揈��
 */
void
ActorNikuman::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);
	UtilGraphics::setVertexAngle(mVertex, mAngleDegree);
	UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
}

/**
 * @brief �Փ˂����ۂɓ����Ă���
 */
void
ActorNikuman::hitResponce(const HitParam& param)
{
	UtilSound::playOnce(cSoundId_SeHitNikuman);
	UtilGame::addScore(cAddScoreNikuman);

	EffectParam effect_param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect2, effect_param);

	mCollision->setEnable(false);

	if (mState.isEqual(cState_GroundAtk))
	{
		mState.changeStateIfDiff(cState_GroundDeath);
		return;
	}
	else if (mState.isEqual(cState_SkyAtk))
	{
		mState.changeStateIfDiff(cState_SkyDeath);
		return;
	}
}

/**
 * @brief �U������
 */
void
ActorNikuman::updateAttack2(const Vector2f& boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mNowPos.x - (boss_cc.x + cActorSize.x));
	range_y = fabsf(mNowPos.y - boss_cc.y);

	plus_x = (range_x / mSpeed);
	plus_y = (range_y / mSpeed);

	mNowPos.x += plus_x;								//���S�Ɍ������ĉE�Ɉړ�
	mNowPos.y += plus_y;								//���S�Ɍ������ĉ��Ɉړ�
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
ActorNikuman::stateEnterIdle()
{
}
void
ActorNikuman::stateIdle()
{
}

/**
 * @brief �X�e�[�g:GroundAtk
 */
void
ActorNikuman::stateEnterGroundAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cActorSize.x, UtilGame::getGroundPosY());
	mRect.updateCenterPosCenter(mNowPos);
	mAngleDegree = 0.0f;
	mAnimation->startLoop();
}
void
ActorNikuman::stateGroundAtk()
{
	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mRectNum = mAnimation->update();
		mNowPos.x += mSpeed;
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief �X�e�[�g:SkyAtk
 */
void
ActorNikuman::stateEnterSkyAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk2 = true;
	mSpeed = getRandomNikumanSpeed();
	float rand_pos_y = static_cast<float>((rand() % cRandY) + cRandYMin);
	mNowPos = Vector2f(-cActorSize.x, rand_pos_y);
	mRect.updateCenterPosCenter(mNowPos);
	mAngleDegree = 0.0f;
	mRectNum = R_NIKU_S_ATK;
}
void
ActorNikuman::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(*this, *boss))
	{
		UtilSound::playOnce(cSoundId_SeHitNikuman);
		setIsHitCheck(true);

		UtilGame::addScore(cAddScoreNikuman);

		EffectParam param(mTexture, mVertex, mNowPos);
		getEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_SkyDeath);
		return;
	}

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		updateAttack2(boss->getNowPos());
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief �X�e�[�g:GroundDeath
 */
void
ActorNikuman::stateEnterGroundDeath()
{
	mRectNum = R_NIKU_DEATH;

	float rand_deg = static_cast<float>((rand() % cDegRand + cDegRandMin));
	mOrbitRebound->setDegree(rand_deg);
	mOrbitRebound->setSpeed(mSpeed);
}
void
ActorNikuman::stateGroundDeath()
{
	mOrbitRebound->update(&mNowPos);

	// ��ʊO�Ȃ玀�S
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:SkyDeath
 */
void
ActorNikuman::stateEnterSkyDeath()
{
	mRectNum = R_NIKU_DEATH;
	mRandMoveX = static_cast<float>((rand() % cParaRandMoveX) + cParaRandMoveXMin);

	// ����������
	float rand_jump_power = static_cast<float>((rand() % cParaRandAcc) + cParaRandAccMin);
	mSpeed -= rand_jump_power;
}
void
ActorNikuman::stateSkyDeath()
{
	// ����������
	mNowPos.x += mRandMoveX;
	mSpeed += cGravity;
	mNowPos.y += mSpeed;

	// ��ʊO�Ȃ玀�S
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
ActorNikuman::stateEnterEnd()
{
	mIsAtk1 = false;
	mIsAtk2 = false;
}
void
ActorNikuman::stateEnd()
{
}
