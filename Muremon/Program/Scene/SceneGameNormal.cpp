/******************************************************************
 *	@file	SceneGameNormal.cpp
 *	@brief	�Q�[���V�[���i�m�[�}���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "SceneGameNormal.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Mission/MissionMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/CollisionMgr.h"
#include "Program/UI/UINormalGame.h"
#include "Program/Effect/EffectMgr.h"

namespace
{

	const int cTimeLimitCount = 10800;					// ��������(3:00)
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	const int cGameOverPosX = 450;

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_ReadyFadeIn,		// �����t�F�[�h�C��
		cState_Ready,			// ����
		cState_ReadyFadeOut,	// �����t�F�[�h�A�E�g
		cState_Game,			// �Q�[����
		cState_Mission,			// �~�b�V������
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
	, mMissionMgr(nullptr)
	, mBoss(nullptr)
	, mUINormalGame(nullptr)
	, mTime(cTimeLimitCount)
	, mIsPose(false)
	, mGameStateFontAlpha(0)
	, mGameStateRectNum(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
{
	mUINormalGame = new UINormalGame();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Game,			cState_Game);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Mission,		cState_Mission);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, GameOver,		cState_GameOver);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, TimeOver,		cState_TimeOver);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
SceneGameNormal::~SceneGameNormal()
{
	APP_SAFE_DELETE(mMissionMgr);
	getActorMgr()->clearActor();
	APP_SAFE_DELETE(mUINormalGame);
}

/**
 * @brief	������
 */
void
SceneGameNormal::impleInit()
{
	UtilGame::setGameModeNormal();
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// �{�X
	mBoss = dynamic_cast<ActorBoss*>(getActorMgr()->createActor(cActorId_Boss, mTexture, mVertex));

	// �v���C���[3��ޕ�
	for (int actor_id = cActorId_Noppo; actor_id <= cActorId_Yoshi; actor_id++)
	{
		// �e�ő吔����
		for (int j = 0; j < cMaxPlayerCount; j++)
		{
			mActor[actor_id][j] = getActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}

	// ������
	getActorMgr()->init();

	mUINormalGame->init();

	mMissionMgr = new MissionMgr(mTexture, mVertex);

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
SceneGameNormal::draw() const
{
	// �w�i
	drawBg();

	if (mState.isEqual(cState_GameOver) ||
		mState.isEqual(cState_TimeOver))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		UtilGraphics::setVertexColor(mVertex, mGameStateFontAlpha, 255, 255, 255);
		UtilGraphics::drawF(mVertex, cDispBgPos, mGameStateRectNum);
	}
	else
	{
		// �A�N�^�[�̕`��
		getActorMgr()->draw();

		// �G�t�F�N�g�`��
		getEffectMgr()->draw();
	}

	// �~�b�V�����֘A
	mMissionMgr->draw();

	// �e��UI
	mUINormalGame->draw(mMissionMgr->getPower(), mTime);
}

/**
 * @brief	�V�[���I��
 */
void
SceneGameNormal::end()
{
	// �Q�[���I��
	requestChangeScene(cSceneId_Ranking);
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
SceneGameNormal::drawBg() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, cDispBgPos, R_GAME_BG);
	UtilGraphics::drawF(mVertex, cDispFlagPos, R_FLAG);
}

ActorBase*
SceneGameNormal::getActorNikuman(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameNormal::getActorYoshi(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameNormal::getActorNoppo(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
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
	UtilSound::playOnce(cSoundId_SeGameStart);
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
	UtilSound::playLoop(cSoundId_BgmBattle);
}
void
SceneGameNormal::stateGame()
{
	if ((mBoss->getNowPos().x - 150) < 500) 
	{
		UtilSound::playLoop(cSoundId_SeAlert);
	}
	else
	{
		UtilSound::stop(cSoundId_SeAlert);
	}

	if (UtilInput::isKeyPushedReturn())
	{
		mIsPose = !mIsPose;
	}

	if (mIsPose) 
	{
		return;
	}

	// �~�b�V�������N������i�K�܂ł�������
	if (mMissionMgr->isPowerFull())
	{
		mState.changeState(cState_Mission);
		return;
	}

	if (mTime == 0)
	{
		mState.changeState(cState_TimeOver);
		return;
	}

	// �e�U���̊J�n
	updateRunAtk();

	// �Փ˃`�F�b�N�̍X�V
	getCollisionMgr()->update();

	// �A�N�^�[�̍X�V
	getActorMgr()->update();

	// �G�t�F�N�g�̍X�V
	getEffectMgr()->update();

	// �q�b�g�`�F�b�N
	ActorMgr::ActorIterator it_begin = getActorMgr()->begin();
	ActorMgr::ActorIterator it_end = getActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		ActorBoss* actor_boss = dynamic_cast<ActorBoss*>(actor);

		// �{�X�ȊO�̃A�N�^�[
		if (actor != nullptr && actor != actor_boss)
		{
			if (actor->isHitCheck())
			{
				float atk_power = UtilBattle::calcAtkPower(*actor);
				mBoss->hit(actor->getNowPos(), atk_power);
				actor->setIsHitCheck(false);
				float mission_guage = mMissionMgr->getPower();
				mission_guage += actor->getMissionPower();
				mMissionMgr->setPower(mission_guage);
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

	// �~�b�V�������s�ŉ����������̂����ɖ߂�
	if (mBoss->isDead())
	{
		UtilBattle::resetBadStatusAtkLv();
	}

	// �Q�[���I�[�o�[����
	if (mBoss->getNowPos().x <= cGameOverPosX)
	{
		mState.changeState(cState_GameOver);
		return;
	}
}

/**
 * @brief �X�e�[�g:Mission
 */
void
SceneGameNormal::stateEnterMission()
{
	UtilSound::stop(cSoundId_SeAlert);
	mMissionMgr->init();
}
void
SceneGameNormal::stateMission()
{
	getEffectMgr()->update();

	mMissionMgr->update();

	if (mMissionMgr->isEnd())
	{
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief �X�e�[�g:GameOver
 */
void
SceneGameNormal::stateEnterGameOver()
{
	UtilSound::stop(cSoundId_SeAlert);
	UtilSound::stop(cSoundId_BgmBattle);
	UtilSound::playOnce(cSoundId_SeGameOver);
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
	UtilSound::stop(cSoundId_SeAlert);
	UtilSound::stop(cSoundId_BgmBattle);
	UtilSound::playOnce(cSoundId_SeGameClear);
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