/******************************************************************
 *	@file	UIRefreshGame.cpp
 *	@brief	リフレッシュゲームUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UIRefreshGame.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/DefineGame.h"

namespace
{
	// 表示位置
	const Vector2f cDispStateFramePos = { 400.0f, 560.0f };
	const Vector2f cDispBossHpPos = { 675.0f, 540.0f };
	const Vector2f cDispGaugePos = { 675.0f, 570.0f };
	const float cDispFaceIconPosX = 30.f;
	const Vector2f cDispFaceIconPosYoshi = { cDispFaceIconPosX, 535.0f };
	const Vector2f cDispFaceIconPosNikuman = { cDispFaceIconPosX, 560.0f };
	const Vector2f cDispFaceIconPosNoppo = { cDispFaceIconPosX, 585.0f };
	const float cDispPushKeyCountPosX = 60.f;
}

/**
 * @brief	コンストラクタ
 */
UIRefreshGame::UIRefreshGame()
	: mTexture(nullptr)
	, mVertex(nullptr)
{
	mTexture = new Texture();
	mVertex = new Vertex();
}

/**
 * @brief	デストラクタ
 */
UIRefreshGame::~UIRefreshGame()
{
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	初期化
 */
void
UIRefreshGame::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");
}

/**
 * @brief	更新
 */
void
UIRefreshGame::update()
{
}

/**
 * @brief	描画
 */
void
UIRefreshGame::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// ステータス枠描画
	UtilGraphics::drawF(mVertex, cDispStateFramePos, R_STATE_FRAME);
	UtilGraphics::drawF(mVertex, cDispFaceIconPosNikuman, R_F_NIKUMAN);	//にくまん顔
	UtilGraphics::drawF(mVertex, cDispFaceIconPosYoshi, R_F_YOSHITARO);	//よしたろう顔
	UtilGraphics::drawF(mVertex, cDispFaceIconPosNoppo, R_F_NOPPO);		//のっぽ顔

	drawKeyCount();
	drawHpGauge();
}

/**
 * @brief	連打数描画
 */
void 
UIRefreshGame::drawKeyCount() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	//にくまん
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getWeakAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		UtilGraphics::drawF(mVertex, Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconPosNikuman.y), R_0 + num % 10);
	}
	//よしたろう
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getMediumAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		UtilGraphics::drawF(mVertex, Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconPosYoshi.y), R_0 + num % 10);
	}
	//のっぽ
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getStrongAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		UtilGraphics::drawF(mVertex, Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconPosNoppo.y), R_0 + num % 10);
	}
}

/**
 * @brief	HPゲージの描画
 */
void
UIRefreshGame::drawHpGauge() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// 「しゃっくの体力」
	UtilGraphics::drawF(mVertex, cDispBossHpPos, R_HP);

	// 実際の体力ゲージ量
	float num = UtilBattle::getBossLifeRate();
	UtilGraphics::setVertexScale(mVertex, num, 1.0f);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 0, 0);
	UtilGraphics::drawF(mVertex, Vector2f(cDispGaugePos.x - (1.f - num) * 100.f, cDispGaugePos.y), R_GAGE_IN);	//体力ゲージ

	// 体力ゲージの「枠」
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	UtilGraphics::drawF(mVertex, cDispGaugePos, R_GAGE_FRAME);
}