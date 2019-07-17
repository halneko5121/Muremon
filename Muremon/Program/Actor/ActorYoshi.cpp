#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"

namespace
{
	// �������֌W
	const int cParaRandAcc = 15;							// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// �ړ���				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + cYoshiRadius + 50.f;	// �������̍ŏI���W

	// �o�E���h�֌W
	const int cDegRand = 30;								// �����_���̕�
	const int cDegRandMin = 180 + 45;						// 75���܂ł̊�

	// �J�n���W
	const int cRandY = 400;
	const int cRandYMin = 100;

	// �g�����֌W
	const int cWaveAmplit = 10;								// �U��(�㉺�ɓ�����)					
	const int cWaveCycle = 200;								// ����(��������Α傫�����������Z��)
	const int cWaveLimitX = 400;							// ���̍��W�܂ŗ���ƒ����^���ֈڍs

	const int cAtkPowerYoshitaro = 40;						// �悵���낤�̍U����
	const int cAddGaugePowerYoshitaro = 20;					// �悵���낤�~�b�V�����Q�[�W������
	const int cAddScoreYoshitaro = 20;						// �悵���낤�X�R�A���Z

	enum ANIME_YOSHI
	{
		ANIME_G_ATK1_YOSHI,
		ANIME_G_ATK2_YOSHI,
		ANIME_G_ATK3_YOSHI,
		ANIME_G_ATK4_YOSHI,

		ANIME_MOTION1_YOSHI,
		ANIME_MOTION2_YOSHI,
		ANIME_MOTION3_YOSHI,

		ANIME_S_ATK1_YOSHI,
		ANIME_S_ATK2_YOSHI,
		ANIME_S_ATK3_YOSHI,
		ANIME_S_ATK4_YOSHI,

		ANIME_DEATH_YOSHI,

		MAX_ANIME_YOSHI,
	};

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
ActorYoshi::ActorYoshi(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f) 
	, mRandDeg(0.0f)
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;
	mAtkPower = cAtkPowerYoshitaro;
	mMissionPower = cAddGaugePowerYoshitaro;
	mScore = cAddScoreYoshitaro;
	mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

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
 * @brief �A�j���ݒ�
 */
int
ActorYoshi::setAnimetion(int max_animetion, int anime_count ,int rect_num)
{
	static int delay = 0;

	if(delay++ > 15){
		if(max_animetion == 0) anime_count = 0;
		else{
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
ActorYoshi::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	mVertex->setAngle(mAngleDegree);
	mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation));
}

/**
 * @brief �U������
 */
void
ActorYoshi::updateAttack2()
{
	mOrbit->mWave->orbitSinWave(&mNowPos, cWaveLimitX, mNowPos);
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
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	}
	mIsAtk1 = true;
	mSpeed = getSpeed();
	mAnimation = 0;
	mNowPos = Vector2f(-cYoshiRadius, (UtilGame::getGroundPosY() + 40.0f - cYoshiRadius));
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorYoshi::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(mNowPos, boss->getNowPos(), ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPos = mNowPos;

		if (UtilSound::isPlaying(S_YOSHI_HIP))
		{
			UtilSound::stop(S_YOSHI_HIP);
		}
		UtilSound::playOnce(S_YOSHI_HIP);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect3, param);

		mState.changeState(cState_GroundDeath);
		return;
	}

	if (mNowPos.x - cYoshiRadius < cWindowWidth)
	{
		updateAttack1();
		mAnimation = setAnimetion(ANIME_G_ATK4_YOSHI, mAnimation, NULL);
	}
	else
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:SkyAtk
 */
void
ActorYoshi::stateEnterSkyAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	}
	mIsAtk2 = true;
	mSpeed = getSpeed();
	mNowPos = Vector2f(-cYoshiRadius, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorYoshi::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(mNowPos, boss->getNowPos(), ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPos = mNowPos;

		if (UtilSound::isPlaying(S_YOSHI_HUSEN))
		{
			UtilSound::stop(S_YOSHI_HUSEN);
		}
		UtilSound::playOnce(S_YOSHI_HUSEN);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect4, param);

		mState.changeState(cState_SkyDeathAnime);
	}

	if (mNowPos.x - cYoshiRadius < cWindowWidth)
	{
		mOrbit->mWave->setSpeed(mSpeed);
		updateAttack2();
		mAnimation = setAnimetion(NULL, mAnimation, ANIME_S_ATK1_YOSHI);
	}
	else
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:GroundDeath
 */
void
ActorYoshi::stateEnterGroundDeath()
{
	mAnimation = 0;
	mRectNum = ANIME_DEATH_YOSHI;
}
void
ActorYoshi::stateGroundDeath()
{
	mOrbit->mRebound->orbitRebound(&mNowPos, mRandDeg, mSpeed, mNowPos);

	// ���S���W����ʊO�Ȃ玀�S
	if ((mNowPos.x < -cYoshiRadius) || (mNowPos.x > cWindowWidth + cYoshiRadius) &&
		(mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:SkyDeathAnime
 */
void
ActorYoshi::stateEnterSkyDeathAnime()
{
}
void
ActorYoshi::stateSkyDeathAnime()
{
	mAnimation = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI), mAnimation, ANIME_S_ATK2_YOSHI);
	if (mAnimation == 3)
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
	mAnimation = 0;																//�`����Œ�
	mRectNum = ANIME_DEATH_YOSHI;
}
void
ActorYoshi::stateSkyDeath()
{
	mAngleDegree += cSpinSpeed;
	mOrbit->mParabora->orbitParabola(&mNowPos, mRandAcc, mRandMoveX, cParaLimitY, mNowPos);

	if ((mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius))
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mNowPos.x < -cYoshiRadius) || (mNowPos.x > cWindowWidth + cYoshiRadius) &&
		(mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius)) 
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
ActorYoshi::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
	mAnimation = 0;
}
void
ActorYoshi::stateEnd()
{
}
