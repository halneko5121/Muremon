/******************************************************************
 *	@file	MissionMgr.cpp
 *	@brief	�~�b�V�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "MissionMgr.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Mission/MissionBase.h"
#include "Program/Mission/Mission1.h"
#include "Program/Mission/Mission2.h"
#include "Program/Mission/Mission3.h"
#include "Program/Mission/Mission4.h"
#include "Program/Mission/Mission5.h"
#include "Program/Mission/Mission6.h"
#include "Program/Mission/Mission7.h"
#include "Program/Mission/Mission8.h"
#include "Program/Mission/Mission9.h"
#include "Program/Mission/Mission10.h"
#include "Program/Mission/Mission11.h"
#include "Program/Mission/Mission12.h"
#include "Program/Mission/Mission13.h"
#include "Program/Mission/Mission14.h"

#define TEN_SECOND	(600)

#define M_TIMENUM_X	(375.f)
#define M_TIMENUM_Y	(125.f)

#define M_COMBO_X	(500.f)
#define M_COMBO_Y	(245.f)

#define MISSION4_FONT_NUM	(16)
#define MISSION5_FONT_NUM	(23)
#define MISSION6_FONT_NUM	(17)
#define MISSION7_FONT_NUM	(19)
#define MISSION8_FONT_NUM	(15)
#define MISSION9_FONT_NUM	(20)

#define MISSION_1PAR	(10)
#define MISSION_2PAR	(20)
#define MISSION_3PAR	(25)
#define MISSION_4PAR	(35)
#define MISSION_5PAR	(40)
#define MISSION_6PAR	(50)
#define MISSION_7PAR	(55)
#define MISSION_8PAR	(65)
#define MISSION_9PAR	(70)
#define MISSION_10PAR	(75)
#define MISSION_11PAR	(85)
#define MISSION_12PAR	(90)
#define MISSION_13PAR	(95)
#define MISSION_14PAR	(100)

#define MISSION_ALPHA_INCREASE	(5)
#define MISSION_ALPHA_MAX	(255)

#define MISSION_HASSEI_X	(400.f)
#define MISSION_HASSEI_Y	(50.f)

const Vector2f MISSION_OSIRASE = { 400.0f, 300.0f };

namespace
{
	const int cMissionClearAddScore = 50000;			// �~�b�V�����N���A���Z�X�R�A

	// �o�b�h�X�e�[�^�X���I�������p�[�Z���e�[�W
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

	// ���`
	const Vector2f cWaveInitPos = { -500.0f, 300.0f };
	const float cWaveSpeedX = ((800.f + 500.f + 500.f) / (60.f * 3.5f));
	const float cWaveUpY = (60.f / (60.f * 3.5f));

	enum NEGATIVE_DATA
	{
		NO_NEGATIVE,
		SPEED_UP,
		RECOVER,
		SLIDE_IN,
		ATTACK_DOWN,
	};

	enum MISSION_NUMBER
	{
		MISSION_1,	//�w10�b�ȓ���100��A�ł���I�I�x
		MISSION_2,	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
		MISSION_3,	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
		MISSION_4,	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
		MISSION_5,	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
		MISSION_6,	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
		MISSION_7,	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
		MISSION_8,	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
		MISSION_9,	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
		MISSION_10,	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
		MISSION_11,	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
		MISSION_12,	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
		MISSION_13,	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
		MISSION_14,	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
	};

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_StartShake,		// �J�n�V�F�C�N
		cState_StartFadeOut,	// �J�n�t�F�[�h�A�E�g
		cState_Run,				// ���s
		cState_Success,			// ����
		cState_Failure,			// ���s
		cState_Ougi,			// ���`
		cState_BadStatus,		// �o�b�h�X�e�[�^�X
		cState_End,				// �I��
		cState_Count
	};

	MissionBase*
	createMission(MissionId id, Texture* texture, Vertex* vertex)
	{
		switch (id)
		{
		case cMissionId_Mission1:	return (new Mission1(id, texture, vertex));
		case cMissionId_Mission2:	return (new Mission2(id, texture, vertex));
		case cMissionId_Mission3:	return (new Mission3(id, texture, vertex));
		case cMissionId_Mission4:	return (new Mission4(id, texture, vertex));
		case cMissionId_Mission5:	return (new Mission5(id, texture, vertex));
		case cMissionId_Mission6:	return (new Mission6(id, texture, vertex));
		case cMissionId_Mission7:	return (new Mission7(id, texture, vertex));
		case cMissionId_Mission8:	return (new Mission8(id, texture, vertex));
		case cMissionId_Mission9:	return (new Mission9(id, texture, vertex));
		case cMissionId_Mission10:	return (new Mission10(id, texture, vertex));
		case cMissionId_Mission11:	return (new Mission11(id, texture, vertex));
		case cMissionId_Mission12:	return (new Mission12(id, texture, vertex));
		case cMissionId_Mission13:	return (new Mission13(id, texture, vertex));
		case cMissionId_Mission14:	return (new Mission14(id, texture, vertex));
		}

		return nullptr;
	}
}

MissionMgr::MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss)
	: mTexture(texture)
	, mVertex(vertex)
	, mActorBoss(boss)
	, mMissionStartPos(MISSION_HASSEI_X, -50.f)
	, mAlpha(0)
	, mAlphaPushZ(255)
	, mFlagZ(true)
	, mFlagDraw(0)
	, mMoveCount(0)
	, mCurrentMissionNo(0)
	, mAlphaFont(0)
	, mWavePos(cWaveInitPos)
	, mNegativeAlpha(0)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeAtkLv(0)
	, mTime(TEN_SECOND)
	, mFlagTimeCount(0)
	, mSuccessTypingCount(1)
	, mKeyCount(0)
	, mKeyCountNikuman(0)
	, mKeyCountYoshitaro(0)
	, mKeyCountNoppo(0)
{
	for (int i = 0; i < cMissionId_Count; i++)
	{
		mMission[i] = createMission(static_cast<MissionId>(i), texture, vertex);
	}

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(MissionMgr, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(MissionMgr, mState, StartShake,		cState_StartShake);
	REGIST_STATE_FUNC2(MissionMgr, mState, StartFadeOut,	cState_StartFadeOut);
	REGIST_STATE_FUNC2(MissionMgr, mState, Run,				cState_Run);
	REGIST_STATE_FUNC2(MissionMgr, mState, Success,			cState_Success);
	REGIST_STATE_FUNC2(MissionMgr, mState, Failure,			cState_Failure);
	REGIST_STATE_FUNC2(MissionMgr, mState, Ougi,			cState_Ougi);
	REGIST_STATE_FUNC2(MissionMgr, mState, BadStatus,		cState_BadStatus);
	REGIST_STATE_FUNC2(MissionMgr, mState, End,				cState_End);
	mState.changeState(cState_Idle);
}

MissionMgr::~MissionMgr()
{
}

void MissionMgr::init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo)
{
	mCurrentMissionNo	= 0;
	mTime		= TEN_SECOND;
	mKeyCount		= 0;
	mSuccessTypingCount	= 1;
	mFlagDraw	= 0;
	mAlpha		= 0;
	mAlphaPushZ= 255;

	mFlagTimeCount = 0;

	mFlagZ		= true;

	mMissionStartPos.x = MISSION_HASSEI_X;
	mMissionStartPos.y = -50.f;

	mKeyCountNikuman		= cnt_nikuman;		//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	mKeyCountYoshitaro	= cnt_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	mKeyCountNoppo		= cnt_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g

	mState.changeState(cState_StartShake);
}

void MissionMgr::update()
{
	mState.executeState();
}

void MissionMgr::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);

	if (!mState.isEqual(cState_StartShake)&&
		!mState.isEqual(cState_StartFadeOut))
	{
		mVertex->setColor(mAlpha,255,255,255);
	}

	int rect_index = calcRectIndex(mState.getStateIndex());
	mVertex->drawF(mMissionStartPos, rect_index);	//�݂�����񔭐�

	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_OSIRASE);	//�݂�����񂨒m�点�g
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_1 + mCurrentMissionNo);	//�݂������

	if(mCurrentMissionNo == MISSION_10 || mCurrentMissionNo == MISSION_11)
	{
		if (mState.isEqual(cState_StartShake) ||
			mState.isEqual(cState_StartFadeOut))
		{
			UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
			mVertex->setColor(mAlpha,255,255,255);
			mVertex->drawF(Vector2f(400.f, 450.f), R_Z_PUSH_START);
		}
	}

	if(mState.isEqual(cState_Run))
	{
		updateMissionD();
	}

	// �~�b�V�������`
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont, 255, 255, 255);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.0f), R_OUGI_FONT);

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->drawF(Vector2f(mWavePos.x, mWavePos.y), R_OUGI);

	// �~�b�V�������s
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mNegativeAlpha, 255, 255, 255);
	mVertex->drawF(Vector2f(400.f, 300.f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.f), R_NEGATIVE1 + mNegativeState - 1);
}

/**
 * @ brief �~�b�V�������I��������
 */
