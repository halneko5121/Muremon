/******************************************************************
 *	@file	ActorNoppo.cpp
 *	@brief	�A�N�^�[�i�̂��ہj
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorNoppo.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Util/Orbit/OrbitWave.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"

namespace
{
	const Vector2f cActorSize = { 50.0f, 150.0f };				// �L�����̃T�C�Y

	//�������֌W
	const int cParaRandAcc = 15;								// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;								// �ړ���				
	const int cParaRandMoveXMin = -5;

	// �g�����֌W
	const int cWaveAmplit = 10;									// �U��(�㉺�ɓ�����)					
	const int cWaveCycle = 60;									// �����t���[��
	
	// �J�n���W
	const int cRandY = 350;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

	const int cAtkPowerNoppo = 60;									// �̂��ۂ̍U����
	const int cAddGaugePowerNoppo = 10;								// �̂��ۃ~�b�V�����Q�[�W������
	const int cAddScoreNoppo = 10;									// �̂��ۃX�R�A���Z

	enum State
	{
		cState_Idle,				// �ҋ@
		cState_GroundAtk,			// �n��U��
		cState_SkyAtk,				// �󒆍U��
		cState_GroundDeathAnime,	// ���S�i�n��)�A�j��
		cState_GroundDeath,			// ���S�i�n��)
		cState_SkyDeath,			// ���S�i�󒆁j
		cState_End,					// �I��
		cState_Count
	};
}

/**
 * @brief �R���X�g���N�^
 */
ActorNoppo::ActorNoppo(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mGroundAtkAnime(nullptr)
	, mSkyAtkAnime(nullptr)
	, mGroundDeadAnime(nullptr)
	, mOrbitWave(nullptr)
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
{
	mAtkPower = cAtkPowerNoppo;
	mMissionPower = cAddGaugePowerNoppo;
	mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	mGroundAtkAnime = new Animation(R_NOPPO_G_ATK1, R_NOPPO_G_ATK4, 10);
	mSkyAtkAnime = new Animation(R_NOPPO_S_ATK1, R_NOPPO_S_ATK2, 10);
	mGroundDeadAnime = new Animation(R_NOPPO_MOTION1, R_NOPPO_MOTION3, 10);

	mOrbitWave = new OrbitWave();

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, Idle,			 cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundAtk,		 cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyAtk,			 cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundDeathAnime, cState_GroundDeathAnime);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundDeath,		 cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyDeath,		 cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, End,				 cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief �f�X�g���N�^
 */
ActorNoppo::~ActorNoppo(void)
{
	APP_SAFE_DELETE(mOrbitWave);
}

/**
 * @brief ������
 */
void
ActorNoppo::initImple()											
{
}

/**
 * ���s
 */
void
ActorNoppo::runImple()
{
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
ActorNoppo::updateImple()
{
	mState.executeState();
}

/**
 * @brief �`�揈��
 */
void
ActorNoppo::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);
	UtilGraphics::setVertexAngle(mVertex, mAngleDegree);
	UtilGraphics::setVertexColor(mVertex, mAlpha, 255, 255, 255);
	if (mState.isEqual(cState_SkyDeath))
	{
		UtilGraphics::drawF(mVertex, mNowPos, mRectNum);
	}
	else
	{
		UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
	}
}

/**
 * @brief �U������
 */
void
ActorNoppo::updateAttack2()
{
	mOrbitWave->update(&mNowPos);
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
ActorNoppo::stateEnterIdle()
{
}
void
ActorNoppo::stateIdle()
{
}

/**
 * @brief �X�e�[�g:GroundAtk
 */
void
ActorNoppo::stateEnterGroundAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cActorSize.x, UtilGame::getGroundPosY());
	mAngleDegree = 0.0f;
	mRectNum = R_NOPPO_G_ATK1;
	mGroundAtkAnime->startLoop();
}
void
ActorNoppo::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(*this, *boss))
	{
		setIsHitCheck(true);

		if (UtilSound::isPlaying(S_NOPPO_GANMEN))
		{
			UtilSound::stop(S_NOPPO_GANMEN);
		}
		UtilSound::playOnce(S_NOPPO_GANMEN);

		UtilGame::addScore(cAddScoreNoppo);

		EffectParam param(mTexture, mVertex, mNowPos);
		getEffectMgr()->createEffect(cEffectId_HitEffect5, param);

		mState.changeState(cState_GroundDeathAnime);
		return;
	}
	// �U������(x����ʊO����Ȃ���Ώ���)
	else
	{
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
}

