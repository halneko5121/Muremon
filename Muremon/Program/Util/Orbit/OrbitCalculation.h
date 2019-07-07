#pragma once

/************************************************************************************
 *	役割：軌道の計算をまとめてありますたい											*
 *	説明：																			*
 *	作成日：2009年 3月 20日															*
 *	更新日：	年	月	 日															*
 *													by	三上　亘					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include <math.h>
#include <d3dx9math.h>
#include <Time.h>

#include"OrbitWave.h"
#include"OrbitRebound.h"
#include"OrbitParadora.h"

/*================================
		Define
=================================*/

#define RADIUS_NIKU						(37.5f)				//キャラの半径
#define RADIUS_YOSHI					(76.5f)				//キャラの半径
#define RADIUS_NOPPO					(150.f)				//キャラの半径

#define RADIUS_HIT_X_YOSHI				(30.f)				
#define RADIUS_HIT_Y_YOSHI				(40.f)				
#define RADIUS_HIT_X_NOPPO				(50.f)				
#define RADIUS_HIT_Y_NOPPO				(100.f)				

class OrbitCalculation
{
public:

	OrbitCalculation(void);
	~OrbitCalculation(void);

public:
	OrbitWave*		mWave;
	OrbitRebound*		mRebound;
	OrbitParabora*	mParabora;
};