int
MissionMgr::isEnd() const
{
	return (mState.isEqual(cState_End));
}

/**
 * @ brief �o�b�h�X�e�[�^�X�F�U�����x�����擾
 */
int
MissionMgr::getBadStatusAtkLv() const
{
	return mNegativeAtkLv;
}

/**
 * @ brief �o�b�h�X�e�[�^�X�F�U�����x�������Z�b�g
 */
void
MissionMgr::resetBadStatusAtkLv()
{
	mNegativeAtkLv = 0;
}

void MissionMgr::updateMission6()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION6_FONT_NUM)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if(mSuccessTypingCount < MISSION6_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_Y)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_R)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_H)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_C)) mSuccessTypingCount++;
			break;
		case 16:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void MissionMgr::updateMission7()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION7_FONT_NUM)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if(mSuccessTypingCount < MISSION7_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_Y)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_R)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_H)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_H)) mSuccessTypingCount++;
			break;
		case 16:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 17:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 18:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void MissionMgr::updateMission8()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION8_FONT_NUM)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if(mSuccessTypingCount < MISSION8_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void MissionMgr::updateMission9()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION9_FONT_NUM)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if(mSuccessTypingCount < MISSION9_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_B)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_R)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 16:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 17:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 18:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 19:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void MissionMgr::updateMission10()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0){
		mTime = 0;
		if(!mFlagZ){
			mAlphaPushZ += 5;
			if(mAlphaPushZ == 240){
				mFlagZ = true;
			}
		}
		else{
			mAlphaPushZ -= 5;
			if(mAlphaPushZ == 50){
				mFlagZ = false;
			}
		}
	}
	if (UtilInput::isKeyPushedDecide())
	{
		mFlagTimeCount += 1;
	}
	if(mFlagTimeCount == 1){
		mTime++;
	}
	else if(mFlagTimeCount == 2)
	{
		if(mTime <= 11*60 - 31 && mTime >= 9*60 + 31)
		{
			mState.changeState(cState_Success);
			return;
		}
		else
		{
			mState.changeState(cState_Failure);
			return;
		}
	}
}

