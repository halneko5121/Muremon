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
#include "Program/DefineGame.h"

namespace
{
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

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
		cState_GameClear,		// �Q�[���N���A
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
	, mNiku(nullptr)
	, mNoppo(nullptr)
	, mYoshi(nullptr)
	, mTime(TIME_LIMIT)
	, mIsPose(false)
	, mStartAlpha(0)
	, mGameState(G_START_SCENE)
	, mMissionStateKeep(0)
	, mNikumanKeyCount(0)
	, mYoshitaroKeyCount(0)
	, mNoppoKeyCount(0)
	, mIsInit(false)
	, mMissionGauge(0)
	, mIsHitNiku(false)
	, mIsHitYoshi(false)
	, mIsHitNoppo(false)
	, mIsHitEffect(false)
	, mHitEffectAlpha(0)
	, mHitEffectTime(0)
	, mCharaAtkY(0)
	, mAlphaFont(0)
	, mTimeCount(0)
	, mWavePos(WAVE_INIT_X, WAVE_INIT_Y)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeDamege(1)
{
	mState.initialize(cState_Count, cState_Idle);
	mState.registState(this, &SceneGameNormal::stateEnterIdle,			&SceneGameNormal::stateExeIdle,			nullptr, cState_Idle);
	mState.registState(this, &SceneGameNormal::stateEnterReadyFadeIn,	&SceneGameNormal::stateExeReadyFadeIn,	nullptr, cState_ReadyFadeIn);
	mState.registState(this, &SceneGameNormal::stateEnterReady,			&SceneGameNormal::stateExeReady,		nullptr, cState_Ready);
	mState.registState(this, &SceneGameNormal::stateEnterReadyFadeOut,	&SceneGameNormal::stateExeReadyFadeOut, nullptr, cState_ReadyFadeOut);
	mState.registState(this, &SceneGameNormal::stateEnterGame,			&SceneGameNormal::stateExeGame,			nullptr, cState_Game);
	mState.registState(this, &SceneGameNormal::stateEnterGameOver,		&SceneGameNormal::stateExeGameOver,		nullptr, cState_GameOver);
	mState.registState(this, &SceneGameNormal::stateEnterGameClear,		&SceneGameNormal::stateExeGameClear,	nullptr, cState_GameClear);
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
	mNiku = new ActorNikuman(mTexture, mVertex);
	mNoppo	= new ActorNoppo(mTexture, mVertex);
	mYoshi	= new ActorYoshi(mTexture, mVertex);
	mBoss = new ActorBoss(mTexture, mVertex);

	mNiku->init();
	mNoppo->init();
	mYoshi->init();
	mBoss->init();

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
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(cDispBgPos, R_GAME_BG);
	mVertex->drawF(Vector2f(G_FLAG_X, G_FLAG_Y), R_FLAG);

	if(mGameState == G_START_SCENE)
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mStartAlpha,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_START);	//�Q�[���X�^�[�g
	}
	else if(mGameState == G_GAME_SCENE)
	{
		mBoss->drawImple();

		drawHitEffect();
		//�L�����B
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

		mNoppo->draw();
		mYoshi->draw();
		mNiku->draw();
	}
	else if(mGameState == G_GAME_OVER)
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_OVER);	//�Q�[���I�[�o�[
	}
	else if(mGameState == G_GAME_CLEAR)
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_CLEAR);	//�Q�[���N���A
	}

	if(mMissionStateKeep == MISSION_OUGI)
	{
		drawMissionOugi();
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE)
	{
		drawMissionNegative();
	}

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->setColor(255,255,255,255);
	mVertex->drawF(cDispStateFramePos, R_STATE_FRAME);	//�X�e�[�^�X�g�`��
	mVertex->drawF(cDispScorePos, R_SCORE);		//������

	drawScore();

	mVertex->drawF(cDispTimePos, R_TIME);		//������

	drawTime();

	mVertex->drawF(Vector2f(G_FACE_X, G_F_NIKUMAN_Y), R_F_NIKUMAN);	//�ɂ��܂��
	mVertex->drawF(Vector2f(G_FACE_X, G_F_YOSHITARO_Y), R_F_YOSHITARO);	//�悵���낤��
	mVertex->drawF(Vector2f(G_FACE_X, G_F_NOPPO_Y), R_F_NOPPO);	//�̂��ۊ�

	drawKeyCount();

	mVertex->drawF(cDispMissionPos, R_MISSION_GAGE);	//�݂�����񂰁`��
	mVertex->drawF(cDispMissionGaugePos, R_GAGE_IN);	//�݂������Q�[�W

	drawMissionGuage();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispMissionGaugePos, R_GAGE_FRAME);	//�݂������Q�[�W�g
	mVertex->drawF(cDispHpPos, R_HP);	//��������̗̑�
	mVertex->drawF(Vector2f(G_GAGE_X, G_GAGE_Y), R_GAGE_IN);	//�̗̓Q�[�W

	drawHpGauge();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(Vector2f(G_GAGE_X, G_GAGE_Y), R_GAGE_FRAME);	//�̗̓Q�[�W�g

	if(mMissionGauge >= MISSION_GAGE_MAX)
	{
		mMission->draw();
	}
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
 * @brief	�A�Ő��`��
 */
void
SceneGameNormal::drawKeyCount()
{
	//�ɂ��܂�
	for(int i = 0;i < 4;i++){
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(G_PUSHNUM + 20.f * i, G_F_NIKUMAN_Y), R_0 + num % 10);
	}
	//�悵���낤
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(Vector2f(G_PUSHNUM + 20.f * i, G_F_YOSHITARO_Y), R_0 + num % 10);
	}
	//�̂���
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(G_PUSHNUM + 20.f * i, G_F_NOPPO_Y), R_0 + num % 10);
	}
}

/**
 * @brief	�X�R�A�̕`��
 */
