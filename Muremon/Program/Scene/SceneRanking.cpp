/******************************************************************
 *	@file	SceneRanking.cpp
 *	@brief	ランキングシーン
 *
 *	製作者：三上
 *	管理者：三上
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
	const int cNamePosX = 150;			// 名前のXの中心位置
	const int cNamePosY = 150;			// 名前のYの中心位置
	const int cPlacePosX = 50;			// 順位のフォントXの中心位置
	const int cDotX = 100;
	const int cScorePosX = 350;			// スコアのXの中心位置
	const int cDislocateX = 50;			// Xの位置をずらす(但し、同じ値でずらさないと意味がない)
	const int cDislocateY = 100;		// Yの位置をずらす(但し、同じ値でずらさないと意味がない)

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
	mTexture->load("Data\\TextureData\\ranking.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\ranking.txt");

	// プレイしたnameの初期化
	mRankNewData.mName[0] = mRankNewData.mName[1] = mRankNewData.mName[2] = 0;

	// プレイしたスコアの初期化
	mRankNewData.mScore = UtilScore::getScore();

	loadRanking();
	mRankingNo = checkRankingIn();

	// ランクインしていればRankChengeへ
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
	// ランクインしていない時
	if (rank == -1)
	{
		if (UtilInput::isKeyPushedReturn())
		{
			UtilSound::playOnce(S_SE_OK);
			mIsSceneEnd = true;
		}
		return;
	}

	// 入力完了
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

	// キー入力に連動する
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

	// ブリンク
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

		figure = (int)log10((double)mRankData[i].mScore) + 1;	// スコアの桁を計算する
		for(int j = figure ; j > 0 ; j--)						// 桁ごとの数字算出
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
	fopen_s(&fp, "Data\\rankingdata.txt", "r");		//ファイルを開く

	if (fp == NULL)					//ファイルがなかった場合
	{
		MessageBox(NULL, "ファイルを開けませんでした", "エラー", NULL);	//赤の文字のところを表示
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
 * ランクインしてるかチェックする
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
	// ランクインした順位からずれていく
	if (new_rank < 5)
	{
		for (int j = 4 ; j > new_rank; j--)
		{
			mRankData[j] = mRankData[j-1];
		}

		// ランクインしたところにプレイしたデータを入れる
		mRankData[new_rank].mName[0] = mRankNewData.mName[0];
		mRankData[new_rank].mName[1] = mRankNewData.mName[1];
		mRankData[new_rank].mName[2] = mRankNewData.mName[2];
		mRankData[new_rank].mScore	 = mRankNewData.mScore;
	}
}