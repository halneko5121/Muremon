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
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorMgr.h"
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
	, mBoss(nullptr)
	, mStartAlpha(0)
	, mGameState(G_START_SCENE)
	, mNikumanKeyCount(0)
	, mYoshitaroKeyCount(0)
	, mNoppoKeyCount(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
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
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// �v���C���[3��ޕ�
	for (int actor_id = cActorId_Noppo; actor_id < cActorId_Count; actor_id++)
	{
		// �e�ő吔����
		for (int j = 0; j < MAX_VALLUE_PLAYER; j++)
		{
			mActor[actor_id][j] = GetActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}
	mBoss = new ActorBoss(mTexture, mVertex);

	GetActorMgr()->init();
	mBoss->init();

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
		
		// �A�N�^�[�̕`��
		GetActorMgr()->draw();
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//�̗̓Q�[�W�g

		// �G�t�F�N�g�`��
		GetEffectMgr()->draw();
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
	float num = mBoss->mLife / mBoss->mMaxLife;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,255,0,0);
	mVertex->drawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//�̗̓Q�[�W
}

void SceneGameRefresh::drawHitEffect()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF((float)mBoss->mMoveX - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}

ActorBase*
SceneGameRefresh::getActorNikuman(int index)
{
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameRefresh::getActorYoshi(int index)
{
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameRefresh::getActorNoppo(int index)
{
	return mActor[cActorId_Noppo][index];
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
	boss_cc.x = mBoss->mMoveX;
	boss_cc.y = mBoss->mMoveY;

	UtilSound::playLoop(S_BGM_BATTLE);

	// �ɂ��܂�
	if (UtilBattle::isRunWeakGroundAttack())
	{
		ActorBase* actor = getActorNikuman(mNikumanCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunWeakSkyAttack())
	{
		ActorBase* actor = getActorNikuman(mNikumanCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}

	// �悵���낤
	if (UtilBattle::isRunMediumGroundAttack())
	{
		ActorBase* actor = getActorYoshi(mYoshitaroCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunMediumSkyAttack())
	{
		ActorBase* actor = getActorYoshi(mYoshitaroCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}

	// �̂���
	if (UtilBattle::isRunStrongGroundAttack())
	{
		ActorBase* actor = getActorNoppo(mNoppoCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunStrongSkyAttack())
	{
		ActorBase* actor = getActorNoppo(mNoppoCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}

	// �A�N�^�[�̍X�V
	GetActorMgr()->update(boss_cc);

	// �G�t�F�N�g�̍X�V
	GetEffectMgr()->update();

	// �q�b�g�`�F�b�N
	ActorMgr::ActorIterator it_begin = GetActorMgr()->begin();
	ActorMgr::ActorIterator it_end = GetActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		// ���܂�
		ActorNikuman* actor_nikuman = dynamic_cast<ActorNikuman*>(actor);
		if (actor_nikuman != nullptr)
		{
			if (actor->isHitCheck())
			{
				mIsHitNiku = true;
				mCharaAtkY = actor_nikuman->getHitPosY();
				actor_nikuman->setIsHitCheck(false);
			}
			else
			{
				mIsHitNiku = false;
			}
		}
		// �悵���낤
		ActorYoshi* actor_yoshi = dynamic_cast<ActorYoshi*>(actor);
		if (actor_yoshi != nullptr)
		{
			if (actor->isHitCheck())
			{
				mIsHitYoshi = true;
				mCharaAtkY = actor_yoshi->getHitPosY();
				actor_yoshi->setIsHitCheck(false);
			}
			else
			{
				mIsHitYoshi = false;
			}
		}
		// �̂���
		ActorNoppo* actor_noppo = dynamic_cast<ActorNoppo*>(actor);
		if (actor_noppo != nullptr)
		{
			if (actor->isHitCheck())
			{
				mIsHitNoppo = true;
				mCharaAtkY = actor_noppo->getHitPosY();
				actor_noppo->setIsHitCheck(false);
			}
			else
			{
				mIsHitNoppo = false;
			}
		}
	}

	if (mIsHitNiku)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NIKUMAN_DAMAGE;
		mIsHitEffect = true;
	}

	if (mIsHitYoshi)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= YOSHITARO_DAMAGE;
		mIsHitEffect = true;
	}

	if (mIsHitNoppo)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NOPPO_DAMAGE;
		mIsHitEffect = true;
	}

	// �ɂ��܂�
	if (UtilBattle::isRunWeakGroundAttack() ||
		UtilBattle::isRunWeakSkyAttack())
	{
		mNikumanKeyCount++;
		mNikumanCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mNikumanCurrentIndex)
		{
			mNikumanCurrentIndex = 0;
		}
	}
	// �悵���낤
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		mYoshitaroKeyCount++;
		mYoshitaroCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mYoshitaroCurrentIndex)
		{
			mYoshitaroCurrentIndex = 0;
		}
	}
	// �̂���
	if (UtilBattle::isRunStrongGroundAttack() ||
		UtilBattle::isRunStrongSkyAttack())
	{
		mNoppoKeyCount++;
		mNoppoCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mNoppoCurrentIndex)
		{
			mNoppoCurrentIndex = 0;
		}
	}

	if (GetAsyncKeyState(VK_RETURN)) {	//�G���^�[�L�[�������ꂽ��^�C�g���ɖ߂�
		mIsSceneEnd = true;
	}

	mBoss->control(PLAY_REFRESH);

	if (!mBoss->mIsDeath)
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