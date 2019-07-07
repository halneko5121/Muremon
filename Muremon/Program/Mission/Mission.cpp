#include "Mission.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"

#define TEN_SECOND	(600)

#define M_TIMENUM_X	(375.f)
#define M_TIMENUM_Y	(125.f)

#define M_COMBO_X	(500.f)
#define M_COMBO_Y	(245.f)

#define MISSION4_FONT_NUM	(16)
#define MISSION5_FONT_NUM	(23)
#define MISSION6_FONT_NUM	(17)
#define MISSION7_FONT_NUM	(19)
#define MISSION8_FONT_NUM	(15)
#define MISSION9_FONT_NUM	(20)

#define MISSION_1PAR	(10)
#define MISSION_2PAR	(20)
#define MISSION_3PAR	(25)
#define MISSION_4PAR	(35)
#define MISSION_5PAR	(40)
#define MISSION_6PAR	(50)
#define MISSION_7PAR	(55)
#define MISSION_8PAR	(65)
#define MISSION_9PAR	(70)
#define MISSION_10PAR	(75)
#define MISSION_11PAR	(85)
#define MISSION_12PAR	(90)
#define MISSION_13PAR	(95)
#define MISSION_14PAR	(100)

#define MISSION_ALPHA_INCREASE	(5)
#define MISSION_ALPHA_MAX	(255)

#define MISSION_HASSEI_X	(400.f)
#define MISSION_HASSEI_Y	(50.f)

#define MISSION_OSIRASE_X	(400.f)
#define MISSION_OSIRASE_Y	(300.f)

namespace
{
	enum MISSION_NUMBER
	{
		MISSION_1,	//�w10�b�ȓ���100��A�ł���I�I�x
		MISSION_2,	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
		MISSION_3,	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
		MISSION_4,	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
		MISSION_5,	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
		MISSION_6,	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
		MISSION_7,	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
		MISSION_8,	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
		MISSION_9,	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
		MISSION_10,	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
		MISSION_11,	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
		MISSION_12,	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
		MISSION_13,	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
		MISSION_14,	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
	};
}

Mission::Mission(Texture* m_texture,Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev)
{
	texture = m_texture;
	vertex	= m_vertex;
	pDevice = apDev;

	cnt_key_nikuman = 0;	//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	cnt_key_yoshitaro = 0;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	cnt_key_noppo = 0;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g

	mission_no	= 0;
	key_state	= 0;
	time		= TEN_SECOND;
	key_cnt		= 0;
	success_type_count	= 1;
	flag_mission_state = MISSION_SEIKO;
	mission_state = MISSION_START;
	flag_draw	= 0;
	cnt_move	= 0;
	alpha_count = 0;
	alpha		= 0;
	alpha_push_z= 255;
	flag_time_cnt = 0;

	flag_z		= true;

	flag_init	= false;

	flag_sound	= true;
	flag_sound2 = true;

	mission_start.x = MISSION_HASSEI_X;
	mission_start.y = -50.f;
}

Mission::~Mission(void)
{
}

void Mission::Init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo)
{
	mission_no	= 0;
	key_state	= 0;
	time		= TEN_SECOND;
	key_cnt		= 0;
	success_type_count	= 1;
	flag_mission_state = MISSION_SEIKO;
	mission_state = MISSION_START;
	flag_draw	= 0;
	cnt_move	= 0;
	alpha_count = 0;
	alpha		= 0;
	alpha_push_z= 255;

	flag_time_cnt = 0;

	flag_z		= true;

	flag_init	= false;

	flag_sound	= true;
	flag_sound2 = true;

	mission_start.x = MISSION_HASSEI_X;
	mission_start.y = -50.f;

	cnt_key_nikuman		= cnt_nikuman;		//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	cnt_key_yoshitaro	= cnt_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	cnt_key_noppo		= cnt_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g
}