void
SceneGameNormal::drawScore()
{
	//�X�R�A
	for(int i = 0;i < 9;i++){
		int num = UtilGame::getScore();
		for(int j = 1; j < 9 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(Vector2f(G_SCORENUM_X + 20.f * i, G_SCORENUM_Y), R_0 + num % 10);
	}
}

/**
 * @brief	�^�C���̕`��
 */
void
SceneGameNormal::drawTime()
{
	//�^�C��
	for(int i = 0;i < 5;i++)
	{
		int num = mTime;
		if(i != 2)
		{
			int a = 0;
			if(i > 2)
			{
				a = i - 1;
			}
			else
			{
				a = i;
			}
			for(int j = 0;j < 4 - a;j++)
			{
				if(j == 0)
				{
					num = num / 60;
				}
				else if(j == 2)
				{
					num = num / 6;
				}
				else
				{
					num = num / 10;
				}
			}
			if(i == 0 || i == 3)
			{
				mVertex->drawF(Vector2f(G_TIMENUM_X + 20.f * i, G_TIMENUM_Y), R_0 + num % 6);
			}
			else
			{
				mVertex->drawF(Vector2f(G_TIMENUM_X + 20.f * i, G_TIMENUM_Y), R_0 + num % 10);
			}
		}
		else
		{
			mVertex->drawF(Vector2f(G_TIMENUM_X + 20.f * i, G_TIMENUM_Y), R_SEMICORON);
		}
	}
}

/**
 * @brief	HP�Q�[�W�̕`��
 */
void
SceneGameNormal::drawHpGauge()
{
	float num = mBoss->mLife / mBoss->mMaxLife;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,200,30,30);
	mVertex->drawF(Vector2f(G_GAGE_X - (1.f - num) * 100.f, G_GAGE_Y), R_GAGE_IN);	//�̗̓Q�[�W
}

/**
 * @brief	�q�b�g�G�t�F�N�g�̕`��
 */
void
SceneGameNormal::drawHitEffect()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF(Vector2f(mBoss->mMoveX - HIT_EFFECT_X, mCharaAtkY), R_HIT_EFFECT);
}

/**
 * @brief	�~�b�V�����Q�[�W�̕`��
 */
void
SceneGameNormal::drawMissionGuage()
{
	float num = (float)mMissionGauge / (float)MISSION_GAGE_MAX;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,30,30,200);
	mVertex->drawF(Vector2f(cDispMissionGaugePos.x - (1.f - num) * 100.f, cDispMissionGaugePos.y), R_GAGE_IN);	//�~�b�V�����Q�[�W
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
		mWavePos.x += WAVE_SPEED_X;
		mWavePos.y -= WAVE_UP_Y;
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
		mWavePos.x = WAVE_INIT_X;
		mWavePos.y = WAVE_INIT_Y;
		UtilGame::addScore(MISSION_CLEAR_SCORE);
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
			mNegativeDamege += 1;
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

	mNegativeState = rand()%100+1;

	if(mNegativeState > 0 && mNegativeState <= cNegativePar1){
		mNegativeState = SPEED_UP;
	}
	else if(mNegativeState > cNegativePar1 && mNegativeState <= cNegativePar2){
		mNegativeState = RECOVER;
	}
	else if(mNegativeState > cNegativePar2 && mNegativeState <= cNegativePar3){
		mNegativeState = SLIDE_IN;
	}
	else if(mNegativeState > cNegativePar3 && mNegativeState <= cNegativePar4){
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
		mNegativeDamege = 1;
	}
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
SceneGameNormal::stateExeIdle()
{
}

