#include "Mission.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"

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
		cState_Start,			// �J�n
		cState_Run,				// ���s
		cState_Success,			// ����
		cState_Failure,			// ���s
		cState_Ougi,			// ���`
		cState_BadStatus,		// �o�b�h�X�e�[�^�X
		cState_End,				// �I��
		cState_Count
	};
}

Mission::Mission(Texture* texture, Vertex* vertex)
	: mTexture(texture)
	, mVertex(vertex)
	, mMissionStartPos(MISSION_HASSEI_X, -50.f)
	, mAlpha(0)
	, mAlphaPushZ(255)
	, mFlagZ(true)
	, mFlagDraw(0)
	, mIsSound(true)
	, mIsSound2(true)
	, mMoveCount(0)
	, mCurrentMissionNo(0)
	, mMissionState(MISSION_START)
	, mTime(TEN_SECOND)
	, mFlagTimeCount(0)
	, mSuccessTypingCount(1)
	, mFlagMissionState(MISSION_SEIKO)
	, mKeyCount(0)
	, mKeyCountNikuman(0)
	, mKeyCountYoshitaro(0)
	, mKeyCountNoppo(0)
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission, mState, Start,		cState_Start);
	REGIST_STATE_FUNC2(Mission, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission, mState, Failure,	cState_Failure);
	REGIST_STATE_FUNC2(Mission, mState, Ougi,		cState_Ougi);
	REGIST_STATE_FUNC2(Mission, mState, BadStatus,	cState_BadStatus);
	REGIST_STATE_FUNC2(Mission, mState, End,		cState_End);
	mState.changeState(cState_Idle);
}

Mission::~Mission()
{
}

void Mission::init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo)
{
	mCurrentMissionNo	= 0;
	mTime		= TEN_SECOND;
	mKeyCount		= 0;
	mSuccessTypingCount	= 1;
	mFlagMissionState = MISSION_SEIKO;
	mMissionState = MISSION_START;
	mFlagDraw	= 0;
	mMoveCount	= 0;
	mAlpha		= 0;
	mAlphaPushZ= 255;

	mFlagTimeCount = 0;

	mFlagZ		= true;

	mIsSound	= true;
	mIsSound2 = true;

	mMissionStartPos.x = MISSION_HASSEI_X;
	mMissionStartPos.y = -50.f;

	mKeyCountNikuman		= cnt_nikuman;		//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	mKeyCountYoshitaro	= cnt_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	mKeyCountNoppo		= cnt_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g

	mState.changeState(cState_Start);
}

void Mission::update()
{
	mState.executeState();

	if( mMissionState != MISSION_START && 
		mMissionState != MISSION_MIDDLE)
	{
		if (mAlpha != 0) 
		{
			mAlpha -= MISSION_ALPHA_INCREASE;
			if (mAlpha < 0) { mAlpha = 0; }
		}
	}
}

void Mission::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);

	if(mMissionState != MISSION_START)
	{
		mVertex->setColor(mAlpha,255,255,255);
	}

	mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI + mMissionState);	//�݂�����񔭐�

	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_OSIRASE);	//�݂�����񂨒m�点�g
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_1 + mCurrentMissionNo);	//�݂������

	if(mCurrentMissionNo == MISSION_10 || mCurrentMissionNo == MISSION_11)
	{
		if(mMissionState == MISSION_START)
		{
			UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
			mVertex->setColor(mAlpha,255,255,255);
			mVertex->drawF(Vector2f(400.f, 450.f), R_Z_PUSH_START);
		}
	}

	if(mMissionState == MISSION_MIDDLE){
		updateMissionD();
	}
}

/**
 * @ brief �~�b�V�����X�e�[�g���擾
 */
int
Mission::getMissionState() const
{
	return mMissionState;
}

void Mission::updateMission1()	//�w10�b�ȓ���100��A�ł���I�I�x
{
	if (mTime <= 0)
	{
		if (mKeyCount >= 100)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isAnyKeyPushed())
	{
		mKeyCount++;
	}
	mTime--;
}

void Mission::updateMission2()	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
{
	if (mTime <= 0)
	{
		if (mKeyCount == 50)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isAnyKeyPushed())
	{
		mKeyCount++;
	}
	mTime--;
}

void Mission::updateMission3()	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
{
	if(mTime <= 0)
	{
		if (mKeyCount == 100)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isAnyKeyPushed())
	{
		mKeyCount++;
	}
	mTime--;
}

void Mission::updateMission4()	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
{
	if(mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION4_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isKeyPushed(UtilInput::cKey_N))
	{
		if (mSuccessTypingCount == 1 || mSuccessTypingCount == 7)
		{
			mSuccessTypingCount++;
		}
	}

	if(mSuccessTypingCount < MISSION4_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_M)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_G)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void Mission::updateMission5()	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION5_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if(mSuccessTypingCount < MISSION5_FONT_NUM)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_M)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_R)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 16:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 17:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 18:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
			break;
		case 19:
			if (UtilInput::isKeyPushed(UtilInput::cKey_J)) mSuccessTypingCount++;
			break;
		case 20:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;

		case 21:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 22:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}
	mTime--;
}

