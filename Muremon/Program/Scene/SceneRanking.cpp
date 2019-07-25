/******************************************************************
 *	@file	SceneRanking.cpp
 *	@brief	ランキングシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneRanking.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
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

	enum State
	{
		cState_Idle,			// 待機
		cState_Input,			// 入力
		cState_View,			// 確認
		cState_End,				// 終了
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
 * @brief	初期化
 */
void
SceneRanking::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "ranking");

	// プレイしたnameの初期化
	mRankNewData.mName[0] = mRankNewData.mName[1] = mRankNewData.mName[2] = 0;

	// プレイしたスコアの初期化
	mRankNewData.mScore = UtilGame::getScore();

	loadRanking();
	mRankingNo = checkRankingIn();

	// ランクインしていればRankChengeへ
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
 * @brief	更新
 */
void
SceneRanking::update()
{
	mState.executeState();
}

/**
 * @brief	描画
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
 * @brief	シーン終了
 */
void
SceneRanking::end()
{
	requestChangeScene(cSceneId_Title);
}

/**
 * @brief	ランキングの読み込み
 */
void
SceneRanking::loadRanking()
{
	FILE *fp;
	fopen_s(&fp, "Data\\rankingdata.txt", "r");		//ファイルを開く

	if (fp == NULL)					//ファイルがなかった場合
	{
		MessageBox(NULL, "ファイルを開けませんでした", "エラー", NULL);	//赤の文字のところを表示
		return;
	}

	for (int i = 0; i < cRankingCount; i++)
	{
		fscanf(fp, "%hhd,%hhd,%hhd,%d\n", &mRankData[i].mName[0], &mRankData[i].mName[1], &mRankData[i].mName[2], &mRankData[i].mScore);
	}
	fclose(fp);
}

/**
 * @brief	ランキングの書き込み
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
 * ランクインしてるかチェックする
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
 * @brief	ランキングのソート
 */
void SceneRanking::sortRanking(int new_rank_index)
{
	// ランクインした順位からずれていく
	if (new_rank_index < cRankingCount)
	{
		for (int j = (cRankingCount-1) ; j > new_rank_index; j--)
		{
			mRankData[j] = mRankData[j-1];
		}

		// ランクインしたところにプレイしたデータを入れる
		mRankData[new_rank_index].mName[0] = mRankNewData.mName[0];
		mRankData[new_rank_index].mName[1] = mRankNewData.mName[1];
		mRankData[new_rank_index].mName[2] = mRankNewData.mName[2];
		mRankData[new_rank_index].mScore	 = mRankNewData.mScore;
	}
}

/**
 * @brief	背景の描画
 */
void
SceneRanking::drawBackGround() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_RANKING_BG);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, Vector2f(cWindowCenterX, cWindowCenterY), R_RANKING_BG);
}

/**
 * @brief	順位の描画
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
 * @brief	名前の描画
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
 * @brief	スコアの描画
 */
void
SceneRanking::drawRankingScore() const
{
	int j = 0;

	for (int i = 0; i < 5; i++)
	{
		int num[9] = { 0 };
		int figure = 0;

		figure = (int)log10((double)mRankData[i].mScore) + 1;	// スコアの桁を計算する
		for (int j = figure; j > 0; j--)						// 桁ごとの数字算出
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
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
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
 * @brief ステート:Input
 */
void
SceneRanking::stateEnterInput()
{
	mInputIndex = 0;
}
void
SceneRanking::stateInput()
{
	// キー入力に連動する
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

	// ブリンク
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

	// 入力完了
	if (mInputIndex == cRankingNameCount)
	{
		mState.changeState(cState_View);
		return;
	}
}

/**
 * @brief ステート:View
 */
void
SceneRanking::stateEnterView()
{
}
void
SceneRanking::stateView()
{
	// ランクインしていない時
	if (UtilInput::isKeyPushedReturn())
	{
		UtilSound::playOnce(cSoundId_SeOk);
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:End
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