int Mission::Control()
{
	if(mission_state == MISSION_START){
		MissionSelect();
		//�ʒu���v�Z
		if(flag_draw == 7){
			FadeIn();
			return mission_state;
		}
		if(flag_draw%2 == 0){
			if(mission_start.y < MISSION_HASSEI_Y){
				mission_start.y += 5.f;
			}
			else{
				flag_draw++;
			}
		}
		else if(flag_draw%2 == 1){
			mission_start.y -= 5.f;
			if(mission_start.y == 0.f + 20.f * cnt_move){
				flag_draw++;
				cnt_move++;
			}
		}
	}
	else if(mission_state == MISSION_MIDDLE){
		if(flag_sound){
			UtilSound::playOnce(S_OSIRASE);
			flag_sound = false;
		}
		MissionControl();
	}
	else{
		if(mission_state == MISSION_SEIKO){
			if(flag_sound2){
				UtilSound::playOnce(S_M_CLEAR);
				flag_sound = false;
			}
		}
		else if(mission_state == MISSION_SIPPAI){
			if(flag_sound2){
				UtilSound::playOnce(S_M_OVER);
				flag_sound2 = false;
			}
		}
		FadeOut();
	}
	return mission_state;
}

void Mission::Draw()
{
	vertex->SetTextureData(texture->GetTextureData(T_MISSION),pDevice);

	if(mission_state != MISSION_START){
		vertex->SetColor(alpha,255,255,255);
	}

	vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI + mission_state);	//�݂�����񔭐�

	vertex->SetColor(alpha,255,255,255);
	vertex->DrawF(MISSION_OSIRASE_X,MISSION_OSIRASE_Y,R_MISSION_OSIRASE);	//�݂�����񂨒m�点�g
	vertex->DrawF(MISSION_OSIRASE_X,MISSION_OSIRASE_Y,R_MISSION_1 + mission_no);	//�݂������

	if(mission_no == MISSION_10 || mission_no == MISSION_11){
		if(mission_state == MISSION_START){
			vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
			vertex->SetColor(alpha,255,255,255);
			vertex->DrawF(400.f,450.f,R_Z_PUSH_START);
		}
	}

	if(mission_state == MISSION_MIDDLE){
		MissionControlD();
	}
	else{
	}
}

void Mission::MissionControl()
{
	switch(mission_no)
	{
	case MISSION_1:
		Mission1();
		break;
	case MISSION_2:
		Mission2();
		break;
	case MISSION_3:
		Mission3();
		break;
	case MISSION_4:
		Mission4();
		break;
	case MISSION_5:
		Mission5();
		break;
	case MISSION_6:
		Mission6();
		break;
	case MISSION_7:
		Mission7();
		break;
	case MISSION_8:
		Mission8();
		break;
	case MISSION_9:
		Mission9();
		break;
	case MISSION_10:
		Mission10();
		break;
	case MISSION_11:
		Mission11();
		break;
	case MISSION_12:
		Mission12();
		break;
	case MISSION_13:
		Mission13();
		break;
	case MISSION_14:
		Mission14();
		break;
	}
	//time++;
}

void Mission::Mission1()	//�w10�b�ȓ���100��A�ł���I�I�x
{
	if (time <= 0)
	{
		if (key_cnt >= 100)	mission_state = MISSION_SEIKO;
		else				mission_state = MISSION_SIPPAI;
		return;
	}

	if (UtilInput::IsAnyKeyPushed())
	{
		key_cnt++;
	}
	time--;
}

void Mission::Mission2()	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
{
	if (time <= 0)
	{
		if (key_cnt == 50)	mission_state = MISSION_SEIKO;
		else				mission_state = MISSION_SIPPAI;
		return;
	}
	
	if (UtilInput::IsAnyKeyPushed())
	{
		key_cnt++;
	}
	time--;
}

void Mission::Mission3()	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
{
	if(time <= 0)
	{
		if(key_cnt == 100)	mission_state = MISSION_SEIKO;
		else				mission_state = MISSION_SIPPAI;
		return;
	}
	
	if (UtilInput::IsAnyKeyPushed())
	{
		key_cnt++;
	}
	time--;
}

