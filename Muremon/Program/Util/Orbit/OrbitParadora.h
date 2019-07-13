#pragma once

/************************************************************************************
 *	�����F�����������̐ݒ�															*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 21��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
 ************************************************************************************/

#include "Program/Define.h"

class OrbitParabora
{
public:
	OrbitParabora();
	~OrbitParabora();

	/****************************************************************************************************
	*	����	�F����������																			*
	*	�֐���	�FPOS_CC OrbitParabola(float acceleration, float move_x, float limit_y ,POS_CC draw_cc)	*
	*	����	�Ffloat  acceleration					�����x											*
	*			�Ffloat move_x�@�@�ړ���	�Ffloat limit_y�@�@y�̌��E�l�@	�FPOS_CC draw_cc�@�@���S���W*
	*	�߂�l	�FPOS_CC draw_cc  ���S���W																*
	*	�쐬��	�F2009�N 3�� 21��																		*
	*	�X�V��	�F	�N	��	 ��							by	�O��@�j									*
	****************************************************************************************************/
	Vector2<float> orbitParabola(float acceleration, float move_x, float limit_y ,Vector2<float> draw_cc);

private:
	int mTime;
};
