/******************************************************************
 *	@file	SceneGameRefresh.cpp
 *	@brief	�Q�[���V�[���i���t���b�V���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneGameRefresh.h"

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"

namespace
{
	POS_CC<float> boss_cc = { 600, 350 };

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_ReadyFadeIn,		// �����t�F�[�h�C��
		cState_Ready,			// ����
		cState_ReadyFadeOut,	// �����t�F�[�h�A�E�g
		cState_Game,			// �Q�[����
		cState_GameOver,		// �Q�[���I�[�o�[
		cState_GameClear,		// �Q�[���N���A
		cState_Count
	};
}

SceneGameRefresh::SceneGameRefresh()
	: mState()
	, mNiku(nullptr)
	, mNoppo(nullptr)
	, mYoshi(nullptr)
	, mBoss(nullptr)
	, mStartAlpha(0)
	, mGameState(G_START_SCENE)
	, mNikumanKeyCount(0)
	, mYoshitaroKeyCount(0)
	, mNoppoKeyCount(0)
	, mIsHitNiku(false)
	, mIsHitYoshi(false)
	, mIsHitNoppo(false)
	, mIsHitEffect(false)
	, mHitEffectAlpha(0)
	, mHitEffectTime(0)
	, mCharaAtkY(0)
{
	mState.initialize(cState_Count, cState_Idle);
	mState.registState(this, &SceneGameRefresh::stateEnterIdle,			&SceneGameRefresh::stateExeIdle,		nullptr, cState_Idle);
	mState.registState(this, &SceneGameRefresh::stateEnterReadyFadeIn,	&SceneGameRefresh::stateExeReadyFadeIn, nullptr, cState_ReadyFadeIn);
	mState.registState(this, &SceneGameRefresh::stateEnterReady,		&SceneGameRefresh::stateExeReady,		nullptr, cState_Ready);
	mState.registState(this, &SceneGameRefresh::stateEnterReadyFadeOut,	&SceneGameRefresh::stateExeReadyFadeOut,nullptr, cState_ReadyFadeOut);
	mState.registState(this, &SceneGameRefresh::stateEnterGame,			&SceneGameRefresh::stateExeGame,		nullptr, cState_Game);
	mState.registState(this, &SceneGameRefresh::stateEnterGameOver,		&SceneGameRefresh::stateExeGameOver,	nullptr, cState_GameOver);
	mState.registState(this, &SceneGameRefresh::stateEnterGameClear,	&SceneGameRefresh::stateExeGameClear,	nullptr, cState_GameClear);
	mState.changeState(cState_Idle);
}

SceneGameRefresh::~SceneGameRefresh(void)
{
}

void SceneGameRefresh::impleInit()
{
	mNiku	= new ActorNikuman();
	mNoppo	= new ActorNoppo();
	mYoshi	= new ActorYoshi();

	mNiku->init();
	mNoppo->init();
	mYoshi->init();

	mBoss = new ActorBoss();
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	mState.changeState(cState_ReadyFadeIn);
}

void SceneGameRefresh::update()
{
	mState.executeState();
}

void SceneGameRefresh::draw()
{
	if(mGameState == G_START_SCENE){
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);
		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//�X�e�[�^�X�g�`��
		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);				//�ɂ��܂��
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);			//�悵���낤��
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);					//�̂��ۊ�

		drawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);								//��������̗̑�
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);					//�̗̓Q�[�W

		drawHpGauge();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

		// �̗̓Q�[�W�g
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);

		// �Q�[���X�^�[�g
		mVertex->setColor(mStartAlpha,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_START);
	}
	else if(mGameState == G_GAME_SCENE){

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);	//�w�i
		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);	//��

		mBoss->draw();
		mBoss->fallDraw();

		drawHitEffect();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//�X�e�[�^�X�g�`��
		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//�ɂ��܂��
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//�悵���낤��
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//�̂��ۊ�

		drawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);	//��������̗̑�
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//�̗̓Q�[�W

		drawHpGauge();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//�̗̓Q�[�W�g

		//�L�����B
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

		mNoppo->draw(R_NOPPO_G_ATK1);
		mYoshi->draw(R_YOSHI_G_ATK1);
		mNiku->draw(R_NIKU_G_ATK1);

		//�G�t�F�N�g�t�H���g��
		mNoppo->drawEffectFont(R_NOPPO_PETI);
		mYoshi->drawEffectFont(R_YOSHI_BOYO);
		mNiku->drawEffectFont(R_NIKU_BETYA);

		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//�̗̓Q�[�W�g
	}
}

void SceneGameRefresh::end()
{
	//�^�C�g����
	requestChangeScene(cSceneName_Title);

	UtilSound::stop(S_BGM_BATTLE);

	mTexture->release();
	mVertex->release();
}

void SceneGameRefresh::drawNum()
{
	//�ɂ��܂�
	for(int i = 0;i < 4;i++){
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//�悵���낤
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//�̂���
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void SceneGameRefresh::drawHpGauge()
{
	float num = mBoss->boss_life / mBoss->max_boss_life;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,255,0,0);
	mVertex->drawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//�̗̓Q�[�W
}

void SceneGameRefresh::drawHitEffect()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF((float)mBoss->boss_move_x - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}

void SceneGameRefresh::initHitFlag()
{
	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
SceneGameRefresh::stateEnterIdle()
{
}
void
SceneGameRefresh::stateExeIdle()
{
}

/**
 * @brief �X�e�[�g:ReadyFadeIn
 */