void Mission::Mission4()	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
{
	if(time <= 0)
	{
		if(success_type_count == MISSION4_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
	{
		if (success_type_count == 1 || success_type_count == 7)
		{
			success_type_count++;
		}
	}

	if(success_type_count < MISSION4_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_M)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_G)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_E)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 15:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission5()	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
{
	if (time <= 0)
	{
		if(success_type_count == MISSION5_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(success_type_count < MISSION5_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_M)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;

		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_E)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_R)) success_type_count++;
			break;
		case 15:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 16:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 17:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 18:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 19:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_J)) success_type_count++;
			break;
		case 20:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;

		case 21:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 22:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission6()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	if (time <= 0)
	{
		if(success_type_count == MISSION6_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(success_type_count < MISSION6_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_Y)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_R)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_H)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;

		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 15:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_C)) success_type_count++;
			break;
		case 16:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission7()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	if (time <= 0)
	{
		if (success_type_count == MISSION7_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(success_type_count < MISSION7_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_Y)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_R)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_H)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;

		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_E)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;
		case 15:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_H)) success_type_count++;
			break;
		case 16:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 17:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 18:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission8()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	if (time <= 0)
	{
		if (success_type_count == MISSION8_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(success_type_count < MISSION8_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_E)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;

		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_E)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission9()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	if (time <= 0)
	{
		if (success_type_count == MISSION9_FONT_NUM)	mission_state = MISSION_SEIKO;
		else											mission_state = MISSION_SIPPAI;
		return;
	}

	if(success_type_count < MISSION9_FONT_NUM)
	{
		switch (success_type_count)
		{
		case 1:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_N)) success_type_count++;
			break;
		case 2:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 3:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 4:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 5:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 6:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_B)) success_type_count++;
			break;
		case 7:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 8:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 9:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		case 10:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_S)) success_type_count++;
			break;

		case 11:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 12:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_R)) success_type_count++;
			break;
		case 13:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_I)) success_type_count++;
			break;
		case 14:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_K)) success_type_count++;
			break;
		case 15:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_O)) success_type_count++;
			break;
		case 16:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_P)) success_type_count++;
			break;
		case 17:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_U)) success_type_count++;
			break;
		case 18:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_T)) success_type_count++;
			break;
		case 19:
			if (UtilInput::IsKeyPushed(UtilInput::cKey_A)) success_type_count++;
			break;
		default:
			break;
		}
	}
	time--;
}

void Mission::Mission10()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(flag_time_cnt == 0){
		time = 0;
		if(!flag_z){
			alpha_push_z += 5;
			if(alpha_push_z == 240){
				flag_z = true;
			}
		}
		else{
			alpha_push_z -= 5;
			if(alpha_push_z == 50){
				flag_z = false;
			}
		}
	}
	if (UtilInput::IsKeyPushedDecide())
	{
		flag_time_cnt += 1;
	}
	if(flag_time_cnt == 1){
		time++;
	}
	else if(flag_time_cnt == 2)
	{
		if(time <= 11*60 - 31 && time >= 9*60 + 31){
			mission_state = MISSION_SEIKO;
		}
		else{
			mission_state = MISSION_SIPPAI;
		}
	}
}

void Mission::Mission11()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(flag_time_cnt == 0){
		time = 0;
		if(!flag_z){
			alpha_push_z += 5;
			if(alpha_push_z == 240){
				flag_z = true;
			}
		}
		else{
			alpha_push_z -= 5;
			if(alpha_push_z == 50){
				flag_z = false;
			}
		}
	}
	if (UtilInput::IsKeyPushedDecide())
	{
		flag_time_cnt += 1;
		if(flag_time_cnt > 2)
		{
			flag_time_cnt = 2;
		}
	}
	if(flag_time_cnt == 1)
	{
		time++;
	}
	else if(flag_time_cnt == 2)
	{
		if(time <= 6*60 - 31 && time >= 4*60 + 31)
		{
			mission_state = MISSION_SEIKO;
		}
		else
		{
			mission_state = MISSION_SIPPAI;
		}
	}
}

