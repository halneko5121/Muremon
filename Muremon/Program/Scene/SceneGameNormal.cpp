/******************************************************************
 *	@file	SceneGameNormal.cpp
 *	@brief	�Q�[���V�[���i�m�[�}���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "SceneGameNormal.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Mission/Mission.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/UI/UINormalGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/DefineGame.h"

namespace
{
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

	const int cTimeLimitCount = 10800;					// ��������(���@3:00)
	const int cMissionClearAddScore = 50000;			// �~�b�V�����N���A���Z�X�R�A
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	// ���`
	const Vector2f cWaveInitPos = { -500.0f, 300.0f };
	const float cWaveSpeedX = ((800.f + 500.f + 500.f) / (60.f * 3.5f));
	const float cWaveUpY = (60.f / (60.f * 3.5f));
	const int cMaxMissionGauge = 5000;

	enum NEGATIVE_DATA
	{
		NO_NEGATIVE,
		SPEED_UP,
		RECOVER,
		SLIDE_IN,
		ATTACK_DOWN,
	};

	Vector2f boss_cc2 = { 600, 350 };

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_ReadyFadeIn,		// �����t�F�[�h�C��
		cState_Ready,			// ����
		cState_ReadyFadeOut,	// �����t�F�[�h�A�E�g
		cState_Game,			// �Q�[����
		cState_GameOver,		// �Q�[���I�[�o�[
		cState_TimeOver,		// �^�C���I�[�o�[
		cState_Count
	};
}

/**
 * @brief	�R���X�g���N�^
 */
SceneGameNormal::SceneGameNormal()
	: mState()
	, mMission(nullptr)
	, mBoss(nullptr)
	, mUINormalGame(nullptr)
	, mTime(cTimeLimitCount)
	, mIsPose(false)
	, mGameStateFontAlpha(0)
	, mGameStateRectNum(0)
	, mMissionStateKeep(0)
	, mIsInit(false)
	, mMissionGauge(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
	, mAlphaFont(0)
	, mTimeCount(0)
	, mWavePos(cWaveInitPos)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeAtkLv(0)
{
	mUINormalGame = new UINormalGame();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Game,			cState_Game);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, GameOver,		cState_GameOver);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, TimeOver,		cState_TimeOver);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
SceneGameNormal::~SceneGameNormal()
{
}

/**
 * @brief	������
 */
void
SceneGameNormal::impleInit()
{
	UtilGame::setGameModeNormal();
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// �v���C���[3��ޕ�
	for (int actor_id = cActorId_Noppo; actor_id <= cActorId_Yoshi; actor_id++)
	{
		// �e�ő吔����
		for (int j = 0; j < cMaxPlayerCount; j++)
		{
			mActor[actor_id][j] = GetActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}
	// �{�X
	mBoss = dynamic_cast<ActorBoss*>(GetActorMgr()->createActor(cActorId_Boss, mTexture, mVertex));

	// ������
	GetActorMgr()->init();

	mUINormalGame->init();

	mMission = new Mission(mTexture, mVertex);

	mState.changeState(cState_ReadyFadeIn);
}

/**
 * @brief	�X�V
 */
void
SceneGameNormal::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
SceneGameNormal::draw()
{
	// �w�i
	drawBg();

	if (mState.isEqual(cState_Game))
	{
		// �A�N�^�[�̕`��
		GetActorMgr()->draw();

		// �G�t�F�N�g�`��
		GetEffectMgr()->draw();
	}
	else
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mGameStateFontAlpha, 255, 255, 255);
		mVertex->drawF(cDispBgPos, mGameStateRectNum);
	}

	if(mMissionStateKeep == MISSION_OUGI)
	{
		drawMissionOugi();
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE)
	{
		drawMissionNegative();
	}

	mUINormalGame->draw(*mBoss, mMissionGauge, mTime);

	mMission->draw();
}

/**
 * @brief	�V�[���I��
 */
void
SceneGameNormal::end()
{
	//�Q�[���I�[�o�[�̏ꍇ
	requestChangeScene(cSceneName_Ranking);

	mTexture->release();
	mVertex->release();
	delete mMission;
}

/**
 * @brief �U���J�n�̍X�V
 */
void 
SceneGameNormal::updateRunAtk()
{
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
}

/**
 * @brief	�w�i�`��
 */
void
SceneGameNormal::drawBg()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(cDispBgPos, R_GAME_BG);
	mVertex->drawF(cDispFlagPos, R_FLAG);
}

/**
 * @brief	�A�N�V�f���g���`�̍X�V
 */