/**
 * @brief �X�e�[�g:ReadyFadeIn
 */
void
SceneGameNormal::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(S_GAME_START);
}
void
SceneGameNormal::stateExeReadyFadeIn()
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
SceneGameNormal::stateEnterReady()
{
}
void
SceneGameNormal::stateExeReady()
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
SceneGameNormal::stateExeReadyFadeOut()
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
SceneGameNormal::stateEnterGame()
{
	UtilSound::playLoop(S_BGM_BATTLE);
}
void
SceneGameNormal::stateExeGame()
{
	boss_cc2.x = mBoss->mMoveX;
	boss_cc2.y = mBoss->mMoveY;

	if (mGameState != G_GAME_OVER) {
		if ((boss_cc2.x - 150) < 500) {
			UtilSound::playLoop(S_SAIREN);
		}
		else
		{
			UtilSound::stop(S_SAIREN);
		}
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

	if (mIsPose) {
		return;
	}

	//�~�b�V�������N������i�K�܂ł�������
	if (mMissionGauge >= MISSION_GAGE_MAX) {
		if (!mIsInit) {
			UtilSound::playOnce(S_OSIRASE);
			mMission->init(mNikumanKeyCount, mYoshitaroKeyCount, mNoppoKeyCount);
			mIsInit = true;
		}
		if (mMissionStateKeep < MISSION_OUGI) {
			mMissionStateKeep = mMission->update();
			if (mNikumanKeyCount != mMission->getCountKeyNikuman()) {
				mNikumanKeyCount = mMission->getCountKeyNikuman();
			}
			if (mYoshitaroKeyCount != mMission->getCountKeyYoshitaro()) {
				mYoshitaroKeyCount = mMission->getCountKeyYoshitaro();
			}
			if (mNoppoKeyCount != mMission->getCountKeyNoppo()) {
				mNoppoKeyCount = mMission->getCountKeyNoppo();
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
		mState.changeState(cState_GameClear);
		return;
	}

	mNiku->update(boss_cc2);
	mYoshi->update(boss_cc2);
	mNoppo->update(boss_cc2);

	mTime -= 1;

	mIsHitNiku = mNiku->isHitCheck();//���������Ƃ����t���O���A���Ă��܂�

	mIsHitYoshi = mYoshi->isHitCheck();//����������ă_���[�W�Ȃǂ�

	mIsHitNoppo = mNoppo->isHitCheck();//���f�����Ă�������

	if (mIsHitNiku)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NIKUMAN_DAMAGE / mNegativeDamege;
		mMissionGauge += NIKUMAN_GAGE;

		UtilGame::addScore(NIKUMAN_SCORE);
		mIsHitEffect = true;
		mCharaAtkY = mNiku->getHitPosY();
		mNiku->setIsHitCheck(false);
	}

	if (mIsHitYoshi)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= YOSHITARO_DAMAGE / mNegativeDamege;
		mMissionGauge += YOSHITARO_GAGE;
		UtilGame::addScore(YOSHITARO_SCORE);
		mIsHitEffect = true;
		mCharaAtkY = mYoshi->getHitPosY();
		mYoshi->setIsHitCheck(false);
	}

	if (mIsHitNoppo)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NOPPO_DAMAGE / mNegativeDamege;
		mMissionGauge += NOPPO_GAGE;
		UtilGame::addScore(NOPPO_SCORE);
		mIsHitEffect = true;
		mCharaAtkY = mNoppo->getHitPosY();
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
	recover();

	mBoss->update(boss_cc2);

	//�Q�[���I�[�o�[����
	if (mBoss->isWin())
	{
		mState.changeState(cState_GameOver);
		return;
	}

	if (!mBoss->isDead())
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
	else {
		mIsHitEffect = false;
		mHitEffectAlpha = 0;
	}
}

/**
 * @brief �X�e�[�g:GameOver
 */
void
SceneGameNormal::stateEnterGameOver()
{
	mGameState = G_GAME_OVER;
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_OVER);
}
void
SceneGameNormal::stateExeGameOver()
{
	if (120 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief �X�e�[�g:GameClear
 */
void
SceneGameNormal::stateEnterGameClear()
{
	mGameState = G_GAME_CLEAR;
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_G_CLEAR);
}
void
SceneGameNormal::stateExeGameClear()
{
	if (180 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}