void
SceneGameRefresh::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(S_GAME_START);
}
void
SceneGameRefresh::stateExeReadyFadeIn()
{
	mStartAlpha += (G_ALPHA_INCREASE - 5);
	if (mStartAlpha >= G_MAX_ALPHA)
	{
		mStartAlpha = G_MAX_ALPHA;
		mState.changeState(cState_Ready);
		return;
	}
}

/**
 * @brief �X�e�[�g:Ready
 */
void
SceneGameRefresh::stateEnterReady()
{
}
void
SceneGameRefresh::stateExeReady()
{
	if (60 < mState.getStateCount())
	{
		mState.changeState(cState_ReadyFadeOut);
		return;
	}
}

/**
 * @brief �X�e�[�g:ReadyFadeOut
 */
void
SceneGameRefresh::stateEnterReadyFadeOut()
{
}
void
SceneGameRefresh::stateExeReadyFadeOut()
{
	mStartAlpha -= (G_ALPHA_INCREASE - 10);
	if (mStartAlpha < 0)
	{
		mStartAlpha = 0;
		mGameState = G_GAME_SCENE;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief �X�e�[�g:Game
 */
void
SceneGameRefresh::stateEnterGame()
{
}
void
SceneGameRefresh::stateExeGame()
{
	boss_cc.x = mBoss->boss_move_x;
	boss_cc.y = mBoss->boss_move_y;

	UtilSound::playLoop(S_BGM_BATTLE);

	mNiku->update(boss_cc, S_NIKUMAN, R_NIKU_G_ATK1, mBoss->boss_fall_flag);

	mYoshi->update(boss_cc, S_YOSHI_HIP, R_YOSHI_G_ATK1, mBoss->boss_fall_flag);

	mNoppo->update(boss_cc, S_NOPPO_KOKE, R_NOPPO_G_ATK1, mBoss->boss_fall_flag);

	mIsHitNiku = mNiku->isHitCheck();//���������Ƃ����t���O���A���Ă��܂�

	mIsHitYoshi = mYoshi->isHitCheck();//����������ă_���[�W�Ȃǂ�

	mIsHitNoppo = mNoppo->isHitCheck();//���f�����Ă�������

	if (mIsHitNiku)
	{
		mBoss->hit_count++;
		mBoss->boss_life -= NIKUMAN_DAMAGE;
		mIsHitEffect = true;
		mCharaAtkY = mNiku->m_chara_y;
		mNiku->setIsHitCheck(false);
	}

	if (mIsHitYoshi)
	{
		mBoss->hit_count++;
		mBoss->boss_life -= YOSHITARO_DAMAGE;
		mIsHitEffect = true;
		mCharaAtkY = mYoshi->m_chara_y;
		mYoshi->setIsHitCheck(false);
	}

	if (mIsHitNoppo)
	{
		mBoss->hit_count++;
		mBoss->boss_life -= NOPPO_DAMAGE;
		mIsHitEffect = true;
		mCharaAtkY = mNoppo->m_chara_y;
		mNoppo->setIsHitCheck(false);
	}

	// �ɂ��܂�
	if (UtilBattle::isRunWeakGroundAttack() ||
		UtilBattle::isRunWeakSkyAttack())
	{
		mNikumanKeyCount++;
	}
	// �悵���낤
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		mYoshitaroKeyCount++;
	}
	// �̂���
	if (UtilBattle::isRunStrongGroundAttack() ||
		UtilBattle::isRunStrongSkyAttack())
	{
		mNoppoKeyCount++;
	}

	if (GetAsyncKeyState(VK_RETURN)) {	//�G���^�[�L�[�������ꂽ��^�C�g���ɖ߂�
		mIsSceneEnd = true;
	}

	mBoss->control(PLAY_REFRESH);

	if (!mBoss->boss_fall_flag)
	{
		if (mIsHitEffect)
		{
			mHitEffectAlpha = 255;
			mHitEffectTime++;
			if (mHitEffectTime == 1)
			{
				mIsHitEffect = false;
				mHitEffectTime = 0;
			}
		}
		else {
			mHitEffectAlpha = 0;
			mHitEffectTime = 0;
		}
	}
	else 
	{
		mIsHitEffect = false;
		mHitEffectAlpha = 0;
	}
}

/**
 * @brief �X�e�[�g:GameOver
 */
void
SceneGameRefresh::stateEnterGameOver()
{
}
void
SceneGameRefresh::stateExeGameOver()
{
}

/**
 * @brief �X�e�[�g:GameClear
 */
void
SceneGameRefresh::stateEnterGameClear()
{
}
void
SceneGameRefresh::stateExeGameClear()
{
}