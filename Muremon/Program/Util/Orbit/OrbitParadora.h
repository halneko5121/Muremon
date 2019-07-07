#pragma once

/************************************************************************************
 *	役割：放物線処理の設定															*
 *	説明：																			*
 *	作成日：2009年 3月 21日															*
 *	更新日：	年	月	 日															*
 *													by	三上　亘					*
 ************************************************************************************/

#include "Program/Define.h"

class OrbitParabora
{
public:
	OrbitParabora(void);
	~OrbitParabora(void);

	/****************************************************************************************************
	*	役割	：放物線処理																			*
	*	関数名	：POS_CC OrbitParabola(float acceleration, float move_x, float limit_y ,POS_CC draw_cc)	*
	*	引数	：float  acceleration					加速度											*
	*			：float move_x　　移動量	：float limit_y　　yの限界値　	：POS_CC draw_cc　　中心座標*
	*	戻り値	：POS_CC draw_cc  中心座標																*
	*	作成日	：2009年 3月 21日																		*
	*	更新日	：	年	月	 日							by	三上　亘									*
	****************************************************************************************************/
	POS_CC<float> orbitParabola(float acceleration, float move_x, float limit_y ,POS_CC<float> draw_cc, int char_num);
};