void
SceneGameNormal::updateMissionOugi()
{
	if(mTimeCount >= 0 && 60 > mTimeCount){
		mAlphaFont += 5;
		if(mAlphaFont > 255){
			mAlphaFont = 255;
		}
	}
	else if(mTimeCount >= 60 && 120 > mTimeCount){
		mAlphaFont = 255;
	}
	else if(mTimeCount >= 120 && 180 > mTimeCount){
		mAlphaFont -= 5;
		if(mAlphaFont < 0){
			mAlphaFont = 0;
		}
	}
	else if(mTimeCount >= 180 && 210 > mTimeCount){
		if(mTimeCount == 180){
			UtilSound::playOnce(S_NAMI);
		}
	}
	else if(mTimeCount >= 210 && 420 > mTimeCount){		//�g�𓮂���(3.5sec)
		mWavePos.x += cWaveSpeedX;
		mWavePos.y -= cWaveUpY;
		if(mTimeCount % 10 <= 4){
			mWavePos.y -= 2.f;
		}
		else if(mTimeCount % 10 <= 9){
			mWavePos.y += 2.f;
		}
	}
	else if(mTimeCount >= 420 && 450 > mTimeCount){
	}
	else if(mTimeCount >= 450 && 630 > mTimeCount){
	}
	if(mTimeCount > 630){
		mBoss->mLife -= 7000;
		recover();
		mMissionStateKeep = MISSION_END;
		mWavePos = cWaveInitPos;
		UtilGame::addScore(cMissionClearAddScore);
	}
	mTimeCount++;
}

/**
 * @brief	�A�N�V�f���g���`�̕`��
 */
void
SceneGameNormal::drawMissionOugi()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont,255,255,255);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.0f), R_OUGI_FONT);

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->drawF(Vector2f(mWavePos.x, mWavePos.y), R_OUGI);
}

/**
 * @brief	�~�b�V�������s���̍X�V
 */
void
SceneGameNormal::updateMissionNegative()
{
	selectNegative();

	mNegativeState = SLIDE_IN;

	if(mTimeCount >= 0 && 60 > mTimeCount){
		mAlphaFont += 5;
		if(mAlphaFont > 255){
			mAlphaFont = 255;
		}
	}
	else if(mTimeCount >= 60 && 120 > mTimeCount){
		mAlphaFont = 255;
	}
	else if(mTimeCount >= 120 && 180 > mTimeCount){
		mAlphaFont -= 5;
		if(mAlphaFont < 0){
			mAlphaFont = 0;
		}
	}
	else if(mTimeCount >= 180){
		switch(mNegativeState)
		{
		case SPEED_UP:
			mBoss->mSpeedX = 3;
			break;
		case RECOVER:
			mBoss->mLife = mBoss->mMaxLife;
			break;
		case SLIDE_IN:
			mBoss->mMoveX = 500;
			break;
		case ATTACK_DOWN:
			mNegativeAtkLv++;
			break;
		}
		mMissionStateKeep = MISSION_END;
	}
	mTimeCount++;
}

/**
 * @brief	�~�b�V�������s���̕`��
 */
void
SceneGameNormal::drawMissionNegative()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont,255,255,255);
	mVertex->drawF(Vector2f(400.f, 300.f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.f), R_NEGATIVE1 + mNegativeState - 1);
}

/**
 * @brief	�ǂ̏����ɂ��邩�̔��f
 */
void SceneGameNormal::selectNegative()
{
	if(mNegativeState != 0){
		return ;
	}

	int rand_negative = rand() % 100 + 1;
	if(rand_negative > 0 && rand_negative <= cNegativePar1){
		mNegativeState = SPEED_UP;
	}
	else if(rand_negative > cNegativePar1 && rand_negative <= cNegativePar2){
		mNegativeState = RECOVER;
	}
	else if(rand_negative > cNegativePar2 && rand_negative <= cNegativePar3){
		mNegativeState = SLIDE_IN;
	}
	else if(rand_negative > cNegativePar3 && rand_negative <= cNegativePar4){
		mNegativeState = ATTACK_DOWN;
	}
}

/**
 * @brief	���s�ŉ����������̂̌��ɖ߂�
 */
void
SceneGameNormal::recover()
{
	if(mBoss->mLife <= 0){
		mNegativeAtkLv = 0;
	}
}