void Mission::Mission12()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	if (time <= 0)
	{
		if (cnt_key_nikuman > cnt_key_noppo && cnt_key_nikuman > cnt_key_yoshitaro)
		{
			mission_state = MISSION_SEIKO;
		}
		else
		{
			mission_state = MISSION_SIPPAI;
		}
		return;
	}

	if (UtilInput::IsKeyPushedLineOne())
	{
		cnt_key_nikuman++;
	}
	time--;
}

void Mission::Mission13()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	if (time <= 0)
	{
		if (cnt_key_yoshitaro > cnt_key_nikuman && cnt_key_yoshitaro > cnt_key_noppo)
		{
			mission_state = MISSION_SEIKO;
		}
		else
		{
			mission_state = MISSION_SIPPAI;
		}
		return;
	}
	
	if (UtilInput::IsKeyPushedLineOne())
	{
		cnt_key_yoshitaro++;
	}
	time--;
}

void Mission::Mission14()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	if(time <= 0)
	{
		if(cnt_key_noppo > cnt_key_nikuman && cnt_key_noppo > cnt_key_yoshitaro)
		{
			mission_state = MISSION_SEIKO;
		}
		else
		{
			mission_state = MISSION_SIPPAI;
		}
		return;
	}
	
	if (UtilInput::IsKeyPushedLineThree())
	{
		cnt_key_noppo++;
	}
	time--;
}

void Mission::MissionControlD()
{
	switch(mission_no)
	{
	case MISSION_1:
		Mission1D();
		break;
	case MISSION_2:
		Mission2D();
		break;
	case MISSION_3:
		Mission3D();
		break;
	case MISSION_4:
		Mission4D();
		break;
	case MISSION_5:
		Mission5D();
		break;
	case MISSION_6:
		Mission6D();
		break;
	case MISSION_7:
		Mission7D();
		break;
	case MISSION_8:
		Mission8D();
		break;
	case MISSION_9:
		Mission9D();
		break;
	case MISSION_10:
		Mission10D();
		break;
	case MISSION_11:
		Mission11D();
		break;
	case MISSION_12:
		Mission12D();
		break;
	case MISSION_13:
		Mission13D();
		break;
	case MISSION_14:
		Mission14D();
		break;
	}
}

void Mission::Mission1D()	//�w10�b�ȓ���100��A�ł���I�I�x
{
	DrawNumT();
	DrawCombo();
}

void Mission::Mission2D()	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
{
	DrawNumT();
	DrawCombo();
}

void Mission::Mission3D()	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
{
	DrawNumT();
	DrawCombo();
}

