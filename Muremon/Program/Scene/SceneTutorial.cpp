//---------------------------------------------
//
//      �������
//			�쐬��:	����
//
//---------------------------------------------
#include "SceneTutorial.h"
#include "Library/Sound/DirectSound.h"
#include "Program/Util/UtilInput.h"

SceneTutorial::SceneTutorial(void)
{
	flag_draw_state = TR_REFRESH;
	slide_state = 0;

	tutorial[TR_REFRESH].y = tutorial[TR_NORMAL].y = TR_Y;

	tutorial[TR_REFRESH].x = tutorial[TR_NORMAL].x  = TR_RIGHT_X;

	alpha=0;
	alpha_count=0;
	fade_flag=TR_FADE_IN;

	mIsSceneChange = true;
}

SceneTutorial::~SceneTutorial(void)
{
}

void SceneTutorial::ImpleInit()
{
	mTexture->LoadTextureData("Data\\TextureData\\Tutorial.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\Tutorial.txt");
}

bool SceneTutorial::Update()
{
	GetDirectSound()->SoundPlayOnce(S_BGM_TITLE);

	KeyControl();

	DrawPosi();

	return mIsSceneChange;
}

void SceneTutorial::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TUTORIAL1), mDevice);

	//mVertex->SetColor(alpha,255,255,255);

	mVertex->DrawF(tutorial[TR_REFRESH].x,tutorial[TR_REFRESH].y,R_TUTORIAL1);

	mVertex->SetTextureData(mTexture->GetTextureData(T_TUTORIAL2), mDevice);

	//mVertex->SetColor(alpha,255,255,255);

	mVertex->DrawF(tutorial[TR_NORMAL].x,tutorial[TR_NORMAL].y,R_TUTORIAL2);
}

int SceneTutorial::End()
{
	ChangeScene(cSceneName_Title);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTutorial::FadeControl()
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
			if(alpha == 0)	//�V�[���ڍs�A�Q�[���X�^�[�g
			break;
	}
}

void SceneTutorial::FadeIn()
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

void SceneTutorial::FadeOut()
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

void SceneTutorial::KeyControl()
{
	if (UtilInput::IsKeyPushed(DIK_Z))
	{
		mIsSceneChange = false;
	}
	else if (UtilInput::IsKeyPushed(DIK_LEFT))
	{
		GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_REFRESH;
		}
		else if(flag_draw_state == TR_END){
			flag_draw_state = TR_NORMAL;
		}
		slide_state = 1;
	}
	else if (UtilInput::IsKeyPushed(DIK_RIGHT))
	{
		GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_REFRESH){
			flag_draw_state = TR_NORMAL;
		}
		else if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_END;
		}
		slide_state = 2;
	}
}

void SceneTutorial::DrawPosi()
{
	if(flag_draw_state == TR_REFRESH)
	{
		if (slide_state == 1)
		{
			if(tutorial[TR_REFRESH].x != TR_CENTER_X)
			{
				tutorial[TR_REFRESH].x += 10.f;
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_REFRESH].x != TR_CENTER_X){
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_NORMAL)
	{
		if (slide_state == 1)
		{
			if(tutorial[TR_NORMAL].x != TR_CENTER_X)
			{
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_NORMAL].x != TR_CENTER_X)
			{
				tutorial[TR_NORMAL].x -= 10.f;
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_END)
	{
		if(tutorial[TR_NORMAL].x != TR_LEFT_X)
		{
			tutorial[TR_NORMAL].x -= 10.f;
		}
		else{
			mIsSceneChange = false;
		}
	}
}