void MissionMgr::updateMission11()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0){
		mTime = 0;
		if(!mFlagZ){
			mAlphaPushZ += 5;
			if(mAlphaPushZ == 240){
				mFlagZ = true;
			}
		}
		else{
			mAlphaPushZ -= 5;
			if(mAlphaPushZ == 50){
				mFlagZ = false;
			}
		}
	}
	if (UtilInput::isKeyPushedDecide())
	{
		mFlagTimeCount += 1;
		if(mFlagTimeCount > 2)
		{
			mFlagTimeCount = 2;
		}
	}
	if(mFlagTimeCount == 1)
	{
		mTime++;
	}
	else if(mFlagTimeCount == 2)
	{
		if(mTime <= 6*60 - 31 && mTime >= 4*60 + 31)
		{
			mState.changeState(cState_Success);
			return;
		}
		else
		{
			mState.changeState(cState_Failure);
			return;
		}
	}
}

void MissionMgr::updateMission12()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	if (mTime <= 0)
	{
		if (mKeyCountNikuman > mKeyCountNoppo && mKeyCountNikuman > mKeyCountYoshitaro)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineOne())
	{
		UtilBattle::addWeakAtkCount();
		mKeyCountNikuman++;
	}
	mTime--;
}

void MissionMgr::updateMission13()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	if (mTime <= 0)
	{
		if (mKeyCountYoshitaro > mKeyCountNikuman && mKeyCountYoshitaro > mKeyCountNoppo)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isKeyPushedLineOne())
	{
		UtilBattle::addMediumAtkCount();
		mKeyCountYoshitaro++;
	}
	mTime--;
}

