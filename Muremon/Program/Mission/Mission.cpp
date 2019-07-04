#include "Mission.h"
#include "Library/Sound/DirectSound.h"
#include "Program/Util/UtilInput.h"

C_Mission::C_Mission(C_Texture* m_texture,C_Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev)
{
	texture = m_texture;
	vertex	= m_vertex;
	pDevice = apDev;

	cnt_key_nikuman = 0;	//にくまんの押されたキーの数をカウント

	cnt_key_yoshitaro = 0;	//吉たろうの押されたキーの数をカウント

	cnt_key_noppo = 0;		//のっぽの押されたキーの数をカウント

	mission_no	= 0;
	key_state	= 0;
	time		= TEN_SECOND;
	key_cnt		= 0;
	type_key	= 1;
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

C_Mission::~C_Mission(void)
{
}

void C_Mission::Init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo)
{
	mission_no	= 0;
	key_state	= 0;
	time		= TEN_SECOND;
	key_cnt		= 0;
	type_key	= 1;
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

	cnt_key_nikuman		= cnt_nikuman;		//にくまんの押されたキーの数をカウント

	cnt_key_yoshitaro	= cnt_yoshitaro;	//吉たろうの押されたキーの数をカウント

	cnt_key_noppo		= cnt_noppo;		//のっぽの押されたキーの数をカウント
}

int C_Mission::Control()
{
	if(mission_state == MISSION_START){
		MissionSelect();
		//位置を計算
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
			GetDirectSound()->SoundPlayOnce(S_OSIRASE);
			flag_sound = false;
		}
		MissionControl();
	}
	else{
		if(mission_state == MISSION_SEIKO){
			if(flag_sound2){
				GetDirectSound()->SoundPlayOnce(S_M_CLEAR);
				flag_sound = false;
			}
		}
		else if(mission_state == MISSION_SIPPAI){
			if(flag_sound2){
				GetDirectSound()->SoundPlayOnce(S_M_OVER);
				flag_sound2 = false;
			}
		}
		FadeOut();
	}
	return mission_state;
}

void C_Mission::Draw()
{
	vertex->SetTextureData(texture->GetTextureData(T_MISSION),pDevice);

	if(mission_state != MISSION_START){
		vertex->SetColor(alpha,255,255,255);
	}

	vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI + mission_state);	//みっしょん発生

	vertex->SetColor(alpha,255,255,255);
	vertex->DrawF(MISSION_OSIRASE_X,MISSION_OSIRASE_Y,R_MISSION_OSIRASE);	//みっしょんお知らせ枠
	vertex->DrawF(MISSION_OSIRASE_X,MISSION_OSIRASE_Y,R_MISSION_1 + mission_no);	//みっしょん

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

void C_Mission::MissionControl()
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

void C_Mission::Mission1()	//『10秒以内に100回連打せよ！！』
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

void C_Mission::Mission2()	//『10秒間でちょうど50回連打せよ！！』
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

void C_Mission::Mission3()	//『10秒間でちょうど100回連打せよ！！』
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