void Mission::updateMission6()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION6_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
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

void Mission::updateMission7()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION7_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
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

void Mission::updateMission8()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION8_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
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

void Mission::updateMission9()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	if (mTime <= 0)
	{
		if (mSuccessTypingCount == MISSION9_FONT_NUM)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
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

void Mission::updateMission10()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
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
		if(mTime <= 11*60 - 31 && mTime >= 9*60 + 31){
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
			return;
		}
		else{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
			return;
		}
	}
}

void Mission::updateMission11()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
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
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
			return;
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
			return;
		}
	}
}

void Mission::updateMission12()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	if (mTime <= 0)
	{
		if (mKeyCountNikuman > mKeyCountNoppo && mKeyCountNikuman > mKeyCountYoshitaro)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineOne())
	{
		mKeyCountNikuman++;
	}
	mTime--;
}

void Mission::updateMission13()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	if (mTime <= 0)
	{
		if (mKeyCountYoshitaro > mKeyCountNikuman && mKeyCountYoshitaro > mKeyCountNoppo)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isKeyPushedLineOne())
	{
		mKeyCountYoshitaro++;
	}
	mTime--;
}

void Mission::updateMission14()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	if(mTime <= 0)
	{
		if(mKeyCountNoppo > mKeyCountNikuman && mKeyCountNoppo > mKeyCountYoshitaro)
		{
			mMissionState = MISSION_SEIKO;
			mState.changeState(cState_Success);
		}
		else
		{
			mMissionState = MISSION_SIPPAI;
			mState.changeState(cState_Failure);
		}
		return;
	}
	
	if (UtilInput::isKeyPushedLineThree())
	{
		mKeyCountNoppo++;
	}
	mTime--;
}

void Mission::updateMissionD()
{
	switch(mCurrentMissionNo)
	{
	case MISSION_1:
		updateMission1D();
		break;
	case MISSION_2:
		updateMission2D();
		break;
	case MISSION_3:
		updateMission3D();
		break;
	case MISSION_4:
		updateMission4D();
		break;
	case MISSION_5:
		updateMission5D();
		break;
	case MISSION_6:
		updateMission6D();
		break;
	case MISSION_7:
		updateMission7D();
		break;
	case MISSION_8:
		updateMission8D();
		break;
	case MISSION_9:
		updateMission9D();
		break;
	case MISSION_10:
		updateMission10D();
		break;
	case MISSION_11:
		updateMission11D();
		break;
	case MISSION_12:
		updateMission12D();
		break;
	case MISSION_13:
		updateMission13D();
		break;
	case MISSION_14:
		updateMission14D();
		break;
	}
}

void Mission::updateMission1D()	//�w10�b�ȓ���100��A�ł���I�I�x
{
	drawTime();
	drawCombo();
}

void Mission::updateMission2D()	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
{
	drawTime();
	drawCombo();
}

void Mission::updateMission3D()	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
{
	drawTime();
	drawCombo();
}

