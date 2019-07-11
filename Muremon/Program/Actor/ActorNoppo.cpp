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

	const float cParaLimitY = cWindowHeight + RADIUS_NOPPO + 50;	// �������̍ŏI���W

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

	CHARADATA init_charadata_noppo = {
		// �X�s�[�h, �A�j���[�V����, ��`, ���ߓx
		(0.0f), 0, 0, (MAX_ALPHA),
		// �e�t���O
		false, false, false, false, false, false, false, false,
		// ���S���W
		POS_CC<float>((-RADIUS_NOPPO), (cWindowWidth + 50.f + RADIUS_NOPPO)),
	};

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_GroundAtk,		// �n��U��
		cState_SkyAtk,			// �󒆍U��
		cState_DeathReady,		// ���S����
		cState_DeathFade,		// ���S�t�F�[�h
		cState_Death,			// ���S
		cState_Count
	};
}

/**
 * @brief �R���X�g���N�^
 */
ActorNoppo::ActorNoppo()
	: mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
{
	mRectStartNum = R_NOPPO_G_ATK1;
	mSoundStartNum = S_NOPPO_KOKE;
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

	// �\����
	mCharaData = init_charadata_noppo;

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundAtk,		cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyAtk,			cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, DeathReady,		cState_DeathReady);
	REGIST_STATE_FUNC2(ActorNoppo, mState, DeathFade,		cState_DeathFade);
	REGIST_STATE_FUNC2(ActorNoppo, mState, Death,			cState_Death);
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
ActorNoppo::init()											
{
}

/**
 * ���s
 */
void
ActorNoppo::runImple()
{
	if (mCharaData.flag_atk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mCharaData.flag_atk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief �X�V
 */
void
ActorNoppo::update(POS_CC<float> boss_cc, bool boss_death)
{
	mBossPos = boss_cc;
	mIsBossDeath = boss_death;

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

	mCharaData.rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief �`�揈��
 */
void
ActorNoppo::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(static_cast<D3DCOLOR>(mCharaData.alpha), 255, 255, 255);
	mVertex->drawF(mCharaData.draw_cc.x, mCharaData.draw_cc.y,
		(mRectStartNum + mCharaData.rect_num + mCharaData.animetion));
}

/**
 * @brief �U������
 */
POS_CC<float>
ActorNoppo::updateAttack2()	
{
	mCharaData.draw_cc = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData.draw_cc);

	return mCharaData.draw_cc;
}

/**
 * @brief ���S����
 */
void
ActorNoppo::deathControl()
{
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
	mCharaData = init_charadata_noppo;
	mCharaData.flag_atk1 = true;
	mCharaData.speed = getSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NOPPO, G_ATK_3_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateGroundAtk()
{
	if (mIsBossDeath) return;

	if (isHit(mCharaData.draw_cc, mBossPos, ID_NOPPO))
	{
		mCharaData.flag_hit = true;
		mCharaData.flag_death = true;
		setIsHitCheck(true);
		m_chara_y = mCharaData.draw_cc.y;

		if (UtilSound::isPlaying(S_NOPPO_GANMEN))
		{
			UtilSound::stop(S_NOPPO_GANMEN);
		}
		UtilSound::playOnce(S_NOPPO_GANMEN);

		GetEffectMgr()->createEffect(cEffectId_HitEffect5, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_DeathReady);
		return;
	}
	// �U������(x����ʊO����Ȃ���Ώ���)
	else
	{
		if (mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth) {
			mCharaData.draw_cc = updateAttack1();
			mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NOPPO, mCharaData.animetion, NULL);
		}
	}
}

/**
 * @brief �X�e�[�g:SkyAtk
 */
void
ActorNoppo::stateEnterSkyAtk()
{
	mCharaData = init_charadata_noppo;
	mCharaData.flag_atk2 = true;
	mCharaData.speed = getSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NOPPO, mAtkStartY);

	mCountEffect = 0;
	mAtkStartY = (float)(rand() % cRandY);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateSkyAtk()
{
	if (mIsBossDeath) return;

	if (isHit(mCharaData.draw_cc, mBossPos, ID_NOPPO))
	{
		mCharaData.flag_hit = true;
		mCharaData.flag_death = true;
		setIsHitCheck(true);
		m_chara_y = mCharaData.draw_cc.y;

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
		GetEffectMgr()->createEffect(cEffectId_HitEffect6, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_DeathReady);
		return;
	}
	// �U������(x����ʊO����Ȃ���Ώ���)
	else
	{
		if (mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth) {
			mOrbit->mWave->setSpeed(mCharaData.speed);
			mCharaData.draw_cc = updateAttack2();
			mCharaData.animetion = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO), mCharaData.animetion, ANIME_S_ATK1_NOPPO);
		}
		else
		{
			mState.changeState(cState_DeathReady);
		}
	}
}

/**
 * @brief �X�e�[�g:DeathReady
 */
void
ActorNoppo::stateEnterDeathReady()
{
}
void
ActorNoppo::stateDeathReady()
{
	static int wait_count = 0;

	if (mCharaData.flag_atk1) {
		if (!mCharaData.flag_death_next) {
			mCharaData.animetion = setAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO), mCharaData.animetion, ANIME_MOTION1_NOPPO);
			if (mCharaData.animetion == 2)
			{
				mCharaData.flag_death_next = true;
			}
		}
		else {
			mCharaData.animetion = 0;																//�`����Œ�
			mCharaData.rect_num = ANIME_MOTION3_NOPPO;
			if (wait_count++ > cWaitMotion) {
				mCharaData.flag_deathfade = true;
				wait_count = 0;
				mState.changeState(cState_DeathFade);
			}
		}
	}
	else if (mCharaData.flag_atk2) {

		// ��]������
		mAngleDegree += SPIN_SPEED;

		mCharaData.animetion = 0;																	//�`����Œ�
		mCharaData.rect_num = ANIME_S_ATK2_NOPPO;

		mCharaData.draw_cc = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.draw_cc);
	}

	//����������̏���
	if (mCharaData.flag_hit) 
	{
		//��ʊO�Ȃ玀�S
		if ((mCharaData.draw_cc.x < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_NOPPO + 50) &&
			(mCharaData.draw_cc.y < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 50)) {
			mCharaData.flag_death = true;
			mState.changeState(cState_Death);
		}
	}
	if ((mCharaData.draw_cc.y < (-RADIUS_NOPPO)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 30)) {
		mState.changeState(cState_Death);
	}
}

/**
 * @brief �X�e�[�g:DeathFade
 */
void
ActorNoppo::stateEnterDeathFade()
{
}
void
ActorNoppo::stateDeathFade()
{
	if (mCharaData.flag_deathfade) {
		mCharaData.draw_cc.x = (-RADIUS_NOPPO);
		mCharaData.draw_cc.y = (GAME_GROUND - RADIUS_NOPPO);

		mCharaData.flag_deathfade = false;
		mState.changeState(cState_Death);
	}
}

/**
 * @brief �X�e�[�g:Death
 */
void
ActorNoppo::stateEnterDeath()
{
	mCharaData.flag_atk1 = mCharaData.flag_atk2 = false;
	mCharaData.flag_death = mCharaData.flag_hit = false;
	mCharaData.animetion = 0;
}
void
ActorNoppo::stateDeath()
{

}