//---------------------------------------------
//
//      操作説明
//			作成者:	平野
//
//---------------------------------------------
#include "Tutorial.h"
#include "Library/DirectSound.h"

C_Tutorial::C_Tutorial(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	key		= new C_Control();

	keep_key_state = key_state = 0;

	flag_draw_state = TR_REFRESH;

	tutorial[TR_REFRESH].y = tutorial[TR_NORMAL].y = TR_Y;

	tutorial[TR_REFRESH].x = tutorial[TR_NORMAL].x  = TR_RIGHT_X;

	alpha=0;
	alpha_count=0;
	fade_flag=TR_FADE_IN;

	scene_change = true;
}

C_Tutorial::~C_Tutorial(void)
{
}

void C_Tutorial::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont* apFont, int score)
{
	C_SceneManage::InitScene(apDev, apFont, score);

	texture->LoadTextureData("Data\\TextureData\\Tutorial.txt",apDev);		//絵の読み込み
	vertex->LoadRect("Data\\RectData\\Tutorial.txt");
}

bool C_Tutorial::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Tutorial::ControlScene()
{
	GetDirectSound()->SoundPlay(false, S_BGM_TITLE);

	KeyControl();

	DrawPosi();
}

void C_Tutorial::DrawScene()
{
	vertex->SetTextureData(texture->GetTextureData(T_TUTORIAL1),pDevice);

	//vertex->SetColor(alpha,255,255,255);

	vertex->DrawF(tutorial[TR_REFRESH].x,tutorial[TR_REFRESH].y,R_TUTORIAL1);

	vertex->SetTextureData(texture->GetTextureData(T_TUTORIAL2),pDevice);

	//vertex->SetColor(alpha,255,255,255);

	vertex->DrawF(tutorial[TR_NORMAL].x,tutorial[TR_NORMAL].y,R_TUTORIAL2);
}

int C_Tutorial::EndScene()
{
	ChangeScene(TITLE);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}

void C_Tutorial::FadeControl()
{
	switch(fade_flag)
	{
		case TR_FADE_IN:
			FadeIn();
			if(alpha == 255) fade_flag=TR_USUALLY;
			break;
		case TR_USUALLY:
			break;
		case TR_FADE_OUT:
			FadeOut();
			if(alpha == 0)	//シーン移行、ゲームスタート
			break;
	}
}

void C_Tutorial::FadeIn()
{
	if(alpha_count++>1)
	{
		alpha += 5;
		alpha_count = 0;
	}
	if(alpha > 255)
	{
		alpha = 255;
		alpha_count = 0;
	}
}

void C_Tutorial::FadeOut()
{
	if(alpha_count++>1)
	{
		alpha -= 5;
		alpha_count = 0;
	}
	if(alpha < 0)
	{
		alpha = 0;
		alpha_count = 0;
	}
}

void C_Tutorial::KeyControl()
{
	key_state = key->KeyCheck();

	if(key_state == KEY_Z){		//Zが押されたら
		scene_change = false;
	}
	if(key_state == KEY_LEFT){	//←が押されたら
		GetDirectSound()->SoundPlay(false, S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_REFRESH;
		}
		else if(flag_draw_state == TR_END){
			flag_draw_state = TR_NORMAL;
		}
	}
	if(key_state == KEY_RIGHT){	//→が押されたら
		GetDirectSound()->SoundPlay(false, S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_REFRESH){
			flag_draw_state = TR_NORMAL;
		}
		else if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_END;
		}
	}
	if(key_state != 0){
		keep_key_state = key_state;
	}
}

void C_Tutorial::DrawPosi()
{
	if(flag_draw_state == TR_REFRESH){
		if(keep_key_state == KEY_LEFT){
			if(tutorial[TR_REFRESH].x != TR_CENTER_X){
				tutorial[TR_REFRESH].x += 10.f;
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else{
			if(tutorial[TR_REFRESH].x != TR_CENTER_X){
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_NORMAL){
		if(keep_key_state == KEY_LEFT){
			if(tutorial[TR_NORMAL].x != TR_CENTER_X){
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else{
			if(tutorial[TR_NORMAL].x != TR_CENTER_X){
				tutorial[TR_NORMAL].x -= 10.f;
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_END){
		if(tutorial[TR_NORMAL].x != TR_LEFT_X){
			tutorial[TR_NORMAL].x -= 10.f;
		}
		else{
			scene_change = false;
		}
	}
}