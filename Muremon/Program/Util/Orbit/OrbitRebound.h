#pragma once

/************************************************************************************
 *	役割	：跳ね返り処理の設定													*		
 *	説明	：今後処理が増えることを考慮し一応クラスわけしました					*														
 *	作成日	：2009年 3月 20日														*	
 *	更新日	：	年	月	 日															*
 *													by	三上　亘					*
 ************************************************************************************/

#include "Program/Define.h"

class C_OrbitRebound
{
public:
	C_OrbitRebound(void);
	~C_OrbitRebound(void);

	/************************************************************************************
	*	役割	：跳ね返り処理(120〜150)												*
	*	関数名	：POS_CC OrbitRebound(float deg, float radius, POS_CC draw_cc)			*
	*	引数	：float deg			角度	：float radius			半径				*
	*	引数	：POS_CC draw_cc	中心座標											*
	*	戻り値	：POS_CC draw_cc	中心座標											*
	*	作成日	：2009年 3月 20日														*
	*	更新日	：	年	月	 日							by	三上　亘					*
	************************************************************************************/
	POS_CC<float> orbitRebound(float deg, float radius, POS_CC<float> draw_cc);
};
