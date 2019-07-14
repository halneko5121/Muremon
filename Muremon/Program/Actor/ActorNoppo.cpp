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
#include "Program/Effect/EffectMgr.h"

namespace
{
	//�������֌W
	const int cParaRandAcc = 15;									// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;									// �ړ���				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = cWindowHeight + cNoppoRadius + 50;	// �������̍ŏI���W

	// �g�����֌W
	const int cWaveAmplit = 20;										// �U��(�㉺�ɓ�����)					
	const int cWaveCycle = 200;										// ����(��������Α傫�����������Z��)
	const int cWaveLimitX = 500;									// ���̍��W�܂ŗ���ƒ����^���ֈڍs

	// �J�n���W
	const int cRandY = 400;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

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
ActorNoppo::ActorNoppo(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
{
	mRectStartNum = R_NOPPO_G_ATK1;
	mSoundStartNum = S_NOPPO_KOKE;
	mNowPos = Vector2f((-cNoppoRadius), (cWindowWidth + 50.f + cNoppoRadius));
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

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
ActorNoppo::updateImple(Vector2f boss_cc)
{
	mBossPos = boss_cc;
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
ActorNoppo::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(static_cast<D3DCOLOR>(mAlpha), 255, 255, 255);
	mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation));
}

/**
 * @brief �U������
 */
Vector2f
ActorNoppo::updateAttack2()	
{
	mNowPos = mOrbit->mWave->orbitSinWave(cWaveLimitX,mNowPos);

	return mNowPos;
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
		mNowPos = Vector2f((-cNoppoRadius), (cWindowWidth + 50.f + cNoppoRadius));
	}
	mIsAtk1 = true;
	mSpeed = getSpeed();
	mNowPos = Vector2f(-cNoppoRadius, G_ATK_3_START_Y);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateGroundAtk()
{
	if (isHit(mNowPos, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		mHitPosY = mNowPos.y;

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
		if (mNowPos.x - cNoppoRadius < cWindowWidth) {
			mNowPos = updateAttack1();
			mAnimation = setAnimetion(ANIME_G_ATK4_NOPPO, mAnimation, NULL);
		}
		else
		{
			mState.changeState(cState_End);
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
		mNowPos = Vector2f((-cNoppoRadius), (cWindowWidth + 50.f + cNoppoRadius));
	}
	mIsAtk2 = true;
	mSpeed = getSpeed();
	mNowPos = Vector2f(-cNoppoRadius, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateSkyAtk()
{
	if (isHit(mNowPos, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		mHitPosY = mNowPos.y;

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
		if (mNowPos.x - cNoppoRadius < cWindowWidth) {
			mOrbit->mWave->setSpeed(mSpeed);
			mNowPos = updateAttack2();
			mAnimation = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO), mAnimation, ANIME_S_ATK1_NOPPO);
		}
		else
		{
			mState.changeState(cState_End);
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
}
void
ActorNoppo::stateSkyDeath()
{
	// ��]������
	mAngleDegree += SPIN_SPEED;

	mAnimation = 0;																	//�`����Œ�
	mRectNum = ANIME_S_ATK2_NOPPO;

	mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mNowPos);

	// ��ʊO�Ȃ玀�S
	if ((mNowPos.x < -(cNoppoRadius + 50)) || (mNowPos.x > cWindowWidth + cNoppoRadius + 50) &&
		(mNowPos.y < -(cNoppoRadius + 50)) || (mNowPos.y > cWindowHeight + cNoppoRadius + 50)) 
	{
		mState.changeState(cState_End);
	}

	if ((mNowPos.y < (-cNoppoRadius)) || (mNowPos.y > cWindowHeight + cNoppoRadius + 30))
	{
		mState.changeState(cState_End);
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