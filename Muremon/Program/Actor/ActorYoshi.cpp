/******************************************************************
 *	@file	ActorNikuman.cpp
 *	@brief	�g���낤�̋���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "ActorYoshi.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Util/Orbit/OrbitWave.h"
#include "Program/Util/Orbit/OrbitRebound.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace
{
	const Vector2f cActorSize = { 50.0f, 100.0f };			// �L�����̃T�C�Y

	// �������֌W
	const int cParaRandAcc = 15;							// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// �ړ���				
	const int cParaRandMoveXMin = -5;

	// �o�E���h�֌W
	const int cDegRand = 30;								// �����_���̕�
	const int cDegRandMin = 180 + 45;						// 75���܂ł̊�

	// �J�n���W
	const int cRandY = 350;
	const int cRandYMin = 100;

	// �g�����֌W
	const int cWaveAmplit = 5;								// �U��(�㉺�ɓ�����)					
	const int cWaveCycle = 30;								// ����(1������t���[����)
	
	const int cAtkPowerYoshitaro = 40;						// �悵���낤�̍U����
	const int cAddGaugePowerYoshitaro = 20;					// �悵���낤�~�b�V�����Q�[�W������
	const int cAddScoreYoshitaro = 20;						// �悵���낤�X�R�A���Z

	enum State
	{
		cState_Idle,				// �ҋ@
		cState_GroundAtk,			// �n��U��
		cState_SkyAtk,				// �󒆍U��
		cState_GroundDeath,			// ���S�i�n��)
		cState_SkyDeathAnime,		// ���S�i�󒆁j�A�j��
		cState_SkyDeath,			// ���S�i�󒆁j
		cState_End,					// �I��
		cState_Count
	};

	/**
	 * @brief �{�X�A�N�^�[���擾����
	 */
	ActorBase*
	getBoss()
	{
		return UtilActor::searchSingleActor(cActorId_Boss);
	}
}

/**
 * @brief �R���X�g���N�^
 */
ActorYoshi::ActorYoshi(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mCollision(nullptr)
	, mGroundAtkAnime(nullptr)
	, mSkyDeadAnime(nullptr)
	, mOrbitWave(nullptr)
	, mOrbitRebound(nullptr)
	, mRandMoveX(0.0f)
{
	mAtkPower = cAtkPowerYoshitaro;
	mMissionPower = cAddGaugePowerYoshitaro;
	mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	mGroundAtkAnime = new Animation(R_YOSHI_G_ATK1, R_YOSHI_G_ATK4, 10);
	mSkyDeadAnime = new Animation(R_YOSHI_S_ATK2, R_YOSHI_S_ATK4, 8);
	mCollision = new Collision(this, &ActorYoshi::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Pleyer);

	mOrbitWave = new OrbitWave();
	mOrbitRebound = new OrbitRebound(0.0f, mSpeed);

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, Idle,				cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundAtk,			cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyAtk,				cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundDeath,			cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeathAnime,		cState_SkyDeathAnime);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeath,			cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, End,					cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief �f�X�g���N�^
 */
ActorYoshi::~ActorYoshi(void)
{
	APP_SAFE_DELETE(mCollision);
	APP_SAFE_DELETE(mGroundAtkAnime);
	APP_SAFE_DELETE(mSkyDeadAnime);
	APP_SAFE_DELETE(mOrbitWave);
	APP_SAFE_DELETE(mOrbitRebound);
}

/**
 * @brief ������
 */
void
ActorYoshi::initImple()
{
}

/**
 * ���s
 */
void
ActorYoshi::runImple()
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
ActorYoshi::updateImple()
{
	mState.executeState();
}

/**
 * @brief �Փ˂����ۂɓ����Ă���
 */
void
ActorYoshi::hitResponce(const HitParam& param)
{
	UtilGame::addScore(cAddScoreYoshitaro);
	mCollision->setEnable(false);

	if (mState.isEqual(cState_GroundAtk))
	{
		mState.changeState(cState_GroundDeath);
		return;
	}

	if (mState.isEqual(cState_SkyAtk))
	{
		mState.changeState(cState_SkyDeathAnime);
		return;
	}
}

/**
 * @brief �`�揈��
 */
void
ActorYoshi::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);
	UtilGraphics::setVertexAngle(mVertex, mAngleDegree);

	if (mState.isEqual(cState_SkyDeath))
	{
		UtilGraphics::drawF(mVertex, mNowPos, mRectNum);
	}
	else
	{
		UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
	}
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
ActorYoshi::stateEnterIdle()
{
}
void
ActorYoshi::stateIdle()
{
}

