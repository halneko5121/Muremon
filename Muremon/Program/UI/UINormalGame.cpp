/******************************************************************
 *	@file	UINormalGame.cpp
 *	@brief	ノーマルゲームUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UINormalGame.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/UI/UIRefreshGame.h"

namespace
{
	// 表示位置
	const Vector2f cDispScorePos = { 60.0f, 20.0f };
	const Vector2f cDispTimePos = { 60.0f, 70.0f };

	const float cMaxMissionGauge = 5000.0f;
}

/**
 * @brief	コンストラクタ
 */
UINormalGame::UINormalGame()
	: mTexture(nullptr)
	, mVertex(nullptr)
{
	mTexture = new Texture();
	mVertex = new Vertex();
	mUIRefreshGame = new UIRefreshGame();
}

/**
 * @brief	デストラクタ
 */
UINormalGame::~UINormalGame()
{
	mTexture->release();
	APP_SAFE_DELETE(mTexture);
	mVertex->release();
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	初期化
 */
void
UINormalGame::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");
	mUIRefreshGame->init();
}

/**
 * @brief	更新
 */
void
UINormalGame::update()
{
}

/**
 * @brief	描画
 */
void
UINormalGame::draw(const ActorBoss& boss, const float& mission_guage, const int& time) const
{
	mUIRefreshGame->draw(boss);

	drawMissionGuage(mission_guage);

	drawScore();

	drawTime(time);
}

/**
 * @brief	ミッションゲージの描画
 */
void
UINormalGame::drawMissionGuage(const float& mission_guage) const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// 「みっしょんゲージ」
	mVertex->drawF(cDispMissionPos, R_MISSION_GAGE);

	// 実際のミッションゲージ量
	float num = mission_guage / cMaxMissionGauge;
	mVertex->setScale(num, 1.f);
	mVertex->setColor(255, 30, 30, 200);
	mVertex->drawF(Vector2f(cDispMissionGaugePos.x - (1.f - num) * 100.f, cDispMissionGaugePos.y), R_GAGE_IN);

	// ミッションゲージの「枠」
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispMissionGaugePos, R_GAGE_FRAME);	//みっしょんゲージ枠
}

/**
 * @brief	スコアの描画
 */
void
UINormalGame::drawScore() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	mVertex->drawF(cDispScorePos, R_SCORE);		//すこあ

	//スコア
	for (int i = 0;i < 9;i++) {
		int num = UtilGame::getScore();
		for (int j = 1; j < 9 - i;j++) {
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispScoreNumPos.x + 20.f * i, cDispScoreNumPos.y), R_0 + num % 10);
	}
}

/**
 * @brief	タイムの描画
 */
void
UINormalGame::drawTime(const int& time) const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	mVertex->drawF(cDispTimePos, R_TIME);		//たいむ

	//タイム
	for (int i = 0;i < 5;i++)
	{
		int num = time;
		if (i != 2)
		{
			int a = 0;
			if (i > 2)
			{
				a = i - 1;
			}
			else
			{
				a = i;
			}
			for (int j = 0;j < 4 - a;j++)
			{
				if (j == 0)
				{
					num = num / 60;
				}
				else if (j == 2)
				{
					num = num / 6;
				}
				else
				{
					num = num / 10;
				}
			}
			if (i == 0 || i == 3)
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 6);
			}
			else
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 10);
			}
		}
		else
		{
			mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_SEMICORON);
		}
	}
}

