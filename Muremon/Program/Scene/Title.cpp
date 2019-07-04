//---------------------------------------------
//
//      �^�C�g��
//			�쐬��:	����
//
//---------------------------------------------
#include "Title.h"
#include "Library/Sound/DirectSound.h"
#include "Program/Util/UtilInput.h"

SceneTitle::SceneTitle(void)
{
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

	mIsSceneChange = true;

	flag_scene_change = 0;

	anime_cursor = 0;

	flag_fade_in = false;

	flag_z = false;

	flag_draw = 0;

	cnt_move = 0;
}

SceneTitle::~SceneTitle(void)
{
}

void SceneTitle::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\title.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\title.txt");
}

bool SceneTitle::Update()
{
	GetDirectSound()->SoundPlayLoop(S_BGM_TITLE);

	FadeControl();
	PosiDrawControl();
	KeyControl();

	if(alpha == TITLE_MAX_ALPHA) { time_count++; }

	if(alpha == 0){
		if(flag_fade == TITLE_FADE_OUT0){
			mIsSceneChange = false;
			flag_scene_change = cSceneName_Logo;
		}
		else if(flag_fade == TITLE_FADE_OUT1){
			mIsSceneChange = false;
			flag_scene_change = cSceneName_Ranking;
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

	return mIsSceneChange;
}

void SceneTitle::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TITLE_BG), mDevice);

	if(alpha - 55 < 0){
		mVertex->SetColor(0,255,255,255);
	}
	else{
		mVertex->SetColor(alpha - 55,255,255,255);
	}

	mVertex->DrawF(TITLE_BG_X,TITLE_BG_Y,R_TITLE_BG);

	mVertex->SetTextureData(mTexture->GetTextureData(T_FONT), mDevice);

	mVertex->SetColor(alpha,255,255,255);
	mVertex->DrawF(title_posi.x,title_posi.y,R_TITLE);
	
	if(draw_scene_change == DRAW_Z_PUSH){
		mVertex->SetColor(alpha - alpha_z,255,255,255);
		mVertex->DrawF(ZPUSH_X,ZPUSH_Y,R_ZPUSH);
	}
	else if(draw_scene_change == DRAW_MENU){
		mVertex->SetColor(alpha,255,255,255);
		mVertex->DrawF(START_X,START_Y,R_START);
		mVertex->DrawF(RANKING_X,RANKING_Y,R_RANKING);
		mVertex->DrawF(END_X,END_Y,R_END);
	}
	else{
		//���[�h�I��(��������E�́[�܂�E�������)
		mVertex->SetColor(alpha,255,255,255);
		mVertex->DrawF(START_X,START_Y,R_REFRESH);
		mVertex->DrawF(RANKING_X,RANKING_Y,R_NORMAL);
		mVertex->DrawF(END_X,END_Y,R_TUTORIAL_T);
	}
	
	//�J�[�\��
	mVertex->SetColor(alpha,255,255,255);
	if(draw_scene_change != DRAW_Z_PUSH){
		mVertex->DrawF(cursor_posi.x,cursor_posi.y,R_CURSOR1+anime_cursor%2);
		mVertex->DrawF(cursor_posi.x + CURSOR2_X,cursor_posi.y,R_CURSOR1+anime_cursor%2);
	}
}

int SceneTitle::End()
{
	ChangeScene(flag_scene_change);

	GetDirectSound()->SoundPouse(S_BGM_TITLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTitle::PosiDrawControl()
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

void SceneTitle::FadeControl()
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

void SceneTitle::FadeIn()
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

void SceneTitle::FadeOut()
{
	if(alpha == 0) { return ; }
	else if(alpha_count++ > 1){
		alpha -= TITLE_ALPHA_INCREASE;
		if(alpha < 0) { alpha = 0; }
		alpha_count = 0;
	}
}

void SceneTitle::KeyControl()
{
	// �߂�����㉺������Ă���a���ɂȂ��悤��
	if(GetDirectSound()->IsPlaySound(S_SE_CURSOR_MOVE))
	{
		if(UtilInput::IsKeyDown(DIK_UP) == KEY_UP ||
			UtilInput::IsKeyDown(DIK_DOWN))
		{
			GetDirectSound()->SoundStop(S_SE_CURSOR_MOVE);
		}
	}

	if(UtilInput::IsKeyPushed(DIK_Z))
	{
		GetDirectSound()->SoundPlayOnce(S_SE_OK);
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
				flag_scene_change = cSceneName_GameRefresh;
			}
			else if(flag_select == G_NORMAL){
				//�́[�܂郂�[�h���J�n������悤�Ƀt���O��ς���
				flag_scene_change = cSceneName_GameNormal;
			}
			else{
				flag_scene_change = cSceneName_Tutorial;
			}
			mIsSceneChange = false;
		}
		time_count = 0;
	}

	// ���L�[�������ꂽ��
	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select--;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select < G_START)
			{
				flag_select = G_END;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select < G_CLEARLY)
			{
				flag_select = G_TUTORIAL;
			}
		}
		else{
			flag_select++;
		}
		time_count=0;
	}

	// ���L�[�������ꂽ��
	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select++;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select > G_END)
			{
				flag_select = G_START;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select > G_TUTORIAL)
			{
				flag_select = G_CLEARLY;
			}
		}
		else{
			flag_select--;
		}
		time_count=0;
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		GetDirectSound()->SoundPlayOnce(S_CANCEL);

		if(draw_scene_change == DRAW_MENU)
		{
			draw_scene_change = DRAW_Z_PUSH;
			flag_select = G_START;
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			draw_scene_change = DRAW_MENU;
			flag_select = G_CLEARLY;
		}
		time_count=0;
	}
}
