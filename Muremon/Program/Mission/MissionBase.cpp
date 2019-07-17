/******************************************************************
 *	@file	MissionBase.cpp
 *	@brief	ミッション基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "MissionBase.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const int cTimeLimitFrame = 600;
	const Vector2f cDispMissionTimePos = { 375.0f, 125.0f };
	const Vector2f cDispCombo = { 500.0f, 245.0f };
}

 /**
  * @brief	コンストラクタ
  */
MissionBase::MissionBase(MissionId id, Texture* texture, Vertex* vertex)
	: mId(id)
	, mTexture(texture)
	, mVertex(vertex)
	, mKeyCount(0)
	, mSuccessTypingCount(1)
	, mTime(0)
{
}

/**
 * @brief	デストラクタ
 */
MissionBase::~MissionBase()
{
}

/**
 * @brief	実行
 */
void
MissionBase::run()
{
	mTime = cTimeLimitFrame;
	mKeyCount = 0;
	mSuccessTypingCount = 1;

	runImple();
}

/**
 * @brief	更新
 */
void
MissionBase::update()
{
	updateImple();
}

/**
 * @brief	時間切れか？
 */
bool
MissionBase::isTimeOver() const
{
	return (mTime == 0);
}

void 
MissionBase::drawTime() const
{
	// タイム
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 2;i++) {
		int num = mTime;
		for (int j = 0;j < 2 - i;j++) {
			if (j == 0) {
				num = num / 60;
			}
			else {
				num = num / 10;
			}
		}
		mVertex->drawF(Vector2f(cDispMissionTimePos.x + 50.f * i, cDispMissionTimePos.y), R_0_B + num % 10);
	}
}

void 
MissionBase::drawCombo() const
{
	// コンボ
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 3;i++) {
		int num = mKeyCount;
		for (int j = 1;j < 3 - i;j++) {
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispCombo.x + 50.f + 50.f * i, cDispCombo.y), R_0_B + num % 10);
	}
	mVertex->drawF(cDispCombo, R_COMBO);
}