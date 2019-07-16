/******************************************************************
 *	@file	MissionBase.cpp
 *	@brief	ミッション基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "MissionBase.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

#define TEN_SECOND	(600)

 /**
  * @brief	コンストラクタ
  */
MissionBase::MissionBase(MissionId id, Texture* texture, Vertex* vertex)
	: mId(id)
	, mTexture(texture)
	, mVertex(vertex)
	, mTime(0)
	, mKeyCount(0)
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
MissionBase::runImple()
{
	mTime = TEN_SECOND;

	runImple();
}

void 
MissionBase::drawTime()
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
//		mVertex->drawF(Vector2f(M_TIMENUM_X + 50.f * i, M_TIMENUM_Y), R_0_B + num % 10);
	}
}

void 
MissionBase::drawCombo()
{
	// コンボ
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 3;i++) {
		int num = mKeyCount;
		for (int j = 1;j < 3 - i;j++) {
			num = num / 10;
		}
//		mVertex->drawF(Vector2f(M_COMBO_X + 50.f + 50.f * i, M_COMBO_Y), R_0_B + num % 10);
	}
//	mVertex->drawF(Vector2f(M_COMBO_X, M_COMBO_Y), R_COMBO);
}