//---------------------------------------------
//
//      �^�C�g��
//			�쐬��:	����
//
//---------------------------------------------
#include "Title.h"
#include "Library/Sound/DirectSound.h"

C_Title::C_Title(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	key		= new C_Control();

	cursor_posi.x = CURSOR_X;
	cursor_posi.y = CURSOR_Y;

	title_posi.x = TITLE_X;
	title_posi.y = -100.f;

	time_count = 0;	//���S�̃^�C���J�E���g

	alpha = 0;	//�A���t�@�l

	alpha_z = 0;

	draw_scene_change = DRAW_Z_PUSH;

	flag_select = G_START;

	start_flag = false;

	flag_fade = TITLE_FADE_IN;

	alpha_count = 0;

	scene_change = true;

	flag_scene_change = 0;

	key_state = 0;

	anime_cursor = 0;

	flag_fade_in = false;

	flag_z = false;

	flag_draw = 0;

	cnt_move = 0;
}

C_Title::~C_Title(void)
{
}

void C_Title::InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, int score)
{
	C_SceneManage::InitScene(apDev, apFont, score);

	texture->LoadTextureData("Data\\TextureData\\title.txt",apDev);		//�G�̓ǂݍ���
	vertex->LoadRect("Data\\RectData\\title.txt");
}

bool C_Title::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Title::ControlScene()
{
	GetDirectSound()->SoundPlay(true,S_BGM_TITLE);

	FadeControl();
	PosiDrawControl();
	KeyControl();

	if(alpha == TITLE_MAX_ALPHA) { time_count++; }

	if(alpha == 0){
		if(flag_fade == TITLE_FADE_OUT0){
			scene_change = false;
			flag_scene_change = LOGO;
		}
		else if(flag_fade == TITLE_FADE_OUT1){
			scene_change = false;
			flag_scene_change = RANKING;
		}
		else if(flag_fade == TITLE_FADE_OUT2){
			PostQuitMessage(0);
		}
	}

	if(time_count%16 == 15){
		anime_cursor++;
	}

	if(time_count == BACK_SCENE_TIME){
		flag_fade = TITLE_FADE_OUT0;
	}

	if(flag_fade == TITLE_FADE_OUT0 && time_count < BACK_SCENE_TIME){
		flag_fade = TITLE_FADE_IN;
	}
}

void C_Title::DrawScene()
{
	vertex->SetTextureData(texture->GetTextureData(T_TITLE_BG),pDevice);

	if(alpha - 55 < 0){
		vertex->SetColor(0,255,255,255);
	}
	else{
		vertex->SetColor(alpha - 55,255,255,255);
	}

	vertex->DrawF(TITLE_BG_X,TITLE_BG_Y,R_TITLE_BG);

	vertex->SetTextureData(texture->GetTextureData(T_FONT),pDevice);

	vertex->SetColor(alpha,255,255,255);
	vertex->DrawF(title_posi.x,title_posi.y,R_TITLE);
	
	if(draw_scene_change == DRAW_Z_PUSH){
		vertex->SetColor(alpha - alpha_z,255,255,255);
		vertex->DrawF(ZPUSH_X,ZPUSH_Y,R_ZPUSH);
	}
	else if(draw_scene_change == DRAW_MENU){
		vertex->SetColor(alpha,255,255,255);
		vertex->DrawF(START_X,START_Y,R_START);
		vertex->DrawF(RANKING_X,RANKING_Y,R_RANKING);
		vertex->DrawF(END_X,END_Y,R_END);
	}
	else{
		//���[�h�I��(��������E�́[�܂�E�������)
		vertex->SetColor(alpha,255,255,255);
		vertex->DrawF(START_X,START_Y,R_REFRESH);
		vertex->DrawF(RANKING_X,RANKING_Y,R_NORMAL);
		vertex->DrawF(END_X,END_Y,R_TUTORIAL_T);
	}
	
	//�J�[�\��
	vertex->SetColor(alpha,255,255,255);
	if(draw_scene_change != DRAW_Z_PUSH){
		vertex->DrawF(cursor_posi.x,cursor_posi.y,R_CURSOR1+anime_cursor%2);
		vertex->DrawF(cursor_posi.x + CURSOR2_X,cursor_posi.y,R_CURSOR1+anime_cursor%2);
	}
}

int C_Title::EndScene()
{
	ChangeScene(flag_scene_change);

	GetDirectSound()->SoundStop(true,S_BGM_TITLE);

	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}

void C_Title::PosiDrawControl()
{
	//�J�[�\���ʒu���v�Z
	cursor_posi.y = CURSOR_Y + CURSOR_Y_REMOVE * flag_select;

	//�^�C�g���ʒu���v�Z
	if(flag_draw == 7) { return ; }
	if(flag_draw%2 == 0){
		if(title_posi.y < TITLE_Y){
			title_posi.y += 5.f;
		}
		else{
			flag_draw++;
		}
	}
	else if(flag_draw%2 == 1){
		title_posi.y -= 5.f;
		if(title_posi.y == 70.f + 20.f * cnt_move){
			flag_draw++;
			cnt_move++;
		}
	}
}

