#pragma once

/************************************************************************************
 *	�����F�����������̐ݒ�															*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 21��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include <math.h>
#include <d3dx9math.h>

#include "Define.h"

/*================================
		Define
=================================*/
#define GRAVITY 						(0.98f)				//�d�͉����x

/*================================
		Class
=================================*/
class C_OrbitParadora
{
public:
	/****************************************************************************************************
	*	����	�F����������																			*
	*	�֐���	�FPOS_CC OrbitParabola(float acceleration, float move_x, float limit_y ,POS_CC draw_cc)	*
	*	����	�Ffloat  acceleration					�����x											*
	*			�Ffloat move_x�@�@�ړ���	�Ffloat limit_y�@�@y�̌��E�l�@	�FPOS_CC draw_cc�@�@���S���W*
	*	�߂�l	�FPOS_CC draw_cc  ���S���W																*
	*	�쐬��	�F2009�N 3�� 21��																		*
	*	�X�V��	�F	�N	��	 ��							by	�O��@�j									*
	****************************************************************************************************/
	POS_CC<float> OrbitParabola(float acceleration, float move_x, float limit_y ,POS_CC<float> draw_cc, int char_num);
	
	
	C_OrbitParadora(void);
	~C_OrbitParadora(void);
};
