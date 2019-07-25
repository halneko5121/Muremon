/******************************************************************
 *	@file	SceneRanking.cpp
 *	@brief	�����L���O�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneRanking.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const int cNamePosX = 150;			// ���O��X�̒��S�ʒu
	const int cNamePosY = 150;			// ���O��Y�̒��S�ʒu
	const int cPlacePosX = 50;			// ���ʂ̃t�H���gX�̒��S�ʒu
	const int cDotX = 100;
	const int cScorePosX = 350;			// �X�R�A��X�̒��S�ʒu
	const int cDislocateX = 50;			// X�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)
	const int cDislocateY = 100;		// Y�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)

	enum TEXTURE_DATA_RANKING
	{
		T_RANKING_BG,
		T_RANKING_FONT,
	};

	enum RECT_DATA_RANKING
	{
		R_RANKING_BG,
		R_FONT_A,
		R_FONT_B,
		R_FONT_C,
		R_FONT_D,
		R_FONT_E,
		R_FONT_F,
		R_FONT_G,
		R_FONT_H,
		R_FONT_I,
		R_FONT_J,
		R_FONT_K,
		R_FONT_L,
		R_FONT_M,
		R_FONT_N,
		R_FONT_O,
		R_FONT_P,
		R_FONT_Q,
		R_FONT_R,
		R_FONT_S,
		R_FONT_T,
		R_FONT_U,
		R_FONT_V,
		R_FONT_W,
		R_FONT_X,
		R_FONT_Y,
		R_FONT_Z,
		R_FONT_0,
		R_FONT_1,
		R_FONT_2,
		R_FONT_3,
		R_FONT_4,
		R_FONT_5,
		R_FONT_6,
		R_FONT_7,
		R_FONT_8,
		R_FONT_9,
		R_FONT_DOT,
	};

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_Input,			// ����
		cState_View,			// �m�F
		cState_End,				// �I��
		cState_Count
	};
}

SceneRanking::SceneRanking()
	: mRankNewData()
	, mRankingNo(-1)
	, mInputIndex(0)
	, mInputKey(0)
	, mIsNameAlphaDown(false)
{
	for (int j = 0; j < cRankingCount; j++)
	{
		for (int i = 0; i < cRankingNameCount; i++)
		{
			mNameAlpha[j][i] = 255;
		}
	}

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneRanking, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(SceneRanking, mState, Input,		cState_Input);
	REGIST_STATE_FUNC2(SceneRanking, mState, View,		cState_View);
	REGIST_STATE_FUNC2(SceneRanking, mState, End,		cState_End);
	mState.changeState(cState_Idle);
}

SceneRanking::~SceneRanking()
{
}

/**
 * @brief	������
 */
void
SceneRanking::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "ranking");

	// �v���C����name�̏�����
	mRankNewData.mName[0] = mRankNewData.mName[1] = mRankNewData.mName[2] = 0;

	// �v���C�����X�R�A�̏�����
	mRankNewData.mScore = UtilGame::getScore();

	loadRanking();
	mRankingNo = checkRankingIn();

	// �����N�C�����Ă����RankChenge��
	if (mRankingNo != -1)
	{
		sortRanking(mRankingNo);
		mState.changeState(cState_Input);
	}
	else
	{
		mState.changeState(cState_View);
	}
}

/**
 * @brief	�X�V
 */
void
SceneRanking::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
SceneRanking::draw() const
{
	drawBackGround();
	drawRankingNum();
	drawRankingName();
	drawRankingScore();
}

/**
 * @brief	�V�[���I��
 */
void
SceneRanking::end()
{
	requestChangeScene(cSceneId_Title);
}

/**
 * @brief	�����L���O�̓ǂݍ���
 */
void
SceneRanking::loadRanking()
{
	FILE *fp;
	fopen_s(&fp, "Data\\rankingdata.txt", "r");		//�t�@�C�����J��

	if (fp == NULL)					//�t�@�C�����Ȃ������ꍇ
	{
		MessageBox(NULL, "�t�@�C�����J���܂���ł���", "�G���[", NULL);	//�Ԃ̕����̂Ƃ����\��
		return;
	}

	for (int i = 0; i < cRankingCount; i++)
	{
		fscanf(fp, "%hhd,%hhd,%hhd,%d\n", &mRankData[i].mName[0], &mRankData[i].mName[1], &mRankData[i].mName[2], &mRankData[i].mScore);
	}
	fclose(fp);
}

/**
 * @brief	�����L���O�̏�������
 */
void
SceneRanking::writeRanking()
{
	FILE *fp;
	fopen_s(&fp, "Data\\rankingdata.txt", "w");

	for(int i = 0; i < cRankingCount; i++)
	{
		fprintf(fp,"%d,%d,%d,%d\n",mRankData[i].mName[0],mRankData[i].mName[1],mRankData[i].mName[2],mRankData[i].mScore);
	}
	fclose(fp);
}

/**
 * �����N�C�����Ă邩�`�F�b�N����
 */
int
SceneRanking::checkRankingIn()
{
	int ranking_num = -1;
	for (int i = 0; i < cRankingCount;i++)
	{
		if (mRankData[i].mScore < mRankNewData.mScore) {
			ranking_num = i;
			break;
		}
	}

	return ranking_num;
}

