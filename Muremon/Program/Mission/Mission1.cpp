/******************************************************************
 *	@file	Mission1.cpp
 *	@brief	ミッション1
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission1.h"

 /**
  * @brief	コンストラクタ
  */
Mission1::Mission1(MissionId id)
	: MissionBase(id)
	, mState()
{
}

/**
 * @brief	デストラクタ
 */
Mission1::~Mission1()
{
}

/**
 * @brief	更新
 */
void
Mission1::update()
{
}

/**
 * @brief	描画
 */
void
Mission1::draw()
{
}

/**
 * @brief	終了したか？
 */
bool
Mission1::isEnd() const
{
	return false;
}