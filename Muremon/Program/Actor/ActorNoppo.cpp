/******************************************************************
 *	@file	ActorNoppo.cpp
 *	@brief	�A�N�^�[�i�̂��ہj
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorNoppo.h"

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
	const Vector2f cNoppoRadius = { 50.0f, 150.0f };				// �L�����̔��a

	//�������֌W
	const int cParaRandAcc = 15;									// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;									// �ړ���				
	const int cParaRandMoveXMin = -5;

	// �g�����֌W
	const int cWaveAmplit = 10;										// �U��(�㉺�ɓ�����)					
	const int cWaveCycle = 60;										// �����t���[��
	
	// �J�n���W
	const int cRandY = 350;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

	const int cAtkPowerNoppo = 60;									// �̂��ۂ̍U����
	const int cAddGaugePowerNoppo = 10;								// �̂��ۃ~�b�V�����Q�[�W������
	const int cAddScoreNoppo = 10;									// �̂��ۃX�R�A���Z

	enum ANIME_NOPPO
	{
		ANIME_G_ATK1_NOPPO,
		ANIME_G_ATK2_NOPPO,
		ANIME_G_ATK3_NOPPO,
		ANIME_G_ATK4_NOPPO,

		ANIME_MOTION1_NOPPO,
		ANIME_MOTION2_NOPPO,
		ANIME_MOTION3_NOPPO,

		ANIME_S_ATK1_NOPPO,
		ANIME_S_ATK2_NOPPO,

		MAX_ANIME_NOPPO,
	};

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
ActorNoppo::ActorNoppo(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mOrbitWave(nullptr)
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
{
	mRectStartNum = R_NOPPO_G_ATK1;
	mSoundStartNum = S_NOPPO_KOKE;
	mAtkPower = cAtkPowerNoppo;
	mMissionPower = cAddGaugePowerNoppo;
	mScore = cAddScoreNoppo;
	mNowPos = Vector2f(-cNoppoRadius.x, -cNoppoRadius.y);
	mOrbitWave = new OrbitWave();

	mRect.setWidth(cNoppoRadius.x);
	mRect.setHeight(cNoppoRadius.y);
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
 * @brief �A�j���ݒ�
 */
int
ActorNoppo::setAnimetion(int max_animetion, int anime_count ,int rect_num)
{
	static int delay = 0;
	if(delay++ > 15)
	{
		if (max_animetion == 0)
		{
			anime_count = 0;
		}
		else
		{
			if(anime_count < max_animetion) anime_count++;
			else anime_count = 0;
		}
		delay = 0;
	}

	mRectNum	= rect_num;

	return anime_count;
}

/**
 * @brief �`�揈��
 */
void
ActorNoppo::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(static_cast<D3DCOLOR>(mAlpha), 255, 255, 255);
	if (mState.isEqual(cState_SkyDeath))
	{
		mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation));
	}
	else
	{
		mVertex->drawCB(mNowPos, (mRectStartNum + mRectNum + mAnimation));
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
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cNoppoRadius.x, -cNoppoRadius.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cNoppoRadius.x, UtilGame::getGroundPosY());
	mAngleDegree = 0.0f;
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

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect5, param);

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
			mAnimation = setAnimetion(ANIME_G_ATK4_NOPPO, mAnimation, NULL);
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
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cNoppoRadius.x, -cNoppoRadius.y);
	}
	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);

	mIsAtk2 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cNoppoRadius.x, mAtkStartY);
	mAngleDegree = 0.0f;
	mOrbitWave->init(cWaveAmplit, cWaveCycle, mSpeed);
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

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect6, param);

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
			mAnimation = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO), mAnimation, ANIME_S_ATK1_NOPPO);
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
}
void
ActorNoppo::stateGroundDeathAnime()
{
	mAnimation = setAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO), mAnimation, ANIME_MOTION1_NOPPO);
	if (mAnimation == 2)
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
	mAnimation = 0;
	mRectNum = ANIME_MOTION3_NOPPO;
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
	mAnimation = 0;
	mRectNum = ANIME_S_ATK2_NOPPO;

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
	mAnimation = 0;
}
void
ActorNoppo::stateEnd()
{

}