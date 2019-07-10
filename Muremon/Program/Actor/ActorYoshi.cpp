#include "ActorYoshi.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"

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
		(-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI),
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
	mOrbit->mWave->init(cWaveAmplit,cWaveCycle,NULL,WAVE_MODE_GAME);

	//praivate�ϐ�
	s_atk_start_y = 0.f;
	//protected�ϐ�
	mRandSpeed	 = 0.f;
	mDelay		 = mMaxAnimetion = mCharaNum = 0;
	mFlagTurn2 = mIsHitCheck  = false;
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//�\����
		mCharaData[i].flag_atk1		= mCharaData[i].flag_atk2		 = false;
		mCharaData[i].flag_death		= mCharaData[i].flag_deathfade	 = false;
		mCharaData[i].flag_effect		= mCharaData[i].flag_effectfont = false;
		mCharaData[i].flag_hit			= mCharaData[i].flag_death_next = false;
		mCharaData[i].draw_cc.x		= (-RADIUS_NOPPO);						//�L�������W�̏�����
		mCharaData[i].draw_cc.y		= (GAME_GROUND - RADIUS_NOPPO);			//�L�������W�̏�����
		mCharaData[i].speed			= 0.f;
		mCharaData[i].animetion		= 0;									//�A�j���[�V����������ő喇��
		mCharaData[i].rect_num			= 0;
		mCharaData[i].alpha			= 0;

		pos_effectfont[i].x	= pos_effectfont[i].y =	rand_acc[i] = rand_move_x[i] = mDegSpin[i] = draw_deg[i] = 0.f;
		mCountEffect[i]				= 0;
		mInit[i]							= true;
	}
}

/**
 * @brief �X�V
 */
void
ActorYoshi::update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death)
{
	mRandSpeed = 0.f;

	// �U���J�n
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		if(mFlagTurn2)
		{
			mCharaData[mCharaNum]	= cInitActorData;
			mCountEffect[mCharaNum] = 0;
			mInit[mCharaNum] = true;
		}
		mCharaData[mCharaNum]		= setAtkFlag(mCharaData[mCharaNum]);
		mCharaData[mCharaNum].speed  = setSpeed();

		if (UtilBattle::isRunMediumGroundAttack())
		{
			rand_deg[mCharaNum] = (float)(rand() % cDegRand + cDegRandMin);
			mCharaData[mCharaNum].draw_cc = setAtkPos(RADIUS_YOSHI, G_ATK_1_START_Y);
			mDegSpin[mCharaNum] = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);
		}
		else if (UtilBattle::isRunMediumSkyAttack())
		{
			s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
			rand_acc[mCharaNum] = (float)(rand() % cParaRandAcc + cParaRandAccMin);
			rand_move_x[mCharaNum] = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
			mDegSpin[mCharaNum] = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

			mCharaData[mCharaNum].draw_cc = setAtkPos(RADIUS_YOSHI, s_atk_start_y);
		}

		if(mCharaNum >= (MAX_VALLUE_PLAYER-1) ){ mCharaNum = 0; mFlagTurn2 = true; }	//�ő吔�𒴂�����1�̖ڂ�			
		else mCharaNum++;																//2�̖ځA3�̖ځ`
	}

	// �L�����̓���(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//�����蔻��
		if(!mCharaData[i].flag_death){
			if(!boss_death){
				if(isHit(mCharaData[i].draw_cc,boss_cc,ID_YOSHI)){
					mCharaData[i].flag_hit		= true;
					mCharaData[i].flag_death	= true;
					setIsHitCheck(true);
					m_chara_y = mCharaData[i].draw_cc.y;

					if(mCharaData[i].flag_atk1){
						if (UtilSound::isPlaying(S_YOSHI_HIP))
						{
							UtilSound::stop(S_YOSHI_HIP);
						}
						UtilSound::playOnce(S_YOSHI_HIP);
					}
					if(mCharaData[i].flag_atk2){
						if (UtilSound::isPlaying(S_YOSHI_HUSEN))
						{
							UtilSound::stop(S_YOSHI_HUSEN);
						}
						UtilSound::playOnce(S_YOSHI_HUSEN);
					}
				}
			}

			if(mCharaData[i].flag_atk1){
				if(mCharaData[i].draw_cc.x - RADIUS_YOSHI < cWindowWidth){
					mCharaData[i].draw_cc	 = updateAttack1(i);
					mCharaData[i].animetion = setAnimetion(ANIME_G_ATK4_YOSHI,mCharaData[i].animetion,NULL,i);
				}
			}
			else if(mCharaData[i].flag_atk2){
				if(mCharaData[i].draw_cc.x - RADIUS_YOSHI < cWindowWidth){
					mOrbit->mWave->setSpeed(mCharaData[i].speed);
					mCharaData[i].draw_cc	 = updateAttack2(i);
					mCharaData[i].animetion = setAnimetion(NULL,mCharaData[i].animetion,ANIME_S_ATK1_YOSHI,i);
				}
			}
		}
		else deathControl(i,sound_startnum,rect_startnum);

		//����������̏���
		if(mCharaData[i].flag_hit){
			//���S���W����ʊO�Ȃ玀�S
			if( (mCharaData[i].draw_cc.x < -RADIUS_YOSHI) || (mCharaData[i].draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
				(mCharaData[i].draw_cc.y < -RADIUS_YOSHI) || (mCharaData[i].draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
					mCharaData[i].flag_death = true;
			}
			
			if(!mCharaData[i].flag_effectfont){
				if(mCountEffect[i]++ < FONT_SET){
					pos_effectfont[i] = setEffectFont(mCharaData[i].draw_cc, RADIUS_YOSHI,POS_HITFONT_X);
					mCharaData[i].flag_effectfont	= true;
				}	
			}
			else{
				if(mCountEffect[i]++ < FONT_DELETE){
					pos_effectfont[i] = setEffectShake(SHAKE_X,SHAKE_Y,pos_effectfont[i]);
				}
				else{ mCharaData[i].flag_effectfont = false; mCountEffect[i] = 0;}
			}
		}
	}
}