void Mission::Mission4D()	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(125.f + 29.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission5D()	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(76.f + 28.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission6D()	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(118.f + 29.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission7D()	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(108.f + 28.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission8D()	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(131.f + 30.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission9D()	//�w�uNOPPOBOKUSIRIKOPUTA�v�Ɠ��͂���I�I�x
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < success_type_count;i++){
		vertex->DrawF(96.f + 29.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void Mission::Mission10D()	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(flag_time_cnt == 0){
		vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI);
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha_push_z,255,255,255);
		vertex->DrawF(400.f,450.f,R_Z_PUSH_START);
	}
	//DrawNumT();		//�f�o�b�O�p
}

void Mission::Mission11D()	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
{
	if(flag_time_cnt == 0){
		vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI);
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha_push_z,255,255,255);
		vertex->DrawF(400.f,450.f,R_Z_PUSH_START);
	}
	//DrawNumT();		//�f�o�b�O�p
}

void Mission::Mission12D()	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
{
	DrawNumT();
}

void Mission::Mission13D()	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
{
	DrawNumT();
}

void Mission::Mission14D()	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
{
	DrawNumT();
}

void Mission::FadeIn()
{
	if(alpha == MISSION_ALPHA_MAX){
		mission_state = MISSION_MIDDLE;
		return ;
	}
	if(alpha_count++ > 1){
		alpha += MISSION_ALPHA_INCREASE;
		if(alpha > MISSION_ALPHA_MAX){
			alpha = MISSION_ALPHA_MAX;
		}
		alpha_count = 0;
	}
}

void Mission::FadeOut()
{
	if(alpha == 0){
		if(mission_state == MISSION_SEIKO){
			mission_state = MISSION_OUGI;
		}
		else if(mission_state == MISSION_SIPPAI){
			mission_state = MISSION_NEGATIVE;
		}
		return ;
	}
	else if(alpha_count++ > 1){
		alpha -= MISSION_ALPHA_INCREASE + 5;
		if(alpha < 0) { alpha = 0; }
		alpha_count = 0;
	}
}

void Mission::MissionSelect()
{
	if(flag_init) { return ; }
	else{
		mission_no = rand()%100+1;
		//mission_no = 86;		//�f�o�b�O�p
		if(mission_no >=0 && mission_no <= MISSION_1PAR){
			mission_no = MISSION_1;
		}
		else if(mission_no > MISSION_1PAR && mission_no <= MISSION_2PAR){
			mission_no = MISSION_2;
		}
		else if(mission_no > MISSION_2PAR && mission_no <= MISSION_3PAR){
			mission_no = MISSION_3;
		}
		else if(mission_no > MISSION_3PAR && mission_no <= MISSION_4PAR){
			mission_no = MISSION_4;
		}
		else if(mission_no > MISSION_4PAR && mission_no <= MISSION_5PAR){
			mission_no = MISSION_5;
		}
		else if(mission_no > MISSION_5PAR && mission_no <= MISSION_6PAR){
			mission_no = MISSION_6;
		}
		else if(mission_no > MISSION_6PAR && mission_no <= MISSION_7PAR){
			mission_no = MISSION_7;
		}
		else if(mission_no > MISSION_7PAR && mission_no <= MISSION_8PAR){
			mission_no = MISSION_8;
		}
		else if(mission_no > MISSION_8PAR && mission_no <= MISSION_9PAR){
			mission_no = MISSION_9;
		}
		else if(mission_no > MISSION_9PAR && mission_no <= MISSION_10PAR){
			mission_no = MISSION_10;
		}
		else if(mission_no > MISSION_10PAR && mission_no <= MISSION_11PAR){
			mission_no = MISSION_11;
		}
		else if(mission_no > MISSION_11PAR && mission_no <= MISSION_12PAR){
			mission_no = MISSION_12;
			if(cnt_key_nikuman >= cnt_key_noppo && cnt_key_nikuman >= cnt_key_yoshitaro){
				mission_no = MISSION_1;
			}
		}
		else if(mission_no > MISSION_12PAR && mission_no <= MISSION_13PAR){
			mission_no = MISSION_13;
			if(cnt_key_yoshitaro >= cnt_key_nikuman && cnt_key_yoshitaro >= cnt_key_noppo){
				mission_no = MISSION_1;
			}
		}
		else if(mission_no > MISSION_13PAR && mission_no <= MISSION_14PAR){
			mission_no = MISSION_14;
			if(cnt_key_noppo >= cnt_key_nikuman && cnt_key_noppo >= cnt_key_yoshitaro){
				mission_no = MISSION_1;
			}
		}
		//mission_no = MISSION_11;		//�f�o�b�O�p
		flag_init = true;
	}
}

void Mission::DrawNumT()
{
	//�^�C��
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 0;i < 2;i++){
		int num = time;
		for(int j = 0;j < 2 - i;j++){
			if(j == 0){
				num = num / 60;
			}
			else{
				num = num / 10;
			}
		}
		vertex->DrawF(M_TIMENUM_X + 50.f * i,M_TIMENUM_Y,R_0_B + num%10);
	}
}

void Mission::DrawCombo()
{
	//�R���{
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 0;i < 3;i++){
		int num = key_cnt;
		for(int j = 1;j < 3 - i;j++){
			num = num / 10;
		}
		vertex->DrawF(M_COMBO_X + 50.f + 50.f * i,M_COMBO_Y,R_0_B + num%10);
	}
	vertex->DrawF(M_COMBO_X,M_COMBO_Y,R_COMBO);
}
