#pragma once

/************************************************************************************
 *	����	�F���˕Ԃ菈���̐ݒ�													*		
 *	����	�F���㏈���������邱�Ƃ��l�����ꉞ�N���X�킯���܂���					*														
 *	�쐬��	�F2009�N 3�� 20��														*	
 *	�X�V��	�F	�N	��	 ��															*
 *													by	�O��@�j					*
 ************************************************************************************/

#include "Program/Define.h"

class C_OrbitRebound
{
public:
	C_OrbitRebound(void);
	~C_OrbitRebound(void);

	/************************************************************************************
	*	����	�F���˕Ԃ菈��(120�`150)												*
	*	�֐���	�FPOS_CC OrbitRebound(float deg, float radius, POS_CC draw_cc)			*
	*	����	�Ffloat deg			�p�x	�Ffloat radius			���a				*
	*	����	�FPOS_CC draw_cc	���S���W											*
	*	�߂�l	�FPOS_CC draw_cc	���S���W											*
	*	�쐬��	�F2009�N 3�� 20��														*
	*	�X�V��	�F	�N	��	 ��							by	�O��@�j					*
	************************************************************************************/
	POS_CC<float> orbitRebound(float deg, float radius, POS_CC<float> draw_cc);
};
