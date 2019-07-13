#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	// �������֌W
	const int cParaRandAcc = 15;							// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// �ړ���				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + RADIUS_YOSHI + 50.f;	// �������̍ŏI���W

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

	CHARADATA cInitActorData = {
		// �X�s�[�h,�A�j���[�V����,��`,���ߓx
		(0.0f), 0, 0, (MAX_ALPHA),
		//�e�t���O
		false, false, false,
		// ���S���W
		Vector2f((-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI)),
	};

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
ActorYoshi::ActorYoshi(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f) 
	, mRandDeg(0.0f)
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;

	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

	mCharaData = cInitActorData;

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundAtk,	cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyAtk,		cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundDeath, cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeath,	cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, End,			cState_End);
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
	if (mCharaData.mIsAtk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mCharaData.mIsAtk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief �X�V
 */
void
ActorYoshi::updateImple(Vector2f boss_cc)
{
	mBossPos = boss_cc;
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

	mCharaData.mRectNum	= rect_num;

	return anime_count;
}

/**
 * @brief �`�揈��
 */
void
ActorYoshi::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	mVertex->setAngle(mAngleDegree);
	mVertex->drawF(mCharaData.mNowPos, (mRectStartNum + mCharaData.mRectNum + mCharaData.mAnimation));
}

/**
 * @brief �U������
 */
Vector2f
ActorYoshi::updateAttack2()														//�L�[���͂ɂ�铮�삻��2
{
	mCharaData.mNowPos = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData.mNowPos);

	return mCharaData.mNowPos;
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
	mCharaData = cInitActorData;
	mCharaData.mIsAtk1 = true;
	mCharaData.mSpeed = getSpeed();
	mCharaData.mAnimation = 0;
	mCharaData.mNowPos = Vector2f(-RADIUS_YOSHI, G_ATK_1_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorYoshi::stateGroundAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		if (UtilSound::isPlaying(S_YOSHI_HIP))
		{
			UtilSound::stop(S_YOSHI_HIP);
		}
		UtilSound::playOnce(S_YOSHI_HIP);

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect3, param);

		mState.changeState(cState_GroundDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_YOSHI < cWindowWidth)
	{
		mCharaData.mNowPos = updateAttack1();
		mCharaData.mAnimation = setAnimetion(ANIME_G_ATK4_YOSHI, mCharaData.mAnimation, NULL);
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
	mCharaData = cInitActorData;
	mCharaData.mIsAtk2 = true;
	mCharaData.mSpeed = getSpeed();
	mCharaData.mNowPos = Vector2f(-RADIUS_YOSHI, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorYoshi::stateSkyAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		if (UtilSound::isPlaying(S_YOSHI_HUSEN))
		{
			UtilSound::stop(S_YOSHI_HUSEN);
		}
		UtilSound::playOnce(S_YOSHI_HUSEN);

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect4, param);

		mState.changeState(cState_SkyDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_YOSHI < cWindowWidth)
	{
		mOrbit->mWave->setSpeed(mCharaData.mSpeed);
		mCharaData.mNowPos = updateAttack2();
		mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_S_ATK1_YOSHI);
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
}
void
ActorYoshi::stateGroundDeath()
{
	if (!mCharaData.mIsDeathNext)
	{
		mCharaData.mAnimation = setAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI), mCharaData.mAnimation, ANIME_MOTION1_YOSHI);
		if (mCharaData.mAnimation == 3)
		{
			mCharaData.mIsDeathNext = true;
		}
	}
	if (mCharaData.mIsDeathNext)
	{
		mCharaData.mAnimation = 0;																//�`����Œ�
		mCharaData.mRectNum = ANIME_DEATH_YOSHI;

		mCharaData.mNowPos = mOrbit->mRebound->orbitRebound(mRandDeg, mCharaData.mSpeed, mCharaData.mNowPos);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mCharaData.mNowPos.x < -RADIUS_YOSHI) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_YOSHI) &&
		(mCharaData.mNowPos.y < -RADIUS_YOSHI) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_YOSHI))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:SkyDeath
 */
void
ActorYoshi::stateEnterSkyDeath()
{
}
void
ActorYoshi::stateSkyDeath()
{
	if (!mCharaData.mIsDeathNext)
	{
		mCharaData.mAnimation = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI), mCharaData.mAnimation, ANIME_S_ATK2_YOSHI);
		if (mCharaData.mAnimation == 3)
		{
			mCharaData.mIsDeathNext = true;
		}
	}
	if (mCharaData.mIsDeathNext)
	{
		mAngleDegree += SPIN_SPEED;
		mCharaData.mAnimation = 0;																//�`����Œ�
		mCharaData.mRectNum = ANIME_DEATH_YOSHI;

		mCharaData.mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.mNowPos);
	}

	if ((mCharaData.mNowPos.y < -RADIUS_YOSHI) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_YOSHI))
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mCharaData.mNowPos.x < -RADIUS_YOSHI) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_YOSHI) &&
		(mCharaData.mNowPos.y < -RADIUS_YOSHI) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_YOSHI)) 
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
	mCharaData.mIsAtk1 = mCharaData.mIsAtk2 = false;
	mCharaData.mIsDeathNext = false;
	mCharaData.mAnimation = 0;
}
void
ActorYoshi::stateEnd()
{
}