/**
 * @brief �X�e�[�g:SkyAtk
 */
void
ActorNoppo::stateEnterSkyAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);

	mIsAtk2 = true;
	mSpeed = getRandomSpeed();
	float rand_pos_y = static_cast<float>((rand() % cRandY) + cRandYMin);
	mNowPos = Vector2f(-cActorSize.x, rand_pos_y);
	mAngleDegree = 0.0f;
	mOrbitWave->init(cWaveAmplit, cWaveCycle, mSpeed);

	mRectNum = R_NOPPO_S_ATK1;
	mSkyAtkAnime->startLoop();
}
void
ActorNoppo::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(*this, *boss))
	{
		setIsHitCheck(true);

		if (UtilSound::isPlaying(S_NOPPO_KOKE))
		{
			UtilSound::stop(S_NOPPO_KOKE);
		}
		UtilSound::playOnce(S_NOPPO_KOKE);
		if ((UtilSound::isPlaying(S_NOPPO_PETI)) &&
			(UtilSound::isPlaying(S_NOPPO_KOKE)))
		{
			UtilSound::stop(S_NOPPO_PETI);
		}
		if (UtilSound::isPlaying(S_NOPPO_KOKE))
		{
			UtilSound::playOnce((S_NOPPO_PETI));
		}

		UtilGame::addScore(cAddScoreNoppo);

		EffectParam param(mTexture, mVertex, mNowPos);
		getEffectMgr()->createEffect(cEffectId_HitEffect6, param);

		mState.changeState(cState_SkyDeath);
		return;
	}
	// �U������(x����ʊO����Ȃ���Ώ���)
	else
	{
		if (UtilGame::isScreenOutWithoutLeft(*this))
		{
			mState.changeState(cState_End);
			return;
		}
		else
		{
			mOrbitWave->setSpeed(mSpeed);
			updateAttack2();
			mRectNum = mSkyAtkAnime->update();
			mRect.updateCenterPosCenter(mNowPos);
		}
	}
}

/**
 * @brief �X�e�[�g:GroundDeathAnime
 */
void
ActorNoppo::stateEnterGroundDeathAnime()
{
	mRectNum = R_NOPPO_MOTION1;
	mGroundDeadAnime->startOnce();
}
void
ActorNoppo::stateGroundDeathAnime()
{
	mRectNum = mGroundDeadAnime->update();
	if (mGroundDeadAnime->isEnd())
	{
		mState.changeState(cState_GroundDeath);
		return;
	}
}

/**
 * @brief �X�e�[�g:GroundDeath
 */
void
ActorNoppo::stateEnterGroundDeath()
{
}
void
ActorNoppo::stateGroundDeath()
{
	if (cWaitMotion <= mState.getStateCount())
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:SkyDeath
 */
void
ActorNoppo::stateEnterSkyDeath()
{
	// ����������
	mSpeed -= mRandAcc;
}
void
ActorNoppo::stateSkyDeath()
{
	// ��]������
	mAngleDegree += cSpinSpeed;

	// �`����Œ�
	mRectNum = R_NOPPO_S_ATK2;

	// ����������
	mNowPos.x += mRandMoveX;
	mSpeed += cGravity;
	mNowPos.y += mSpeed;

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
ActorNoppo::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
	mAlpha = 0;
	mGroundAtkAnime = 0;
}
void
ActorNoppo::stateEnd()
{

}