/**
 * @brief �X�e�[�g:GroundAtk
 */
void
ActorYoshi::stateEnterGroundAtk()
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
	mRectNum = R_YOSHI_G_ATK1;
	mGroundAtkAnime->startLoop();
}
void
ActorYoshi::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mNowPos.x += mSpeed;
		mRectNum = mGroundAtkAnime->update();
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief �X�e�[�g:SkyAtk
 */
void
ActorYoshi::stateEnterSkyAtk()
{
	// �U���J�n
	mIsAtk1 = false;
	mIsAtk2 = true;
	float rand_pos_y = static_cast<float>((rand() % cRandY) + cRandYMin);
	mNowPos = Vector2f(-cActorSize.x, rand_pos_y);
	mRect.updateCenterPosCenter(mNowPos);
	mSpeed = getRandomSpeed();
	mAngleDegree = 0.0f;
	mOrbitWave->init(cWaveAmplit, cWaveCycle, mSpeed);
	mRectNum = R_YOSHI_S_ATK1;
}
void
ActorYoshi::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mOrbitWave->update(&mNowPos);
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief �X�e�[�g:GroundDeath
 */
void
ActorYoshi::stateEnterGroundDeath()
{
	if (UtilSound::isPlaying(cSoundId_SeHitYoshiGround))
	{
		UtilSound::stop(cSoundId_SeHitYoshiGround);
	}
	UtilSound::playOnce(cSoundId_SeHitYoshiGround);

	EffectParam param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect3, param);

	mRectNum = R_YOSHI_DEATH;
	float rand_deg = static_cast<float>((rand() % cDegRand) + cDegRandMin);
	mOrbitRebound->setDegree(rand_deg);
	mOrbitRebound->setSpeed(mSpeed);
}
void
ActorYoshi::stateGroundDeath()
{
	mOrbitRebound->update(&mNowPos);
	mRect.updateCenterPosCenter(mNowPos);

	// ��ʊO�Ȃ玀�S
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:SkyDeathAnime
 */
void
ActorYoshi::stateEnterSkyDeathAnime()
{
	if (UtilSound::isPlaying(cSoundId_SeHitYoshiSky))
	{
		UtilSound::stop(cSoundId_SeHitYoshiSky);
	}
	UtilSound::playOnce(cSoundId_SeHitYoshiSky);

	EffectParam param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect4, param);

	mSkyDeadAnime->startOnce();
}
void
ActorYoshi::stateSkyDeathAnime()
{
	mRectNum = mSkyDeadAnime->update();
	if (mSkyDeadAnime->isEnd())
	{
		mState.changeState(cState_SkyDeath);
		return;
	}
}

/**
 * @brief �X�e�[�g:SkyDeath
 */
void
ActorYoshi::stateEnterSkyDeath()
{
	mRectNum = R_YOSHI_DEATH;
	mRandMoveX = static_cast<float>((rand() % cParaRandMoveX) + cParaRandMoveXMin);

	// ����������
	float rand_jump_power = static_cast<float>((rand() % cParaRandAcc) + cParaRandAccMin);
	mSpeed -= rand_jump_power;
}
void
ActorYoshi::stateSkyDeath()
{
	mAngleDegree += cSpinSpeed;

	// ����������
	mNowPos.x += mRandMoveX;
	mSpeed += cGravity;
	mNowPos.y += mSpeed;
	mRect.updateCenterPosCenter(mNowPos);

	// ��ʊO�Ȃ玀�S
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
ActorYoshi::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
}
void
ActorYoshi::stateEnd()
{
}
