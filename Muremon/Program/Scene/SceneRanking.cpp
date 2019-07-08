/******************************************************************
 *	@file	SceneRanking.cpp
 *	@brief	�����L���O�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneRanking.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilScore.h"
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
}

SceneRanking::SceneRanking()
{
	mIsSceneEnd = false;

	mRankingNo=-1;

	mInputKey = 0;

	mInputIndex = 0;

	for(int j=0;j<5;j++)
	{
		for(int i=0;i<3;i++)
		{
			mNameAlpha[j][i]=255;
		}
	}

	mIsNameAlphaDown=false;
}

SceneRanking::~SceneRanking()
{
}

void
SceneRanking::impleInit()
{
	mTexture->load("Data\\TextureData\\ranking.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->load("Data\\RectData\\ranking.txt");

	// �v���C����name�̏�����
	mRankNewData.mName[0] = mRankNewData.mName[1] = mRankNewData.mName[2] = 0;

	// �v���C�����X�R�A�̏�����
	mRankNewData.mScore = UtilScore::getScore();

	loadRanking();
	mRankingNo = checkRankingIn();

	// �����N�C�����Ă����RankChenge��
	if (mRankingNo != -1)
	{
		sortRanking(mRankingNo);
	}
}

void SceneRanking::update()
{
	updateRanking(mRankingNo);
}

void SceneRanking::updateRanking(int rank)
{
	// �����N�C�����Ă��Ȃ���
	if (rank == -1)
	{
		if (UtilInput::isKeyPushedReturn())
		{
			UtilSound::playOnce(S_SE_OK);
			mIsSceneEnd = true;
		}
		return;
	}

	// ���͊���
	if (mInputIndex == 3)
	{
		if (UtilInput::isKeyPushedReturn())
		{
			UtilSound::playOnce(S_SE_OK);
			writeRanking();
			mIsSceneEnd = true;
		}
		return;
	}

	// �L�[���͂ɘA������
	for(int i = 'A'; i <= 'Z'; i++)
	{
		if(GetAsyncKeyState(i))
		{
			UtilSound::playOnce(S_SE_CURSOR_MOVE);
			mInputKey = i - 'A';
			mRankData[rank].mName[mInputIndex] = mInputKey;
			break;
		}
	}

	// �u�����N
	if (mIsNameAlphaDown)
	{
		mNameAlpha[rank][mInputIndex] -= 5;
		if (mNameAlpha[rank][mInputIndex] == 0) mIsNameAlphaDown = false;
	}
	else 
	{
		mNameAlpha[rank][mInputIndex] += 5;
		if (mNameAlpha[rank][mInputIndex] = 255) mIsNameAlphaDown = true;
	}

	if (UtilInput::isKeyPushedReturn())
	{
		UtilSound::playOnce(S_SE_OK);
		mNameAlpha[rank][mInputIndex] = 255;
		mInputIndex++;
	}
}

void SceneRanking::draw()
{
	drawBackGround();
	drawRankingPlace();
	drawRankingName();
	drawRankingScore();
}

void SceneRanking::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();
}

void SceneRanking::drawBackGround()
{
	mVertex->setTextureData(mTexture->getTextureData(T_RANKING_BG), mDevice);
	mVertex->setColor(255,255,255,255);
	mVertex->drawF(400.f,300.f,R_RANKING_BG);
}

void SceneRanking::drawRankingPlace()
{
	for(int i=0;i<5;i++)
	{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->setColor(255,255,255,255);
			mVertex->drawF((float)cPlacePosX,(float)cNamePosY + i * cDislocateY,R_FONT_1 + i);
			mVertex->drawF((float)cDotX,(float)cNamePosY+i * cDislocateY,R_FONT_DOT);
	}
}

void SceneRanking::drawRankingName()
{
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<3;i++)
		{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->setColor(mNameAlpha[j][i],255,255,255);
			mVertex->drawF((float)cNamePosX+i*cDislocateX,(float)cNamePosY+j*cDislocateY,R_FONT_A + mRankData[j].mName[i]);
		}
	}
}

void SceneRanking::drawRankingScore()
{
	int j=0;

	for(int i = 0; i < 5; i++)
	{	
		int num[9]={0};
		int figure=0;

		figure = (int)log10((double)mRankData[i].mScore) + 1;	// �X�R�A�̌����v�Z����
		for(int j = figure ; j > 0 ; j--)						// �����Ƃ̐����Z�o
		{
			num[9-j] = mRankData[i].mScore / (int)pow((double)10,j - 1) - mRankData[i].mScore / (int)pow((double)10,j) * 10;
		}
		for(int j = figure ; j > 0 ; j--)
		{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->setColor(255,255,255,255);
			mVertex->drawF((float)cScorePosX+(9-j)*cDislocateX,(float)cNamePosY+i*cDislocateY,R_FONT_0 + num[9-j]);
		}
	}
}

void SceneRanking::loadRanking()
{
	FILE *fp;
	fopen_s(&fp, "Data\\rankingdata.txt", "r");		//�t�@�C�����J��

	if (fp == NULL)					//�t�@�C�����Ȃ������ꍇ
	{
		MessageBox(NULL, "�t�@�C�����J���܂���ł���", "�G���[", NULL);	//�Ԃ̕����̂Ƃ����\��
		return;
	}

	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%hhd,%hhd,%hhd,%d\n", &mRankData[i].mName[0], &mRankData[i].mName[1], &mRankData[i].mName[2], &mRankData[i].mScore);
	}
	fclose(fp);
}

void SceneRanking::writeRanking()
{
	FILE *fp;
	fopen_s(&fp, "Data\\rankingdata.txt", "w");

	for(int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5;i++)
	{
		if (mRankData[i].mScore < mRankNewData.mScore) {
			ranking_num = i;
			break;
		}
	}

	return ranking_num;
}

void SceneRanking::sortRanking(int new_rank)
{
	// �����N�C���������ʂ��炸��Ă���
	if (new_rank < 5)
	{
		for (int j = 4 ; j > new_rank; j--)
		{
			mRankData[j] = mRankData[j-1];
		}

		// �����N�C�������Ƃ���Ƀv���C�����f�[�^������
		mRankData[new_rank].mName[0] = mRankNewData.mName[0];
		mRankData[new_rank].mName[1] = mRankNewData.mName[1];
		mRankData[new_rank].mName[2] = mRankNewData.mName[2];
		mRankData[new_rank].mScore	 = mRankNewData.mScore;
	}
}