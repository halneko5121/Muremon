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
#include "Program/Mission/MissionMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/UI/UINormalGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/DefineGame.h"

namespace
{

	const int cTimeLimitCount = 10800;					// ��������(3:00)
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	// ���`
	const int cMaxMissionGauge = 5000;

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
	, mMission(nullptr)
	, mBoss(nullptr)
	, mUINormalGame(nullptr)
	, mTime(cTimeLimitCount)
	, mIsPose(false)
	, mGameStateFontAlpha(0)
	, mGameStateRectNum(0)
	, mMissionGauge(0)
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
	APP_SAFE_DELETE(mMission);
	GetActorMgr()->clearActor();
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
	mBoss = dynamic_cast<ActorBoss*>(GetActorMgr()->createActor(cActorId_Boss, mTexture, mVertex));

	// �v���C���[3��ޕ�
	for (int actor_id = cActorId_Noppo; actor_id <= cActorId_Yoshi; actor_id++)
	{
		// �e�ő吔����
		for (int j = 0; j < cMaxPlayerCount; j++)
		{
			mActor[actor_id][j] = GetActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}

	// ������
	GetActorMgr()->init();

	mUINormalGame->init();

	mMission = new MissionMgr(mTexture, mVertex, mBoss);

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
		mVertex->setColor(mGameStateFontAlpha, 255, 255, 255);
		mVertex->drawF(cDispBgPos, mGameStateRectNum);
	}
	else
	{
		// �A�N�^�[�̕`��
		GetActorMgr()->draw();

		// �G�t�F�N�g�`��
		GetEffectMgr()->draw();
	}

	// �~�b�V�����֘A
	mMission->draw();

	// �e��UI
	mUINormalGame->draw(*mBoss, mMissionGauge, mTime);
}

/**
 * @brief	�V�[���I��
 */
void
SceneGameNormal::end()
{
	// �Q�[���I��
	requestChangeScene(cSceneName_Ranking);
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
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(cDispBgPos, R_GAME_BG);
	mVertex->drawF(cDispFlagPos, R_FLAG);
}

/**
 * @brief	���s�ŉ����������̂̌��ɖ߂�
 */
void
SceneGameNormal::recover()
{
	if(mBoss->isDead())
	{
		mMission->resetBadStatusAtkLv();
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
	if ((mBoss->getNowPos().x - 150) < 500) 
	{
		UtilSound::playLoop(S_SAIREN);
	}
	else
	{
		UtilSound::stop(S_SAIREN);
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
	if (mMissionGauge >= cMaxMissionGauge)
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

	// �A�N�^�[�̍X�V
	GetActorMgr()->update();

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
				float mul_power = pow(0.5f, mMission->getBadStatusAtkLv());
				mBoss->hit(actor->getNowPos(), (actor->getAtkPower() * mul_power));
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
 * @brief �X�e�[�g:Mission
 */
void
SceneGameNormal::stateEnterMission()
{
	UtilSound::stop(S_SAIREN);
	mMission->init();
}
void
SceneGameNormal::stateMission()
{
	GetEffectMgr()->update();

	mMission->update();

	if (mMission->isEnd())
	{
		mMissionGauge = 0;
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