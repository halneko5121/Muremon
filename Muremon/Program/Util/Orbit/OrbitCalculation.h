#pragma once

/************************************************************************************
 *	役割：軌道の計算をまとめてありますたい											*
 *	説明：																			*
 *	作成日：2009年 3月 20日															*
 *	更新日：	年	月	 日															*
 *													by	三上　亘					*
 ************************************************************************************/

#include"OrbitWave.h"
#include"OrbitRebound.h"
#include"OrbitParadora.h"

class OrbitCalculation
{
public:
	OrbitCalculation(void);
	~OrbitCalculation(void);

public:
	OrbitWave*			mWave;
	OrbitRebound*		mRebound;
	OrbitParabora*		mParabora;
};