void C_Mission::Mission4()	//『「NIKUMANTOTUGEKI」と入力せよ！！』
{
	if(time <= 0)
	{
		if(type_key == MISSION4_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(type_key < MISSION4_FONT_NUM){
		if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
		{
			if(type_key == 1 || type_key == 7)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 2 || type_key == 15)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_K))
		{
			if(type_key == 3 || type_key == 14)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_U))
		{
			if(type_key == 4 || type_key == 11)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_M))
		{
			if(type_key == 5)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_A))
		{
			if(type_key == 6)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 8 || type_key == 10)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_O))
		{
			if(type_key == 9)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_G))
		{
			if(type_key == 12)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_E))
		{
			if(type_key == 13)
			{
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission5()	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
{
	if (time <= 0)
	{
		if(type_key == MISSION5_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(type_key < MISSION5_FONT_NUM)
	{
		if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
		{
			if(type_key == 1 || type_key == 7 || type_key == 9)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 2 || type_key == 8 || type_key == 13)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_K))
		{
			if(type_key == 3 || type_key == 12 || type_key == 16 || type_key == 17)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_U))
		{
			if(type_key == 4 || type_key == 20 || type_key == 22)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_M))
		{
			if(type_key == 5)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_A))
		{
			if(type_key == 6 || type_key == 15 || type_key == 18)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_S))
		{
			if(type_key == 10)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_E))
		{
			if(type_key == 11){
				type_key++;
			}
			else{
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_R))
		{
			if(type_key == 14)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_J))
		{
			if(type_key == 19){
				type_key++;
			}
			else{
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 21)
			{
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission6()	//『「YOSITAROHIPATACK」と入力せよ！！』
{
	if (time <= 0)
	{
		if(type_key == MISSION6_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(type_key < MISSION6_FONT_NUM)
	{
		if (UtilInput::IsKeyPushed(UtilInput::cKey_Y))
		{
			if(type_key == 1)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_O))
		{
			if(type_key == 2 || type_key == 8)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_S))
		{
			if(type_key == 3)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 4 || type_key == 10)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 5 || type_key == 13)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_A))
		{
			if(type_key == 6 || type_key == 12 || type_key == 14)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_R))
		{
			if(type_key == 7)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_H))
		{
			if(type_key == 9)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_P))
		{
			if(type_key == 11)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_C))
		{
			if(type_key == 15)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_K))
		{
			if(type_key == 16)
			{
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission7()	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
{
	if (time <= 0)
	{
		if (type_key == MISSION7_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(type_key < MISSION7_FONT_NUM)
	{
		if (UtilInput::IsKeyPushed(UtilInput::cKey_Y))
		{
			if(type_key == 1)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_O))
		{
			if(type_key == 2 || type_key == 8 || type_key == 16 || type_key == 17)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_S))
		{
			if(type_key == 3 || type_key == 11 || type_key == 14)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 4)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 5 || type_key == 18)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_A))
		{
			if(type_key == 6)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_R))
		{
			if(type_key == 7)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_H))
		{
			if(type_key == 9 || type_key == 15)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_U))
		{
			if(type_key == 10){
				type_key++;
			}
			else{
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_E))
		{
			if(type_key == 12)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
		{
			if(type_key == 13)
			{
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission8()	//『「NOPPOKOKEPPETI」と入力せよ！！』
{
	if (time <= 0)
	{
		if (type_key == MISSION8_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}
	
	if(type_key < MISSION8_FONT_NUM)
	{
		if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
		{
			if(type_key == 1)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_O))
		{
			if(type_key == 2 || type_key == 5 || type_key == 7)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_P))
		{
			if(type_key == 3 || type_key == 4 || type_key == 10 || type_key == 11)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_K))
		{
			if(type_key == 6 || type_key == 8){
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_E))
		{
			if(type_key == 9 || type_key == 12)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 13){
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 14){
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission9()	//『「NOPPOBOKUSIRIKOPUTA」と入力せよ！！』
{
	if (time <= 0)
	{
		if (type_key == MISSION9_FONT_NUM)	mission_state = MISSION_SEIKO;
		else								mission_state = MISSION_SIPPAI;
		return;
	}

	if(type_key < MISSION9_FONT_NUM)
	{
		if (UtilInput::IsKeyPushed(UtilInput::cKey_N))
		{
			if(type_key == 1)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_O))
		{
			if(type_key == 2 || type_key == 5 || type_key == 7 || type_key == 15)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_P))
		{
			if(type_key == 3 || type_key == 4 || type_key == 16)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_B))
		{
			if(type_key == 6)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_K))
		{
			if(type_key == 8 || type_key == 14)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_U))
		{
			if(type_key == 9 || type_key == 17)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_S))
		{
			if(type_key == 10)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_I))
		{
			if(type_key == 11 || type_key == 13)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_R))
		{
			if(type_key == 12)
			{
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_T))
		{
			if(type_key == 18){
				type_key++;
			}
		}
		else if (UtilInput::IsKeyPushed(UtilInput::cKey_A))
		{
			if(type_key == 19)
			{
				type_key++;
			}
		}
	}
	time--;
}

void C_Mission::Mission10()	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
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

void C_Mission::Mission11()	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
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

void C_Mission::Mission12()	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
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

void C_Mission::Mission13()	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
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

void C_Mission::Mission14()	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』
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

void C_Mission::MissionControlD()
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

void C_Mission::Mission1D()	//『10秒以内に100回連打せよ！！』
{
	DrawNumT();
	DrawCombo();
}

void C_Mission::Mission2D()	//『10秒間でちょうど50回連打せよ！！』
{
	DrawNumT();
	DrawCombo();
}

void C_Mission::Mission3D()	//『10秒間でちょうど100回連打せよ！！』
{
	DrawNumT();
	DrawCombo();
}

void C_Mission::Mission4D()	//『「NIKUMANTOTUGEKI」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(125.f + 29.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission5D()	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(76.f + 28.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission6D()	//『「YOSITAROHIPATACK」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(118.f + 29.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission7D()	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(108.f + 28.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission8D()	//『「NOPPOKOKEPPETI」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(131.f + 30.f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission9D()	//『「NOPPOBOKUSIRIKOPUTA」と入力せよ！！』
{
	DrawNumT();
	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
	for(int i = 1;i < type_key;i++){
		vertex->DrawF(96.f + 29.5f * (i - 1),278.f,R_F_NIKUMAN);
	}
}

void C_Mission::Mission10D()	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
{
	if(flag_time_cnt == 0){
		vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI);
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha_push_z,255,255,255);
		vertex->DrawF(400.f,450.f,R_Z_PUSH_START);
	}
	//DrawNumT();		//デバッグ用
}

void C_Mission::Mission11D()	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
{
	if(flag_time_cnt == 0){
		vertex->DrawF(mission_start.x,mission_start.y,R_MISSION_HASSEI);
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha_push_z,255,255,255);
		vertex->DrawF(400.f,450.f,R_Z_PUSH_START);
	}
	//DrawNumT();		//デバッグ用
}

void C_Mission::Mission12D()	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
{
	DrawNumT();
}

void C_Mission::Mission13D()	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
{
	DrawNumT();
}

void C_Mission::Mission14D()	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』
{
	DrawNumT();
}

void C_Mission::FadeIn()
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

void C_Mission::FadeOut()
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

void C_Mission::MissionSelect()
{
	if(flag_init) { return ; }
	else{
		mission_no = rand()%100+1;
		//mission_no = 86;		//デバッグ用
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
		//mission_no = MISSION_11;		//デバッグ用
		flag_init = true;
	}
}

void C_Mission::DrawNumT()
{
	//タイム
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

void C_Mission::DrawCombo()
{
	//コンボ
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
