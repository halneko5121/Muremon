#include "OrbitRebound.h"
/******************************************************************
 *	@file	OrbitRebound.cpp
 *	@brief	跳ね返り処理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

/**
 * @brief コンストラクタ
 */
OrbitRebound::OrbitRebound(float degree, float speed)
	: mDegree(degree)
	, mSpeed(speed)
{
}

/**
 * @brief デストラクタ
 */
OrbitRebound::~OrbitRebound()
{
}

/**
 * @brief 角度の設定
 */
void
OrbitRebound::setDegree(float degree)
{
	mDegree = degree;
}

/**
 * @brief 速度の設定
 */
void
OrbitRebound::setSpeed(float speed)
{
	mSpeed = speed;
}

/**
 * @brief 跳ね返りの更新
 */
void
OrbitRebound::update(Vector2f* dst_pos)
{
	float rad = mDegree * RAD;
	float add_x = mSpeed * static_cast<float>(cos(rad));		// 速さは半径の大きさに比例
	float add_y = mSpeed * static_cast<float>(sin(rad));

	dst_pos->x += add_x;
	dst_pos->y += add_y;
}