void MissionMgr::updateMission14()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	if(mTime <= 0)
	{
		if(mKeyCountNoppo > mKeyCountNikuman && mKeyCountNoppo > mKeyCountYoshitaro)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isKeyPushedLineThree())
	{
		UtilBattle::addStrongAtkCount();
		mKeyCountNoppo++;
	}
	mTime--;
}

void MissionMgr::updateMissionD()
{
	mMission[mCurrentMissionNo]->draw();
}

void MissionMgr::updateMission6D()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(118.0f + 29.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void MissionMgr::updateMission7D()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(108.0f + 28.0f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void MissionMgr::updateMission8D()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(131.0f + 30.f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void MissionMgr::updateMission9D()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(96.0f + 29.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void MissionMgr::updateMission10D()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0)
	{
		mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ,255,255,255);
		mVertex->drawF(Vector2f(400.0f, 450.0f), R_Z_PUSH_START);
	}
}

void MissionMgr::updateMission11D()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0)
	{
		mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ,255,255,255);
		mVertex->drawF(Vector2f(400.0f, 450.0f),R_Z_PUSH_START);
	}
}

void MissionMgr::updateMission12D()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

void MissionMgr::updateMission13D()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

void MissionMgr::updateMission14D()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

/**
 * @brief ���݂̃X�e�[�g�����`�ԍ����Z�o����
 */
int
MissionMgr::calcRectIndex(int state_index) const
{
	switch (state_index)
	{
	case cState_StartShake:
	case cState_StartFadeOut:
		return R_MISSION_HASSEI;
	case cState_Run:
		return R_MISSION_KAISI;
	case cState_Success:
		return R_MISSION_SEIKO;
	case cState_Failure:
		return R_MISSION_SIPPAI;
	default:
		return 0;
	}
}

void MissionMgr::drawTime()
{
	// �^�C��
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for(int i = 0;i < 2;i++){
		int num = mTime;
		for(int j = 0;j < 2 - i;j++){
			if(j == 0){
				num = num / 60;
			}
			else{
				num = num / 10;
			}
		}
		mVertex->drawF(Vector2f(M_TIMENUM_X + 50.f * i, M_TIMENUM_Y), R_0_B + num % 10);
	}
}

