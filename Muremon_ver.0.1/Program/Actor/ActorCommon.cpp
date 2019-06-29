#include "ActorCommon.h"

namespace
{
	// ���x�֌W
	const int SPEED_RAND		= (450 / 60);	// �L�����̑���		
	const int SPEED_MIN			= (200 / 60);

	// ���܂�(����)
	const int SPEED_RAND_NIKU	= 15;			// ���̉񐔂������ĖړI�n�_�ɓ��B����
	const int SPEED_MIN_NIKU	= 15;
}

//l,t,r,b
//���S����A�㉺���E�̕�
F_RECT rect_pos_p[] = {
	{RADIUS_NIKU ,RADIUS_NIKU ,RADIUS_NIKU ,RADIUS_NIKU},
	{RADIUS_HIT_X_YOSHI,RADIUS_HIT_Y_YOSHI,RADIUS_HIT_X_YOSHI,RADIUS_HIT_Y_YOSHI},
	{RADIUS_HIT_X_NOPPO,RADIUS_HIT_Y_NOPPO,RADIUS_HIT_X_NOPPO,RADIUS_HIT_Y_NOPPO},
};

F_RECT rect_pos_e = {DRAW_E_RAD_X,DRAW_E_RAD_Y,DRAW_E_RAD_X,DRAW_E_RAD_Y};

/**
 * @brief �R���X�g���N�^
 */
C_CharaCommon::C_CharaCommon(void)
{
	m_pOrbit	 = new C_OrbitCalculation();

	m_pSound	 = new C_DSound();
}

/**
 * @brief �f�X�g���N�^
 */
C_CharaCommon::~C_CharaCommon(void)
{
}

/**
 * @brief �U������
 */
POS_CC<float>
C_CharaCommon::CharaAttack_1(int m_chara_num)
{
	m_charadata[m_chara_num].draw_cc.x += m_charadata[m_chara_num].speed;			//�E�Ɉړ�

	return m_charadata[m_chara_num].draw_cc;
}

/**
 * @brief �Փ˃`�F�b�N
 */
bool
C_CharaCommon::HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int chara_id)
{
	F_RECT check_rect_p = { 0.f,0.f,0.f,0.f };
	F_RECT check_rect_e = { 0.f,0.f,0.f,0.f };

	if(draw_cc_p.x < DEADLINE) return FALSE;

	switch(chara_id){
	case ID_YOSHI:
		if(draw_cc_p.y < 50) return FALSE;	break;
	case ID_NIKUMAN:
		if(draw_cc_p.y < 75) return FALSE;	break;
	case ID_NOPPO:
		if(draw_cc_p.y < 0) return FALSE;	break;
	}

	check_rect_p = CalculateBack_Rect(draw_cc_p,rect_pos_p[chara_id]);			
	check_rect_e = CalculateBack_Rect(draw_cc_e,rect_pos_e);									

	//�܂��~�̓����蔻��
//	if( (pow( (draw_cc_e.x - draw_cc_p.x),2) + pow( (draw_cc_e.y - draw_cc_p.y),2)) <= pow((rect_pos_p[chara_id].top + DRAW_E_RAD_X),2) ){
		//�~�̓����蔻��ɓ����Ă������`�ł̓����蔻��
		if( (check_rect_p.right >= check_rect_e.left)	&& (check_rect_p.left	<= check_rect_e.right) &&
			(check_rect_p.top	<= check_rect_e.bottom) && (check_rect_p.bottom >= check_rect_e.top	 ) ){
				return TRUE;
		}
//	}

	return FALSE;
}

/**
 * @brief �l�����v�Z
 */
F_RECT
C_CharaCommon::CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos)
{
	// ���S���W���炻�ꂼ��G�̔��a�����E���Z 
	rect_pos.left		= (draw_cc.x - rect_pos.left);
	rect_pos.top		= (draw_cc.y - rect_pos.top);
	rect_pos.right		= (draw_cc.x + rect_pos.right);
	rect_pos.bottom		= (draw_cc.y + rect_pos.bottom);

	return rect_pos;
}

/**
 * @brief �X�s�[�h�̐ݒ�
 */
float
C_CharaCommon::SetSpeed(int key)
{
	switch(key){
	case KEY_SKY_2://���܂�̍U��2�͌v�Z���@���Ⴄ�̂�
		m_randspeed = (float)(rand() % SPEED_RAND_NIKU) + SPEED_MIN_NIKU;
		break;
	default:
		m_randspeed = (float)(rand() % SPEED_RAND) + SPEED_MIN;			
		break;
	}
	return m_randspeed;
}

/**
 * @brief �U���t���O�̐ݒ�
 */
CHARADATA
C_CharaCommon::SetAtk_Flag(int key , CHARADATA set_charadata)
{
	switch(key){
		case KEY_GROUND_1: case KEY_GROUND_2: case KEY_GROUND_3:
			set_charadata.flag_atk1 = true;
			break;
		case KEY_SKY_1:	   case KEY_SKY_2:	  case KEY_SKY_3:
			set_charadata.flag_atk2 = true;
			break;
	}	
	return set_charadata;
}

/**
 * @brief �ʒu�̐ݒ�
 */
POS_CC<float>
C_CharaCommon::SetAtk_Pos(float start_x, float start_y)
{
	POS_CC<float> draw_cc = {0.f,0.f};

	draw_cc.x = (-start_x);
	draw_cc.y = start_y;

	return draw_cc;
}

/**
 * @brief �t�H���g�ʒu�̐ݒ�
 */
POS_CC<float>
C_CharaCommon::SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font)
{
	POS_CC<float> pos_effectfont = { 0.f	,0.f };

	//�w�׃`���I�x�Ƃ��\���ʒu(���S���W���獶��)
	pos_effectfont.x = (font_cc.x - (chara_radius + range_font) );
	pos_effectfont.y = (font_cc.y - (chara_radius + range_font) );

	return pos_effectfont;
}

/**
 * @brief �V�F�C�N����
 */
POS_CC<float>
C_CharaCommon::EffectShake(float change_x ,float change_y, POS_CC<float> font_cc)
{
	static float shake_x	,shake_y	= 0.f; 
	static bool  flag_shake_right,flag_shake_down = false; 
	static int	 shake_count = 0;

	if(shake_x > change_x)			{ flag_shake_right = false; shake_count++; }
	else if(shake_x < (-change_x))	{ flag_shake_right = true;  shake_count++; }

	if(shake_y > change_y)		  { flag_shake_down = false; }
	else if(shake_y <-(change_y)) { flag_shake_down = true;  }

	if(shake_count > 5)	{ flag_shake_down = true;  shake_count = 0; }

	font_cc.x += (flag_shake_right) ? shake_x++ : shake_x--;
	font_cc.y += (flag_shake_down ) ? shake_y++ : shake_y--;

	return font_cc;
}