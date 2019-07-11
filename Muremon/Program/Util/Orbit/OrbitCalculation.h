#pragma once

/************************************************************************************
 *	�����F�O���̌v�Z���܂Ƃ߂Ă���܂�����											*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 20��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
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