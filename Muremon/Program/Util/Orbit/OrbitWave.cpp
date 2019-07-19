/******************************************************************
 *	@file	OrbitWave.cpp
 *	@brief	正弦波軌道
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "OrbitWave.h"

/**
 * @brief コンストラクタ
 */
OrbitWave::OrbitWave()
	: mAmplitude(0)
	, mCycleFrame(0)
	, mSpeedX(0.0f)
	, mTime(0)
{
}

/**
 * @brief デストラクタ
 */
OrbitWave::~OrbitWave()
{
}

/**
 * @brief 初期化
 * @param amplitude		振幅の量(上下の幅)
 * @param cycle_frame	周期の時間（フレーム）
 * @param speed_x		移動の早さ
 */
void
OrbitWave::init(int amplitude, int cycle_frame, float speed_x)
{
	mTime = 0;
	mAmplitude = amplitude;
	mCycleFrame = cycle_frame;
	mSpeedX = speed_x;
}

/**
 * @brief 振幅の設定
 * @param amplitude		振幅の量(上下の幅)
 */
void
OrbitWave::setAmplitude(int amplitude)
{
	mAmplitude = amplitude;
}

/**
 * @brief 周期フレームの変更
 * @param cycle_frame	周期フレーム
 */
void
OrbitWave::setCycleFrame(int cycle_frame)
{
	mCycleFrame = cycle_frame;
}

/**
 * @brief 速度の設定
 * @param speed_x		速度
 */
void
OrbitWave::setSpeed(float speed_x)
{
	mSpeedX = speed_x;
}

/**
 * @brief 正弦波の更新
 * @param dst_pos	位置の出力
 */
void
OrbitWave::update(Vector2f* dst_pos)
{
	dst_pos->x += mSpeedX;
	dst_pos->y = dst_pos->y + sin(PI * 2 / mCycleFrame * mTime) * mAmplitude;
	mTime++;
}
