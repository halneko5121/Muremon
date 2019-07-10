#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

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
		false, false, false, false, false, false, false, false,
		// ���S���W
		POS_CC<float>((-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI)),
	};
}

/**
 * @brief �R���X�g���N�^
 */
ActorYoshi::ActorYoshi()
{
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
ActorYoshi::init()											
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;

	mOrbit->mWave->init(cWaveAmplit,cWaveCycle,NULL,WAVE_MODE_GAME);

	//praivate�ϐ�
	s_atk_start_y = 0.f;
	//protected�ϐ�
	mDelay		 = mMaxAnimetion = 0;
	mFlagTurn2 = mIsHitCheck  = false;

	//�\����
	mCharaData.flag_atk1	= mCharaData.flag_atk2		 = false;
	mCharaData.flag_death	= mCharaData.flag_deathfade	 = false;
	mCharaData.flag_effect	= mCharaData.flag_effectfont = false;
	mCharaData.flag_hit		= mCharaData.flag_death_next = false;
	mCharaData.draw_cc.x	= (-RADIUS_NOPPO);						//�L�������W�̏�����
	mCharaData.draw_cc.y	= (GAME_GROUND - RADIUS_NOPPO);			//�L�������W�̏�����
	mCharaData.speed		= 0.f;
	mCharaData.animetion	= 0;									//�A�j���[�V����������ő喇��
	mCharaData.rect_num		= 0;
	mCharaData.alpha		= 0;

	pos_effectfont.x		= pos_effectfont.y =	rand_acc = rand_move_x = mDegSpin = draw_deg = 0.f;
	mCountEffect			= 0;
}

/**
 * ���s
 */
void
ActorYoshi::runImple()
{
	mCountEffect = 0;
	mCharaData.speed = setSpeed();
	mCharaData.animetion = 0;

	if (mCharaData.flag_atk1)
	{
		rand_deg = (float)(rand() % cDegRand + cDegRandMin);
		mCharaData.draw_cc = setAtkPos(RADIUS_YOSHI, G_ATK_1_START_Y);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);
	}
	else if (mCharaData.flag_atk2)
	{
		s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
		rand_acc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
		rand_move_x = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

		mCharaData.draw_cc = setAtkPos(RADIUS_YOSHI, s_atk_start_y);
	}
}

/**
 * @brief �X�V
 */