ActorBase*
SceneGameNormal::getActorNikuman(int index)
{
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameNormal::getActorYoshi(int index)
{
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameNormal::getActorNoppo(int index)
{
	return mActor[cActorId_Noppo][index];
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
SceneGameNormal::stateEnterIdle()
{
}
void
SceneGameNormal::stateIdle()
{
}

/**
 * @brief �X�e�[�g:ReadyFadeIn
 */
void
SceneGameNormal::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(S_GAME_START);
	mGameStateRectNum = R_GAME_START;
}
void
SceneGameNormal::stateReadyFadeIn()
{
	mGameStateFontAlpha += (cAlphaIncrease - 5);
	if (mGameStateFontAlpha >= 255)
	{
		mGameStateFontAlpha = 255;
		mState.changeState(cState_Ready);
		return;
	}
}

/**
 * @brief �X�e�[�g:Ready
 */
void
SceneGameNormal::stateEnterReady()
{
}
void
SceneGameNormal::stateReady()
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
SceneGameNormal::stateEnterReadyFadeOut()
{
}
void
SceneGameNormal::stateReadyFadeOut()
{
	mGameStateFontAlpha -= (cAlphaIncrease - 10);
	if (mGameStateFontAlpha < 0)
	{
		mGameStateFontAlpha = 0;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief �X�e�[�g:Game
 */
void
SceneGameNormal::stateEnterGame()
{
	UtilSound::playLoop(S_BGM_BATTLE);
}
void
SceneGameNormal::stateGame()
{
	boss_cc2.x = mBoss->mMoveX;
	boss_cc2.y = mBoss->mMoveY;

	if ((boss_cc2.x - 150) < 500) {
		UtilSound::playLoop(S_SAIREN);
	}
	else
	{
		UtilSound::stop(S_SAIREN);
	}

	if (UtilInput::isKeyPushedReturn())
	{
		if (mIsPose) {
			mIsPose = false;
		}
		else {
			mIsPose = true;
		}
	}

	if (mIsPose) 
	{
		return;
	}

	//�~�b�V�������N������i�K�܂ł�������
	if (mMissionGauge >= cMaxMissionGauge)
	{
		if (!mIsInit)
		{
			mMission->init(
				UtilBattle::getWeakAtkCount(),
				UtilBattle::getMediumAtkCount(),
				UtilBattle::getStrongAtkCount());
			mIsInit = true;
		}
		if (mMissionStateKeep < MISSION_OUGI) {
			mMission->update();
			mMissionStateKeep = mMission->getMissionState();
			if (UtilBattle::getWeakAtkCount() != mMission->getCountKeyNikuman()) 
			{
				UtilBattle::setWeakAtkCount(mMission->getCountKeyNikuman());
			}
			if (UtilBattle::getMediumAtkCount() != mMission->getCountKeyYoshitaro())
			{
				UtilBattle::setMediumAtkCount(mMission->getCountKeyYoshitaro());
			}
			if (UtilBattle::getStrongAtkCount() != mMission->getCountKeyNoppo())
			{
				UtilBattle::setStrongAtkCount(mMission->getCountKeyNoppo());
			}
		}
		else if (mMissionStateKeep == MISSION_OUGI) {
			updateMissionOugi();
		}
		else if (mMissionStateKeep == MISSION_NEGATIVE) {
			updateMissionNegative();
		}
		else if (mMissionStateKeep == MISSION_END) {
			mNegativeState = NO_NEGATIVE;
			mTimeCount = 0;
			mMissionStateKeep = 0;
			mMissionGauge = 0;
			mIsInit = false;
		}
		return;
	}

	if (mTime == 0)
	{
		mState.changeState(cState_TimeOver);
		return;
	}

	// �e�U���̊J�n
	updateRunAtk();

	// �A�N�^�[�̍X�V
	GetActorMgr()->update(boss_cc2);

	// �G�t�F�N�g�̍X�V
	GetEffectMgr()->update();

	// �q�b�g�`�F�b�N
	ActorMgr::ActorIterator it_begin = GetActorMgr()->begin();
	ActorMgr::ActorIterator it_end = GetActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		ActorBoss* actor_boss = dynamic_cast<ActorBoss*>(actor);

		// �{�X�ȊO�̃A�N�^�[
		if (actor != nullptr && actor != actor_boss)
		{
			if (actor->isHitCheck())
			{
				float mul_power = pow(0.5f, mNegativeAtkLv);
				mBoss->hit(actor->getHitPosY(), (actor->getAtkPower() * mul_power));
				actor->setIsHitCheck(false);
				mMissionGauge += actor->getMissionPower();
				UtilGame::addScore(actor->getScore());
			}
		}
	}

	mTime -= 1;

	// �ɂ��܂�
	if (UtilBattle::isRunWeakGroundAttack() ||
		UtilBattle::isRunWeakSkyAttack())
	{
		UtilBattle::addWeakAtkCount();
		mNikumanCurrentIndex++;
		if (cMaxPlayerCount <= mNikumanCurrentIndex)
		{
			mNikumanCurrentIndex = 0;
		}
	}
	// �悵���낤
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		UtilBattle::addMediumAtkCount();
		mYoshitaroCurrentIndex++;
		if (cMaxPlayerCount <= mYoshitaroCurrentIndex)
		{
			mYoshitaroCurrentIndex = 0;
		}
	}
	// �̂���
	if (UtilBattle::isRunStrongGroundAttack() ||
		UtilBattle::isRunStrongSkyAttack())
	{
		UtilBattle::addStrongAtkCount();
		mNoppoCurrentIndex++;
		if (cMaxPlayerCount <= mNoppoCurrentIndex)
		{
			mNoppoCurrentIndex = 0;
		}
	}
	recover();

	//�Q�[���I�[�o�[����
	if (mBoss->isWin())
	{
		mState.changeState(cState_GameOver);
		return;
	}
}

/**
 * @brief �X�e�[�g:GameOver
 */
void
SceneGameNormal::stateEnterGameOver()
{
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_OVER);
	mGameStateRectNum = R_GAME_OVER;
	mGameStateFontAlpha = 255;
}
void
SceneGameNormal::stateGameOver()
{
	if (120 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief �X�e�[�g:TimeOver
 */
void
SceneGameNormal::stateEnterTimeOver()
{
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_G_CLEAR);
	mGameStateRectNum = R_GAME_CLEAR;
	mGameStateFontAlpha = 255;
}
void
SceneGameNormal::stateTimeOver()
{
	if (180 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}