/**
 * @brief	�����L���O�̃\�[�g
 */
void SceneRanking::sortRanking(int new_rank_index)
{
	// �����N�C���������ʂ��炸��Ă���
	if (new_rank_index < cRankingCount)
	{
		for (int j = (cRankingCount-1) ; j > new_rank_index; j--)
		{
			mRankData[j] = mRankData[j-1];
		}

		// �����N�C�������Ƃ���Ƀv���C�����f�[�^������
		mRankData[new_rank_index].mName[0] = mRankNewData.mName[0];
		mRankData[new_rank_index].mName[1] = mRankNewData.mName[1];
		mRankData[new_rank_index].mName[2] = mRankNewData.mName[2];
		mRankData[new_rank_index].mScore	 = mRankNewData.mScore;
	}
}

/**
 * @brief	�w�i�̕`��
 */
void
SceneRanking::drawBackGround() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_RANKING_BG);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, Vector2f(cWindowCenterX, cWindowCenterY), R_RANKING_BG);
}

/**
 * @brief	���ʂ̕`��
 */
void
SceneRanking::drawRankingNum() const
{
	for (int i = 0;i < cRankingCount;i++)
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_RANKING_FONT);
		UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
		UtilGraphics::drawF(mVertex, Vector2f(static_cast<float>(cPlacePosX), static_cast<float>(cNamePosY + i * cDislocateY)), R_FONT_1 + i);
		UtilGraphics::drawF(mVertex, Vector2f(static_cast<float>(cDotX), static_cast<float>(cNamePosY + i * cDislocateY)), R_FONT_DOT);
	}
}

/**
 * @brief	���O�̕`��
 */
void
SceneRanking::drawRankingName() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_RANKING_FONT);
	for (int j = 0;j < cRankingCount;j++)
	{
		for (int i = 0;i < cRankingNameCount;i++)
		{
			UtilGraphics::setVertexColor(mVertex, mNameAlpha[j][i], 255, 255, 255);
			UtilGraphics::drawF(mVertex, Vector2f(static_cast<float>(cNamePosX + i * cDislocateX),
				static_cast<float>(cNamePosY + j * cDislocateY)), R_FONT_A + mRankData[j].mName[i]);
		}
	}
}

/**
 * @brief	�X�R�A�̕`��
 */
void
SceneRanking::drawRankingScore() const
{
	int j = 0;

	for (int i = 0; i < 5; i++)
	{
		int num[9] = { 0 };
		int figure = 0;

		figure = (int)log10((double)mRankData[i].mScore) + 1;	// �X�R�A�̌����v�Z����
		for (int j = figure; j > 0; j--)						// �����Ƃ̐����Z�o
		{
			num[9 - j] = mRankData[i].mScore / (int)pow((double)10, j - 1) - mRankData[i].mScore / (int)pow((double)10, j) * 10;
		}
		for (int j = figure; j > 0; j--)
		{
			UtilGraphics::setTexture(mVertex, *mTexture, T_RANKING_FONT);
			UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
			UtilGraphics::drawF(mVertex, Vector2f(static_cast<float>(cScorePosX + (9 - j)*cDislocateX),
				static_cast<float>(cNamePosY + i * cDislocateY)), R_FONT_0 + num[9 - j]);
		}
	}
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
SceneRanking::stateEnterIdle()
{
}
void
SceneRanking::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Input
 */
void
SceneRanking::stateEnterInput()
{
	mInputIndex = 0;
}
void
SceneRanking::stateInput()
{
	// �L�[���͂ɘA������
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (GetAsyncKeyState(i))
		{
			UtilSound::playOnce(cSoundId_SeCursorMove);
			mInputKey = i - 'A';
			mRankData[mRankingNo].mName[mInputIndex] = mInputKey;
			break;
		}
	}

	// �u�����N
	if (mIsNameAlphaDown)
	{
		mNameAlpha[mRankingNo][mInputIndex] -= 5;
		if (mNameAlpha[mRankingNo][mInputIndex] == 0) mIsNameAlphaDown = false;
	}
	else
	{
		mNameAlpha[mRankingNo][mInputIndex] += 5;
		if (mNameAlpha[mRankingNo][mInputIndex] = 255) mIsNameAlphaDown = true;
	}

	if (UtilInput::isKeyPushedReturn())
	{
		UtilSound::playOnce(cSoundId_SeOk);
		mNameAlpha[mRankingNo][mInputIndex] = 255;
		mInputIndex++;
	}

	// ���͊���
	if (mInputIndex == cRankingNameCount)
	{
		mState.changeState(cState_View);
		return;
	}
}

/**
 * @brief �X�e�[�g:View
 */
void
SceneRanking::stateEnterView()
{
}
void
SceneRanking::stateView()
{
	// �����N�C�����Ă��Ȃ���
	if (UtilInput::isKeyPushedReturn())
	{
		UtilSound::playOnce(cSoundId_SeOk);
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
SceneRanking::stateEnterEnd()
{
	mIsSceneEnd = true;
}
void
SceneRanking::stateEnd()
{
}