void
ActorYoshi::update(POS_CC<float> boss_cc, bool boss_death)
{
	//�����蔻��
	if(!mCharaData.flag_death)
	{
		if(!boss_death)
		{
			if(isHit(mCharaData.draw_cc,boss_cc,ID_YOSHI))
			{
				mCharaData.flag_hit		= true;
				mCharaData.flag_death	= true;
				setIsHitCheck(true);
				m_chara_y = mCharaData.draw_cc.y;

				if(mCharaData.flag_atk1)
				{
					if (UtilSound::isPlaying(S_YOSHI_HIP))
					{
						UtilSound::stop(S_YOSHI_HIP);
					}
					UtilSound::playOnce(S_YOSHI_HIP);
				}
				if(mCharaData.flag_atk2)
				{
					if (UtilSound::isPlaying(S_YOSHI_HUSEN))
					{
						UtilSound::stop(S_YOSHI_HUSEN);
					}
					UtilSound::playOnce(S_YOSHI_HUSEN);
				}
			}
		}

		if(mCharaData.flag_atk1)
		{
			if(mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
			{
				mCharaData.draw_cc	 = updateAttack1();
				mCharaData.animetion = setAnimetion(ANIME_G_ATK4_YOSHI,mCharaData.animetion,NULL);
			}
		}
		else if(mCharaData.flag_atk2)
		{
			if(mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
			{
				mOrbit->mWave->setSpeed(mCharaData.speed);
				mCharaData.draw_cc	 = updateAttack2();
				mCharaData.animetion = setAnimetion(NULL,mCharaData.animetion,ANIME_S_ATK1_YOSHI);
			}
		}
	}
	else
	{
		deathControl(mSoundStartNum, mRectStartNum);
	}

	//����������̏���
	if(mCharaData.flag_hit){
		//���S���W����ʊO�Ȃ玀�S
		if( (mCharaData.draw_cc.x < -RADIUS_YOSHI) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
			(mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
				mCharaData.flag_death = true;
		}
			
		if(!mCharaData.flag_effectfont){
			if(mCountEffect++ < FONT_SET){
				pos_effectfont = setEffectFont(mCharaData.draw_cc, RADIUS_YOSHI,POS_HITFONT_X);
				mCharaData.flag_effectfont	= true;
			}	
		}
		else{
			if(mCountEffect++ < FONT_DELETE){
				pos_effectfont = setEffectShake(SHAKE_X,SHAKE_Y,pos_effectfont);
			}
			else{ mCharaData.flag_effectfont = false; mCountEffect = 0;}
		}
	}
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

	mCharaData.rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief �t�H���g�̕`�揈��
 */
void
ActorYoshi::drawEffectFont(int rect_startnum)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	int rect_change = 0;

	//�t�H���g�G�t�F�N�g�̕`��(������100�̕�)
	if(mCharaData.flag_hit){
		if(mCountEffect++ < FONT_DELETE){
			if(mCharaData.flag_atk1)		rect_change = 0; 
			else if(mCharaData.flag_atk2)	rect_change = 1;
			mVertex->drawF(pos_effectfont.x,pos_effectfont.y,rect_startnum + rect_change);
		}
	}
}

/**
 * @brief �`�揈��
 */
void
ActorYoshi::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	//�L�����̕`��(������100�̕�)
	if(mCharaData.flag_atk1){
		mVertex->setAngle(0.f);
	}
	else if(mCharaData.flag_atk2){
		if(mCharaData.flag_death_next){
			mVertex->setAngle(mDegSpin += mDegSpin);
		}
		else {
			mVertex->setAngle(0.f);
		}
	}
	mVertex->drawF(mCharaData.draw_cc.x, mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion));

	drawEffectFont(R_YOSHI_BOYO);
}

/**
 * @brief �U������
 */
POS_CC<float>
ActorYoshi::updateAttack2()														//�L�[���͂ɂ�铮�삻��2
{
	mCharaData.draw_cc = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData.draw_cc);

	return mCharaData.draw_cc;
}

/**
 * @brief ���S����
 */
void
ActorYoshi::deathControl(int sound_num, int rect_startnum)
{
//	if(mCharaData.animetion != 0) mCharaData.animetion = 0;

	if(mCharaData.flag_atk1)
	{
		if(!mCharaData.flag_death_next)
		{
			mCharaData.animetion = setAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI),mCharaData.animetion,ANIME_MOTION1_YOSHI);
			if(mCharaData.animetion == 3)
			{
				mCharaData.flag_death_next = true;
			}
		}
		if(mCharaData.flag_death_next)
		{
			mCharaData.animetion = 0;																//�`����Œ�
			mCharaData.rect_num  = ANIME_DEATH_YOSHI;
	
			mCharaData.draw_cc	 = mOrbit->mRebound->orbitRebound(rand_deg,mCharaData.speed,mCharaData.draw_cc);
		}
	}
	else if(mCharaData.flag_atk2)
	{
		if(!mCharaData.flag_death_next)
		{
			mCharaData.animetion = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI),mCharaData.animetion,ANIME_S_ATK2_YOSHI);
			if(mCharaData.animetion == 3)
			{
				mCharaData.flag_death_next = true;
			}
		}
		if(mCharaData.flag_death_next)
		{
			mCharaData.animetion = 0;																//�`����Œ�
			mCharaData.rect_num  = ANIME_DEATH_YOSHI;

			mCharaData.draw_cc	 = mOrbit->mParabora->orbitParabola(rand_acc,rand_move_x,cParaLimitY,mCharaData.draw_cc);
		}
	}

	if( (mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI) )
	{
		mCharaData.flag_atk1  = mCharaData.flag_atk2  = false;
		mCharaData.flag_death = mCharaData.flag_hit	  = false;
		mCharaData.flag_death_next = false;
	}
}