void MissionMgr::drawCombo()
{
	// �R���{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for(int i = 0;i < 3;i++){
		int num = mKeyCount;
		for(int j = 1;j < 3 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(Vector2f(M_COMBO_X + 50.f + 50.f * i, M_COMBO_Y), R_0_B + num % 10);
	}
	mVertex->drawF(Vector2f(M_COMBO_X, M_COMBO_Y), R_COMBO);
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
MissionMgr::stateEnterIdle()
{
}
void
MissionMgr::stateIdle()
{
}

/**
 * @brief �X�e�[�g:StartShake
 */
void
MissionMgr::stateEnterStartShake()
{
	UtilSound::playOnce(S_OSIRASE);
	mMoveCount = 0;

	// �݂����������߂��菉����������
	mCurrentMissionNo = cMissionId_Mission5; // rand() % 100 + 1;

	/*
	if (mCurrentMissionNo >= 0 && mCurrentMissionNo <= MISSION_1PAR) {
		mCurrentMissionNo = MISSIcMissionId_Mission1;
	}
	else if (mCurrentMissionNo > MISSION_1PAR && mCurrentMissionNo <= MISSION_2PAR) {
		mCurrentMissionNo = cMissionId_Mission2;
	}
	else if (mCurrentMissionNo > MISSION_2PAR && mCurrentMissionNo <= MISSION_3PAR) {
		mCurrentMissionNo = cMissionId_Mission3;
	}
	else if (mCurrentMissionNo > MISSION_3PAR && mCurrentMissionNo <= MISSION_4PAR) {
		mCurrentMissionNo = cMissionId_Mission4;
	}
	else if (mCurrentMissionNo > MISSION_4PAR && mCurrentMissionNo <= MISSION_5PAR) {
		mCurrentMissionNo = cMissionId_Mission5;
	}
	else if (mCurrentMissionNo > MISSION_5PAR && mCurrentMissionNo <= MISSION_6PAR) {
		mCurrentMissionNo = cMissionId_Mission6;
	}
	else if (mCurrentMissionNo > MISSION_6PAR && mCurrentMissionNo <= MISSION_7PAR) {
		mCurrentMissionNo = cMissionId_Mission7;
	}
	else if (mCurrentMissionNo > MISSION_7PAR && mCurrentMissionNo <= MISSION_8PAR) {
		mCurrentMissionNo = cMissionId_Mission8;
	}
	else if (mCurrentMissionNo > MISSION_8PAR && mCurrentMissionNo <= MISSION_9PAR) {
		mCurrentMissionNo = cMissionId_Mission9;
	}
	else if (mCurrentMissionNo > MISSION_9PAR && mCurrentMissionNo <= MISSION_10PAR) {
		mCurrentMissionNo = cMissionId_Mission10;
	}
	else if (mCurrentMissionNo > MISSION_10PAR && mCurrentMissionNo <= MISSION_11PAR) {
		mCurrentMissionNo = cMissionId_Mission11;
	}
	else if (mCurrentMissionNo > MISSION_11PAR && mCurrentMissionNo <= MISSION_12PAR) {
		mCurrentMissionNo = cMissionId_Mission12;
		if (mKeyCountNikuman >= mKeyCountNoppo && mKeyCountNikuman >= mKeyCountYoshitaro) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
	else if (mCurrentMissionNo > MISSION_12PAR && mCurrentMissionNo <= MISSION_13PAR) {
		mCurrentMissionNo = cMissionId_Mission13;
		if (mKeyCountYoshitaro >= mKeyCountNikuman && mKeyCountYoshitaro >= mKeyCountNoppo) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
	else if (mCurrentMissionNo > MISSION_13PAR && mCurrentMissionNo <= MISSION_14PAR) {
		mCurrentMissionNo = cMissionId_Mission14;
		if (mKeyCountNoppo >= mKeyCountNikuman && mKeyCountNoppo >= mKeyCountYoshitaro) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
	*/
}
void
MissionMgr::stateStartShake()
{
	if (mFlagDraw % 2 == 0) 
	{
		if (mMissionStartPos.y < MISSION_HASSEI_Y) 
		{
			mMissionStartPos.y += 5.f;
		}
		else
		{
			mFlagDraw++;
		}
	}
	else if (mFlagDraw % 2 == 1) 
	{
		mMissionStartPos.y -= 5.f;
		if (mMissionStartPos.y == 0.f + 20.f * mMoveCount) {
			mFlagDraw++;
			mMoveCount++;
		}
	}

	// �ʒu���v�Z
	if (mFlagDraw == 7)
	{
		mState.changeState(cState_StartFadeOut);
		return;
	}	
}

/**
 * @brief �X�e�[�g:StartFadeOut
 */
void
MissionMgr::stateEnterStartFadeOut()
{
}
void
MissionMgr::stateStartFadeOut()
{
	mAlpha += MISSION_ALPHA_INCREASE;
	if (mAlpha > MISSION_ALPHA_MAX)
	{
		mAlpha = MISSION_ALPHA_MAX;
	}
	if (mAlpha == MISSION_ALPHA_MAX)
	{
		mState.changeState(cState_Run);
		return;
	}
}

/**
 * @brief �X�e�[�g:Run
 */
void
MissionMgr::stateEnterRun()
{
	UtilSound::playOnce(S_OSIRASE);
	mMission[mCurrentMissionNo]->run();
}
void
MissionMgr::stateRun()
{
	mMission[mCurrentMissionNo]->update();

	if (mMission[mCurrentMissionNo]->isSuccess())
	{
		mState.changeState(cState_Success);
		return;
	}
	if (mMission[mCurrentMissionNo]->isFailure())
	{
		mState.changeState(cState_Failure);
		return;
	}
}

/**
 * @brief �X�e�[�g:Success
 */
void
MissionMgr::stateEnterSuccess()
{
	UtilSound::playOnce(S_M_CLEAR);
}
void
MissionMgr::stateSuccess()
{
	mAlpha -= MISSION_ALPHA_INCREASE;
	if (mAlpha < 0) { mAlpha = 0; }

	if (mAlpha == 0)
	{
		mState.changeState(cState_Ougi);
		return;
	}
}

/**
 * @brief �X�e�[�g:Failure
 */
void
MissionMgr::stateEnterFailure()
{
	UtilSound::playOnce(S_M_OVER);
}
void
MissionMgr::stateFailure()
{
	mAlpha -= MISSION_ALPHA_INCREASE;
	if (mAlpha < 0) { mAlpha = 0; }

	if (mAlpha == 0)
	{
		mState.changeState(cState_BadStatus);
		return;
	}
}

/**
 * @brief �X�e�[�g:Ougi
 */
void
MissionMgr::stateEnterOugi()
{
}
void
MissionMgr::stateOugi()
{
	int count = mState.getStateCount();

	if (count >= 0 && 60 > count) {
		mAlphaFont += 5;
		if (mAlphaFont > 255) {
			mAlphaFont = 255;
		}
	}
	else if (count >= 60 && 120 > count) {
		mAlphaFont = 255;
	}
	else if (count >= 120 && 180 > count) {
		mAlphaFont -= 5;
		if (mAlphaFont < 0) {
			mAlphaFont = 0;
		}
	}
	else if (count >= 180 && 210 > count) {
		if (count == 180) {
			UtilSound::playOnce(S_NAMI);
		}
	}
	else if (count >= 210 && 420 > count) {		//�g�𓮂���(3.5sec)
		mWavePos.x += cWaveSpeedX;
		mWavePos.y -= cWaveUpY;
		if (count % 10 <= 4) {
			mWavePos.y -= 2.f;
		}
		else if (count % 10 <= 9) {
			mWavePos.y += 2.f;
		}
	}
	else if (count >= 420 && 450 > count) {
	}
	else if (count >= 450 && 630 > count) {
	}

	if (count > 630) {
		mActorBoss->mLife -= 7000;
		mWavePos = cWaveInitPos;
		UtilGame::addScore(cMissionClearAddScore);
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:BadStatus
 */
void
MissionMgr::stateEnterBadStatus()
{
	int rand_negative = rand() % 100 + 1;
	if (rand_negative > 0 && rand_negative <= cNegativePar1) {
		mNegativeState = SPEED_UP;
	}
	else if (rand_negative > cNegativePar1 && rand_negative <= cNegativePar2) {
		mNegativeState = RECOVER;
	}
	else if (rand_negative > cNegativePar2 && rand_negative <= cNegativePar3) {
		mNegativeState = SLIDE_IN;
	}
	else if (rand_negative > cNegativePar3 && rand_negative <= cNegativePar4) {
		mNegativeState = ATTACK_DOWN;
	}

	mNegativeState = SLIDE_IN;
}
void
MissionMgr::stateBadStatus()
{
	int count = mState.getStateCount();

	if (count >= 0 && 60 > count) {
		mNegativeAlpha += 5;
		if (mNegativeAlpha > 255) {
			mNegativeAlpha = 255;
		}
	}
	else if (count >= 60 && 120 > count) {
		mNegativeAlpha = 255;
	}
	else if (count >= 120 && 180 > count) {
		mNegativeAlpha -= 5;
		if (mNegativeAlpha < 0) {
			mNegativeAlpha = 0;
		}
	}
	else if (count >= 180)
	{
		switch (mNegativeState)
		{
		case SPEED_UP:
			mActorBoss->mSpeedX = 3;
			break;
		case RECOVER:
			mActorBoss->mLife = mActorBoss->mMaxLife;
			break;
		case SLIDE_IN:
			mActorBoss->mMoveX = 500;
			break;
		case ATTACK_DOWN:
			mNegativeAtkLv++;
			break;
		}
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
MissionMgr::stateEnterEnd()
{
	mNegativeState = NO_NEGATIVE;
}
void
MissionMgr::stateEnd()
{
}