void C_Title::FadeControl()
{
	switch(flag_fade)
	{
		case TITLE_FADE_IN:
			FadeIn();
			break;
		case TITLE_FADE_OUT0:
		case TITLE_FADE_OUT1:
		case TITLE_FADE_OUT2:
			FadeOut();
			break;
	}
}

void C_Title::FadeIn()
{
	if(flag_fade_in){
		if(!flag_z){
			alpha_z += 5;
			if(alpha_z == 200){
				flag_z = true;
			}
		}
		else{
			alpha_z -= 5;
			if(alpha_z == 0){
				flag_z = false;
			}
		}
		return ; 
	}
	else if(alpha_count++ > 1){
		alpha += TITLE_ALPHA_INCREASE;
		if(alpha > TITLE_MAX_ALPHA){
			alpha = TITLE_MAX_ALPHA;
			flag_fade_in = true;
		}
		alpha_count = 0;
	}
}

void C_Title::FadeOut()
{
	if(alpha == 0) { return ; }
	else if(alpha_count++ > 1){
		alpha -= TITLE_ALPHA_INCREASE;
		if(alpha < 0) { alpha = 0; }
		alpha_count = 0;
	}
}

void C_Title::KeyControl()
{
	key_state = key->KeyCheck();

	//�߂�����㉺������Ă���a���ɂȂ��悤��
	if(GetDirectSound()->IsPlaySound(S_SE_CURSOR_MOVE)){
		if(key_state == KEY_UP || key_state == KEY_DOWN){
			GetDirectSound()->SoundStop(true,S_SE_CURSOR_MOVE);
		}
	}

	if(key_state == KEY_Z){
		GetDirectSound()->SoundPlay(false,S_SE_OK);
		if(draw_scene_change == DRAW_Z_PUSH){		//PUSH_Z���\������Ă��鎞�ɂy�L�[�������ꂽ��
			draw_scene_change = DRAW_MENU;
		}
		else if(draw_scene_change == DRAW_MENU){	//���j���[���\������Ă��鎞�ɂy�L�[�������ꂽ��
			if(flag_select == G_START){
				draw_scene_change = DRAW_GAME_MENU;
				flag_select = 0;
			}
			else if(flag_select == G_RANKING){
				flag_fade = TITLE_FADE_OUT1;
			}
			else{
				flag_fade = TITLE_FADE_OUT2;
			}
		}
		else{										//�Q�[�����j���[���\������Ă��鎞�ɂy�L�[�������ꂽ��
			if(flag_select == G_CLEARLY){
				//�������胂�[�h���J�n������悤�Ƀt���O��ς���
				flag_scene_change = GAME_REFRESH;
			}
			else if(flag_select == G_NORMAL){
				//�́[�܂郂�[�h���J�n������悤�Ƀt���O��ς���
				flag_scene_change = GAME_NORMAL;
			}
			else{
				flag_scene_change = TUTORIAL;
			}
			scene_change = false;
		}
		time_count = 0;
	}

	if(key_state == KEY_UP){		//���L�[�������ꂽ��
		if(draw_scene_change != DRAW_Z_PUSH) GetDirectSound()->SoundPlay(false,S_SE_CURSOR_MOVE);
		flag_select--;
		if(draw_scene_change == DRAW_MENU){
			if(flag_select < G_START){
				flag_select = G_END;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU){
			if(flag_select < G_CLEARLY){
				flag_select = G_TUTORIAL;
			}
		}
		else{
			flag_select++;
		}
		time_count=0;
	}

	if(key_state == KEY_DOWN){	//���L�[�������ꂽ��
		if(draw_scene_change != DRAW_Z_PUSH) GetDirectSound()->SoundPlay(false,S_SE_CURSOR_MOVE);
		flag_select++;
		if(draw_scene_change == DRAW_MENU){
			if(flag_select > G_END){
				flag_select = G_START;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU){
			if(flag_select > G_TUTORIAL){
				flag_select = G_CLEARLY;
			}
		}
		else{
			flag_select--;
		}
		time_count=0;
	}

	if(key_state == KEY_X){
		GetDirectSound()->SoundPlay(false, S_CANCEL);
		if(draw_scene_change == DRAW_MENU){
			draw_scene_change = DRAW_Z_PUSH;
			flag_select = G_START;
		}
		else if(draw_scene_change == DRAW_GAME_MENU){
			draw_scene_change = DRAW_MENU;
			flag_select = G_CLEARLY;
		}
		time_count=0;
	}
}