void Mission::updateMission4D()	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(125.0f + 29.0f * (i - 1),278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission5D()	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(76.0f + 28.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission6D()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(118.0f + 29.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission7D()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(108.0f + 28.0f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission8D()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(131.0f + 30.f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission9D()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for(int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(96.0f + 29.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

void Mission::updateMission10D()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0)
	{
		mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ,255,255,255);
		mVertex->drawF(Vector2f(400.0f, 450.0f), R_Z_PUSH_START);
	}
}

void Mission::updateMission11D()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(mFlagTimeCount == 0)
	{
		mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ,255,255,255);
		mVertex->drawF(Vector2f(400.0f, 450.0f),R_Z_PUSH_START);
	}
}

void Mission::updateMission12D()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

void Mission::updateMission13D()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

void Mission::updateMission14D()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	drawTime();
}

void Mission::fadeIn()
{
	if(mAlpha == MISSION_ALPHA_MAX){
		mMissionState = MISSION_MIDDLE;
		mState.changeState(cState_Run);
		return ;
	}
	mAlpha += MISSION_ALPHA_INCREASE;
	if(mAlpha > MISSION_ALPHA_MAX){
		mAlpha = MISSION_ALPHA_MAX;
	}
}

void Mission::drawTime()
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

void Mission::drawCombo()
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
Mission::stateEnterIdle()
{
}
void
Mission::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Start
 */
void
Mission::stateEnterStart()
{
	// �݂����������߂��菉����������
	mCurrentMissionNo = rand() % 100 + 1;

	if (mCurrentMissionNo >= 0 && mCurrentMissionNo <= MISSION_1PAR) {
		mCurrentMissionNo = MISSION_1;
	}
	else if (mCurrentMissionNo > MISSION_1PAR && mCurrentMissionNo <= MISSION_2PAR) {
		mCurrentMissionNo = MISSION_2;
	}
	else if (mCurrentMissionNo > MISSION_2PAR && mCurrentMissionNo <= MISSION_3PAR) {
		mCurrentMissionNo = MISSION_3;
	}
	else if (mCurrentMissionNo > MISSION_3PAR && mCurrentMissionNo <= MISSION_4PAR) {
		mCurrentMissionNo = MISSION_4;
	}
	else if (mCurrentMissionNo > MISSION_4PAR && mCurrentMissionNo <= MISSION_5PAR) {
		mCurrentMissionNo = MISSION_5;
	}
	else if (mCurrentMissionNo > MISSION_5PAR && mCurrentMissionNo <= MISSION_6PAR) {
		mCurrentMissionNo = MISSION_6;
	}
	else if (mCurrentMissionNo > MISSION_6PAR && mCurrentMissionNo <= MISSION_7PAR) {
		mCurrentMissionNo = MISSION_7;
	}
	else if (mCurrentMissionNo > MISSION_7PAR && mCurrentMissionNo <= MISSION_8PAR) {
		mCurrentMissionNo = MISSION_8;
	}
	else if (mCurrentMissionNo > MISSION_8PAR && mCurrentMissionNo <= MISSION_9PAR) {
		mCurrentMissionNo = MISSION_9;
	}
	else if (mCurrentMissionNo > MISSION_9PAR && mCurrentMissionNo <= MISSION_10PAR) {
		mCurrentMissionNo = MISSION_10;
	}
	else if (mCurrentMissionNo > MISSION_10PAR && mCurrentMissionNo <= MISSION_11PAR) {
		mCurrentMissionNo = MISSION_11;
	}
	else if (mCurrentMissionNo > MISSION_11PAR && mCurrentMissionNo <= MISSION_12PAR) {
		mCurrentMissionNo = MISSION_12;
		if (mKeyCountNikuman >= mKeyCountNoppo && mKeyCountNikuman >= mKeyCountYoshitaro) {
			mCurrentMissionNo = MISSION_1;
		}
	}
	else if (mCurrentMissionNo > MISSION_12PAR && mCurrentMissionNo <= MISSION_13PAR) {
		mCurrentMissionNo = MISSION_13;
		if (mKeyCountYoshitaro >= mKeyCountNikuman && mKeyCountYoshitaro >= mKeyCountNoppo) {
			mCurrentMissionNo = MISSION_1;
		}
	}
	else if (mCurrentMissionNo > MISSION_13PAR && mCurrentMissionNo <= MISSION_14PAR) {
		mCurrentMissionNo = MISSION_14;
		if (mKeyCountNoppo >= mKeyCountNikuman && mKeyCountNoppo >= mKeyCountYoshitaro) {
			mCurrentMissionNo = MISSION_1;
		}
	}
}
void
Mission::stateStart()
{
	//�ʒu���v�Z
	if (mFlagDraw == 7) {
		fadeIn();
		return;
	}
	if (mFlagDraw % 2 == 0) {
		if (mMissionStartPos.y < MISSION_HASSEI_Y) {
			mMissionStartPos.y += 5.f;
		}
		else {
			mFlagDraw++;
		}
	}
	else if (mFlagDraw % 2 == 1) {
		mMissionStartPos.y -= 5.f;
		if (mMissionStartPos.y == 0.f + 20.f * mMoveCount) {
			mFlagDraw++;
			mMoveCount++;
		}
	}
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission::stateEnterRun()
{
	UtilSound::playOnce(S_OSIRASE);
}
void
Mission::stateRun()
{
	switch (mCurrentMissionNo)
	{
	case MISSION_1:
		updateMission1();
		break;
	case MISSION_2:
		updateMission2();
		break;
	case MISSION_3:
		updateMission3();
		break;
	case MISSION_4:
		updateMission4();
		break;
	case MISSION_5:
		updateMission5();
		break;
	case MISSION_6:
		updateMission6();
		break;
	case MISSION_7:
		updateMission7();
		break;
	case MISSION_8:
		updateMission8();
		break;
	case MISSION_9:
		updateMission9();
		break;
	case MISSION_10:
		updateMission10();
		break;
	case MISSION_11:
		updateMission11();
		break;
	case MISSION_12:
		updateMission12();
		break;
	case MISSION_13:
		updateMission13();
		break;
	case MISSION_14:
		updateMission14();
		break;
	}
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission::stateEnterSuccess()
{
	UtilSound::playOnce(S_M_CLEAR);
}
void
Mission::stateSuccess()
{
	if (mAlpha == 0)
	{
		mMissionState = MISSION_OUGI;
		mState.changeState(cState_Ougi);
		return;
	}
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission::stateEnterFailure()
{
	UtilSound::playOnce(S_M_OVER);
}
void
Mission::stateFailure()
{
	if (mAlpha == 0) {
		mMissionState = MISSION_NEGATIVE;
		mState.changeState(cState_BadStatus);
		return;
	}
}

/**
 * @brief �X�e�[�g:Ougi
 */
void
Mission::stateEnterOugi()
{
}
void
Mission::stateOugi()
{
}

/**
 * @brief �X�e�[�g:BadStatus
 */
void
Mission::stateEnterBadStatus()
{
}
void
Mission::stateBadStatus()
{
}

/**
 * @brief �X�e�[�g:End
 */
void
Mission::stateEnterEnd()
{
}
void
Mission::stateEnd()
{
}