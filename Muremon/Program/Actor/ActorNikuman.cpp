#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

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
		(0.0f), 0, 0, (MAX_ALPHA),
		// �e�t���O
		false, false, false, false, false, false, false, false,
		// ���S���W
		POS_CC<float>(0.f, 0.f),
	};
}

/**
 * @brief �R���X�g���N�^
 */
ActorNikuman::ActorNikuman()
{
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
ActorNikuman::init()								
{
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;

	//praivate�ϐ�
	s_atk_start_y = 0.f;
	//protected�ϐ�
	mDelay		 = mMaxAnimetion = 0;
	mFlagTurn2 = mIsHitCheck  = false;

	//�\����
	mCharaData.flag_atk1		= mCharaData.flag_atk2		 = false;
	mCharaData.flag_death		= mCharaData.flag_deathfade	 = false;
	mCharaData.flag_effect		= mCharaData.flag_effectfont = false;
	mCharaData.flag_hit			= mCharaData.flag_death_next = false;
	mCharaData.draw_cc.x		= (-RADIUS_NOPPO);						//�L�������W�̏�����
	mCharaData.draw_cc.y		= (GAME_GROUND - RADIUS_NOPPO);			//�L�������W�̏�����
	mCharaData.speed			= 0.f;
	mCharaData.animetion		= 0;									//�A�j���[�V����������ő喇��
	mCharaData.rect_num			= 0;
	mCharaData.alpha			= 0;

	pos_effectfont.x	= pos_effectfont.y = rand_acc = rand_move_x = mDegSpin = draw_deg = 0.f;
	mCountEffect = 0;
}

/**
 * ���s
 */
void
ActorNikuman::runImple()
{
	// �U���J�n
	mCountEffect = 0;
	mDegSpin = 0.f;
	mCharaData.animetion = 0;

	if (mCharaData.flag_atk1)
	{
		rand_deg = (float)(rand() % cDegRand + cDegRandMin);
		mCharaData.draw_cc = setAtkPos(RADIUS_NIKU, G_ATK_2_START_Y);
		mCharaData.speed = setSpeed();
		mDegSpin = 0.f;
	}
	else if (mCharaData.flag_atk2)
	{
		s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
		rand_acc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
		rand_move_x = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

		mCharaData.speed = setSpeed();
		mCharaData.draw_cc = setAtkPos(RADIUS_NIKU, s_atk_start_y);
	}
}

/**
 * @brief �X�V
 */
void
ActorNikuman::update(POS_CC<float> boss_cc, bool boss_death)
{
	//�����蔻��
	if(!mCharaData.flag_death){
		if(!boss_death){
			if(isHit(mCharaData.draw_cc,boss_cc,ID_NIKUMAN)){
				UtilSound::playOnce(S_NIKUMAN);
				mCharaData.flag_hit		= true;
				mCharaData.flag_death	= true;	
				setIsHitCheck(true);
				m_chara_y = mCharaData.draw_cc.y;
			}
		}

		if(mCharaData.flag_atk1){
			if(mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth){
				mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NIKU,mCharaData.animetion,NULL);
				mCharaData.draw_cc	 = updateAttack1();
			}
		}
		else if(mCharaData.flag_atk2){
			if(mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth){
				mCharaData.animetion = setAnimetion(NULL,mCharaData.animetion,ANIME_S_ATK1_NIKU);
				mCharaData.draw_cc	 = updateAttack2(boss_cc);
			}
		}
	}
	else deathControl(mSoundStartNum,mRectStartNum);


	//����������̏���
	if(mCharaData.flag_hit){
		//���S���W����ʊO�Ȃ玀�S
		if( (mCharaData.draw_cc.x < -RADIUS_NIKU)  || (mCharaData.draw_cc.x > cWindowWidth  + RADIUS_NIKU) &&
			(mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
				mCharaData.flag_death = true;
		}

		if(!mCharaData.flag_effectfont){
			if(mCountEffect++ < FONT_SET){
				pos_effectfont = setEffectFont(mCharaData.draw_cc,RADIUS_NIKU,POS_HITFONT_X);
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

	mCharaData.rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief �t�H���g�̕`�揈��
 */
void
ActorNikuman::drawEffectFont(int rect_startnum)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	//�t�H���g�G�t�F�N�g�̕`��(������100�̕�)
	if(mCharaData.flag_hit){
		if(mCountEffect++ < FONT_DELETE){
			mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
			mVertex->drawF(pos_effectfont.x,pos_effectfont.y,rect_startnum);
		}
	}
}

/**
 * @brief �`�揈��
 */
void
ActorNikuman::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(draw_deg += mDegSpin);
	mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
	mVertex->drawF(mCharaData.draw_cc.x,mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion) );

	drawEffectFont(R_NIKU_BETYA);
}

/**
 * @brief �U������
 */
POS_CC<float>
ActorNikuman::updateAttack2(POS_CC<float> boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mCharaData.draw_cc.x - (boss_cc.x + RADIUS_NIKU));
	range_y = fabsf(mCharaData.draw_cc.y - boss_cc.y);

	plus_x = (range_x / mCharaData.speed);
	plus_y = (range_y / mCharaData.speed);

	mCharaData.draw_cc.x += plus_x;								//���S�Ɍ������ĉE�Ɉړ�
	mCharaData.draw_cc.y += plus_y;								//���S�Ɍ������ĉ��Ɉړ�

	return mCharaData.draw_cc;
}

/**
 * @brief ���S����
 */
void
ActorNikuman::deathControl(int sound_num, int rect_startnum)
{
	mCharaData.animetion = 0;
	mCharaData.animetion	= setAnimetion(NULL,mCharaData.animetion,ANIME_DEATH_NIKU);

	if(mCharaData.flag_atk1){
		mCharaData.draw_cc  = mOrbit->mRebound->orbitRebound(rand_deg,mCharaData.speed,mCharaData.draw_cc);
	}
	else if(mCharaData.flag_atk2){
		mCharaData.draw_cc  = mOrbit->mParabora->orbitParabola(rand_acc,rand_move_x,cParaLimitY,mCharaData.draw_cc);	
	}

	if( (mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
		mCharaData.flag_atk1  = false;
		mCharaData.flag_atk2  = false;
		mCharaData.flag_death = false;
		mCharaData.flag_hit	= false;
		mDegSpin				= 0.f;
	}
}