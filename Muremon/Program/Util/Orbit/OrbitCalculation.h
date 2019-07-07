#pragma once

/************************************************************************************
 *	�����F�O���̌v�Z���܂Ƃ߂Ă���܂�����											*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 20��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
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

#define RADIUS_NIKU						(37.5f)				//�L�����̔��a
#define RADIUS_YOSHI					(76.5f)				//�L�����̔��a
#define RADIUS_NOPPO					(150.f)				//�L�����̔��a

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