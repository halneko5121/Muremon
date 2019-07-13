#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Effect/EffectMgr.h"

namespace 
{
	// �������֌W
	const int cParaRandAcc = 15;					// �����x
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;					// �ړ���				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + RADIUS_NIKU;	// �������̍ŏI���W

	// �o�E���h�֌W
	const int cDegRand = 30;						// �����_���̕�
	const int cDegRandMin = 180 + 45;				// 75���܂ł̊�

	// �J�n���W
	const int cRandY = 300;
	const int cRandYMin = -200;

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

	CHARADATA cInitActorData = {
		// �X�s�[�h, �A�j���[�V����, ��`, ���ߓx
		(0.0f), 0, 0, 255,
		// �e�t���O
		false, false, false,
		// ���S���W
		Vector2f(0.f, 0.f),
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
ActorNikuman::ActorNikuman(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
	, mRandDeg(0.0f)
{
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;

	// �\����
	mCharaData = cInitActorData;

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

	mCharaData.mRectNum	= rect_num;

	return anime_count;
}

/**
 * @brief �`�揈��
 */
void
ActorNikuman::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mCharaData.mNowPos, (mRectStartNum + mCharaData.mRectNum + mCharaData.mAnimation) );
}

/**
 * @brief �U������
 */
Vector2f
ActorNikuman::updateAttack2(Vector2f boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mCharaData.mNowPos.x - (boss_cc.x + RADIUS_NIKU));
	range_y = fabsf(mCharaData.mNowPos.y - boss_cc.y);

	plus_x = (range_x / mCharaData.mSpeed);
	plus_y = (range_y / mCharaData.mSpeed);

	mCharaData.mNowPos.x += plus_x;								//���S�Ɍ������ĉE�Ɉړ�
	mCharaData.mNowPos.y += plus_y;								//���S�Ɍ������ĉ��Ɉړ�

	return mCharaData.mNowPos;
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
	mCharaData = cInitActorData;
	mCharaData.mIsAtk1 = true;
	mCharaData.mSpeed = getNikumanSpeed();
	mCharaData.mAnimation = 0;
	mCharaData.mNowPos = Vector2f(-RADIUS_NIKU, G_ATK_2_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorNikuman::stateGroundAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NIKUMAN)) 
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_GroundDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_NIKU < cWindowWidth)
	{
		mCharaData.mAnimation = setAnimetion(ANIME_G_ATK4_NIKU, mCharaData.mAnimation, NULL);
		mCharaData.mNowPos = updateAttack1();
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
	mCharaData = cInitActorData;
	mCharaData.mIsAtk2 = true;
	mCharaData.mSpeed = getNikumanSpeed();
	mCharaData.mNowPos = Vector2f(-RADIUS_NIKU, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNikuman::stateSkyAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NIKUMAN))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_SkyDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_NIKU < cWindowWidth) 
	{
		mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_S_ATK1_NIKU);
		mCharaData.mNowPos = updateAttack2(mBossPos);
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
	mCharaData.mAnimation = 0;
	mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_DEATH_NIKU);

	mCharaData.mNowPos = mOrbit->mRebound->orbitRebound(mRandDeg, mCharaData.mSpeed, mCharaData.mNowPos);

	if ((mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU)) 
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mCharaData.mNowPos.x < -RADIUS_NIKU) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU))
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
	mCharaData.mAnimation = 0;
	mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_DEATH_NIKU);

	mCharaData.mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.mNowPos);

	if ((mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU))
	{
		mState.changeState(cState_End);
	}

	// ���S���W����ʊO�Ȃ玀�S
	if ((mCharaData.mNowPos.x < -RADIUS_NIKU) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU)) 
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
	mCharaData.mIsAtk1 = false;
	mCharaData.mIsAtk2 = false;
}
void
ActorNikuman::stateEnd()
{
}
