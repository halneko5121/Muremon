#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Effect/EffectMgr.h"

namespace 
{
	// �������֌W
	const int cParaRandAcc = 15;					// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;					// �ړ���				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + cNikumanRadius;	// �������̍ŏI���W

	// �o�E���h�֌W
	const int cDegRand = 30;						// �����_���̕�
	const int cDegRandMin = 180 + 45;				// 75���܂ł̊�

	// �J�n���W
	const int cRandY = 300;
	const int cRandYMin = -200;

	const int cAtkPowerNikuman = 20;				// �ɂ��܂�̍U����
	const int cAddGaugePowerNikuman = 30;			// �ɂ��܂�~�b�V�����Q�[�W������
	const int cAddScoreNikuman = 30;				// �ɂ��܂�X�R�A���Z

	enum ANIME_NIKU
	{
		ANIME_G_ATK1_NIKU,
		ANIME_G_ATK2_NIKU,
		ANIME_G_ATK3_NIKU,
		ANIME_G_ATK4_NIKU,

		ANIME_S_ATK1_NIKU,

		ANIME_DEATH_NIKU,

		MAX_ANIME_NIKU,
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
ActorNikuman::ActorNikuman(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
	, mRandDeg(0.0f)
{
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;
	mAtkPower = cAtkPowerNikuman;
	mMissionPower = cAddGaugePowerNikuman;
	mScore = cAddScoreNikuman;
	mNowPos = Vector2f((-cNikumanRadius), (cWindowWidth + 50.f + cNikumanRadius));

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
ActorNikuman::updateImple(Vector2f boss_cc)
{
	mBossPos = boss_cc;
	mState.executeState();
}

/**
 * @brief �A�j���ݒ�
 */
int
ActorNikuman::setAnimetion(int max_animetion, int anime_count ,int rect_num)
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
ActorNikuman::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation) );
}

/**
 * @brief �U������
 */
Vector2f
ActorNikuman::updateAttack2(Vector2f boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mNowPos.x - (boss_cc.x + cNikumanRadius));
	range_y = fabsf(mNowPos.y - boss_cc.y);

	plus_x = (range_x / mSpeed);
	plus_y = (range_y / mSpeed);

	mNowPos.x += plus_x;								//���S�Ɍ������ĉE�Ɉړ�
	mNowPos.y += plus_y;								//���S�Ɍ������ĉ��Ɉړ�

	return mNowPos;
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
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cNikumanRadius), (cWindowWidth + 50.f + cNikumanRadius));
	}
	mIsAtk1 = true;
	mSpeed = getNikumanSpeed();
	mAnimation = 0;
	mNowPos = Vector2f(-cNikumanRadius, (UtilGame::getGroundPosY() + 20.0f - cNikumanRadius));
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorNikuman::stateGroundAtk()
{
	if (isHit(mNowPos, mBossPos, ID_NIKUMAN)) 
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPos = mNowPos;

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_GroundDeath);
	}

	if (mNowPos.x - cNikumanRadius < cWindowWidth)
	{
		mAnimation = setAnimetion(ANIME_G_ATK4_NIKU, mAnimation, NULL);
		updateAttack1();
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
ActorNikuman::stateEnterSkyAtk()
{
	// �U���J�n
	{
		mSpeed = 0.0f;
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cNikumanRadius), (cWindowWidth + 50.f + cNikumanRadius));
	}
	mIsAtk2 = true;
	mSpeed = getNikumanSpeed();
	mNowPos = Vector2f(-cNikumanRadius, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNikuman::stateSkyAtk()
{
	if (isHit(mNowPos, mBossPos, ID_NIKUMAN))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPos = mNowPos;

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_SkyDeath);
	}

	if (mNowPos.x - cNikumanRadius < cWindowWidth) 
	{
		mAnimation = setAnimetion(NULL, mAnimation, ANIME_S_ATK1_NIKU);
		mNowPos = updateAttack2(mBossPos);
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
ActorNikuman::stateEnterGroundDeath()
{
}
void
ActorNikuman::stateGroundDeath()
{
	mAnimation = 0;
	mAnimation = setAnimetion(NULL, mAnimation, ANIME_DEATH_NIKU);

	mNowPos = mOrbit->mRebound->orbitRebound(mRandDeg, mSpeed, mNowPos);

	if ((mNowPos.y < -cNikumanRadius) || (mNowPos.y > cWindowHeight + cNikumanRadius)) 
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mNowPos.x < -cNikumanRadius) || (mNowPos.x > cWindowWidth + cNikumanRadius) &&
		(mNowPos.y < -cNikumanRadius) || (mNowPos.y > cWindowHeight + cNikumanRadius))
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
}
void
ActorNikuman::stateSkyDeath()
{
	mAnimation = 0;
	mAnimation = setAnimetion(NULL, mAnimation, ANIME_DEATH_NIKU);

	mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mNowPos);

	if ((mNowPos.y < -cNikumanRadius) || (mNowPos.y > cWindowHeight + cNikumanRadius))
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mNowPos.x < -cNikumanRadius) || (mNowPos.x > cWindowWidth + cNikumanRadius) &&
		(mNowPos.y < -cNikumanRadius) || (mNowPos.y > cWindowHeight + cNikumanRadius)) 
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