/**
 * @brief �A�j���ݒ�
 */
int
ActorYoshi::setAnimetion(int max_animetion, int anime_count ,int rect_num ,int mCharaNum)
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

	mCharaData[mCharaNum].rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief �t�H���g�̕`�揈��
 */
void
ActorYoshi::drawEffectFont(int rect_startnum)
{
	mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), GetGraphicsDevice());

	int rect_change = 0;

	//�t�H���g�G�t�F�N�g�̕`��(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_hit){
			if(mCountEffect[i]++ < FONT_DELETE){
				if(mCharaData[i].flag_atk1)		rect_change = 0; 
				else if(mCharaData[i].flag_atk2)	rect_change = 1;
				mVertex->drawF(pos_effectfont[i].x,pos_effectfont[i].y,rect_startnum + rect_change);
			}
		}
	}
}

/**
 * @brief �`�揈��
 */
void
ActorYoshi::draw(int rect_startnum)
{
	mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_YOSHI), GetGraphicsDevice());

	//�L�����̕`��(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_atk1){
			mVertex->setAngle(0.f);
		}
		else if(mCharaData[i].flag_atk2){
			if(mCharaData[i].flag_death_next){
				mVertex->setAngle(mDegSpin[i] += mDegSpin[i]);
			}
			else {
				mVertex->setAngle(0.f);
			}
		}
		mVertex->drawF(mCharaData[i].draw_cc.x, mCharaData[i].draw_cc.y, (rect_startnum + mCharaData[i].rect_num + mCharaData[i].animetion));
	}
}

/**
 * @brief �U������
 */
POS_CC<float>
ActorYoshi::updateAttack2(int mCharaNum)														//�L�[���͂ɂ�铮�삻��2
{
	mCharaData[mCharaNum].draw_cc = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData[mCharaNum].draw_cc,mCharaNum);

	return mCharaData[mCharaNum].draw_cc;
}

/**
 * @brief ���S����
 */
void
ActorYoshi::deathControl(int mCharaNum, int sound_num, int rect_startnum)						//���S����
{

	if(mInit[mCharaNum]){
		if(mCharaData[mCharaNum].animetion != 0) mCharaData[mCharaNum].animetion = 0;
		mInit[mCharaNum] = false;
	}
	if(mCharaData[mCharaNum].flag_atk1){
		if(!mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = setAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI),mCharaData[mCharaNum].animetion,ANIME_MOTION1_YOSHI,mCharaNum);
			if(mCharaData[mCharaNum].animetion == 3){
				mCharaData[mCharaNum].flag_death_next = true;
			}
		}
		if(mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = 0;																//�`����Œ�
			mCharaData[mCharaNum].rect_num  = ANIME_DEATH_YOSHI;
	
			mCharaData[mCharaNum].draw_cc	 = mOrbit->mRebound->orbitRebound(rand_deg[mCharaNum],mCharaData[mCharaNum].speed,mCharaData[mCharaNum].draw_cc);
		}
	}
	else if(mCharaData[mCharaNum].flag_atk2){
		if(!mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI),mCharaData[mCharaNum].animetion,ANIME_S_ATK2_YOSHI,mCharaNum);
			if(mCharaData[mCharaNum].animetion == 3){
				mCharaData[mCharaNum].flag_death_next = true;
			}
		}
		if(mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = 0;																//�`����Œ�
			mCharaData[mCharaNum].rect_num  = ANIME_DEATH_YOSHI;

			mCharaData[mCharaNum].draw_cc	 = mOrbit->mParabora->orbitParabola(rand_acc[mCharaNum],rand_move_x[mCharaNum],cParaLimitY,mCharaData[mCharaNum].draw_cc,mCharaNum);
		}
	}

	if( (mCharaData[mCharaNum].draw_cc.y < -RADIUS_YOSHI) || (mCharaData[mCharaNum].draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
		mCharaData[mCharaNum].flag_atk1  = mCharaData[mCharaNum].flag_atk2  = false;
		mCharaData[mCharaNum].flag_death = mCharaData[mCharaNum].flag_hit	  = false;
		mCharaData[mCharaNum].flag_death_next = false;
	}
}