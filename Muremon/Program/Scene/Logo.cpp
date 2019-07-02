//---------------------------------------------
//
//      ���S
//			�쐬��:	����
//
//---------------------------------------------
#include "Logo.h"

C_Logo::C_Logo(void)
{
	time_count = 0;
	alpha = 0;
	mIsSceneChange = true;
}

C_Logo::~C_Logo(void)
{
}

void C_Logo::InitScene()
{
	mTexture->LoadTextureData("Data\\TextureData\\logo.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\logo.txt");
}

bool C_Logo::ControlScene()
{
	FadeControl();
	return mIsSceneChange;
}

void C_Logo::DrawScene()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_LOGO), mDevice);
	mVertex->SetColor(alpha,255,255,255);
	mVertex->DrawF(400.f,300.f,R_LOGO);
}

int C_Logo::EndScene()
{
	ChangeScene(cSceneName_Title);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void C_Logo::FadeControl()
{
	time_count++;
	
	if(time_count > 0 && time_count < MAXALPHATIME)	
	{
		alpha += 5;
		if(alpha > 255)
		{
			alpha=255;
		}
	}

	else if(time_count>= MAXALPHATIME && time_count < ALPHADWINDLITIME)	alpha=255;

	else if(time_count >= ALPHADWINDLITIME)
	{
		alpha -= 5;

		if(alpha < 0)	
		{
			alpha = 0;
		}
		if(alpha == 0) mIsSceneChange = false;/*scene_flag = TITLE;*///�^�C�g����ʂ�
	}
}

