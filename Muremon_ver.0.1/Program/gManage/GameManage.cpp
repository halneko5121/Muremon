//---------------------------------------------
//
//      �Q�[���S�̂̊Ǘ����s��
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "GameManage.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�Q�[���Ŏg�������o�̏�����
//      ����  �F�Ȃ�
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_GameMain::InitGameMain(void)
{
    //�V��������
	wind	= new C_Window;
	gra		= new C_DGraphics;
    font    = new C_DFont;
	scene	= new C_Logo();

	//fps		= new CFps;
	//mapread = new MapRead;
	sou		= new C_DSound;
}

//////////////////////////////////////////////////////////
//
//      �����@�F���C���֐�
//      ����  �FHINSTANCE   hInstance   �C���X�^���X�n���h��
//              HINSTANCE   hPrevInst   �g�p���Ă��Ȃ�
//              LPSTR       lpCmdLine   �g�p���Ă��Ȃ�
//              int         nShowCmd    �g�p���Ă��Ȃ�
//      �߂�l�Fint         ���b�Z�[�W���[�v��Ԃ�
//
//////////////////////////////////////////////////////////
int WINAPI C_GameMain::WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
    //����
    InitGameMain();
	//�E�B���h�E�������֐�
	wind->InitWindow(hInstance);

	//DirectGraphics������
	if(FAILED(gra->InitDGraphics(wind,wind->GetHwnd(),800,600)))
	{
		MessageBox(NULL,TEXT("DirectGraphics�̏������Ɏ��s"),NULL,MB_OK);
		return 0;
	}
    //DirectFont������
	if(FAILED(font->InitDFont(gra->GetDevice())))
	{
		MessageBox(NULL,TEXT("DirectFont�̏������Ɏ��s"),NULL,MB_OK);
		return 0;
	}

//	fps->SetHwnd(wind->GetHwnd());

	//DirectSound������
	if(FAILED(sou->InitDSound(wind->GetHwnd())))
	{
		MessageBox(NULL,TEXT("DirectSound�̏������Ɏ��s"),NULL,MB_OK);
		return 0;
	}

	srand((unsigned int)time(NULL));


	return MsgLoop();
}
	
//////////////////////////////////////////////////////////
//
//      �����@�F�Q�[�������[�v�֐�
//      ����  �F�Ȃ�
//      �߂�l�Fint     ���b�Z�[�W
//
//////////////////////////////////////////////////////////
int C_GameMain::MsgLoop(void)
{
	MSG msg;

	int cnt = 0;

	background = D3DCOLOR_XRGB(0x00,0x00,0x00);

	//������
	ZeroMemory(&msg , sizeof(msg));

	gra->SetRender();	//�`��ݒ�

    scene->InitScene(gra->GetDevice(),/*input,*/font, /*mapread,*/ sou,0);

	sou->LoadSoundData("Data\\sound_data.txt");

	srand((unsigned int)time(NULL));

//	static int fps_count = 0; 
//	char str_fps[80];

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg , NULL , 0 , 0 , PM_REMOVE))
		{
			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ύX
			TranslateMessage(&msg);

			//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗐M
			DispatchMessage(&msg);
		}
		else
		{
			static DWORD oldTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			if(nowTime - oldTime >= 1000/60)
			{
				//1�b������
//				fps_count++;


				gra->RenderStart(background);
				//fps->FpsCount();
				if(!scene->RunScene())
				{
					score = scene->EndScene();								//�V�[���I��
					if(scene->GetSceneID() == TITLE) background = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);	//���S���I�������N���A���̐F�𔒂ɂ���
					if(scene->GetSceneID() == PROLOGUE) background = D3DCOLOR_XRGB(0x00,0x00,0x00);	//�^�C�g�����I�������N���A���̐F�����ɂ���
					ControlGame();										//�V�[���؂�ւ�
					//scene->InitScene(gra->GetDevice() , /*input ,*/ font, /*mapread,*/ sou);	//�V�[��������
				}

//				wsprintf(str_fps,"FPS:%d\n",fps_count);
//				OutputDebugString(str_fps);

//				font->DrawFont(str_fps ,100,100);
//				fps_count = 0;

				gra->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				font->DrawFont("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	ReleaseGameMain();  //�J��

	return (int)msg.wParam;
}

//////////////////////////////////////////////////////////
//
//      �����@�F�Q�[���Ŏg�������o�̊J������
//      ����  �F�Ȃ�
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_GameMain::ReleaseGameMain(void)
{
    //�J��
	scene->EndScene();
	delete scene;
	delete gra;
    delete font;
	delete wind;
	delete sou;
}

//////////////////////////////////////////////////////////
//
//      �����@�F���C�������̃R���g���[�����s��
//      ����  �F�Ȃ�
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_GameMain::ControlGame(void)
{
    switch(scene->GetSceneID()) //�V�[��ID�ɂ���ĕ���
    {
	case LOGO:
		delete scene;
		scene = new C_Logo();
		scene->InitScene(gra->GetDevice(),font,sou,0);
		break;
    case TITLE:
        delete scene;
		scene = new C_Title();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case TUTORIAL:
		delete scene;
		scene = new C_Tutorial();
		scene->InitScene(gra->GetDevice(),font,sou,0);
		break;
	case GAME_REFRESH:
        delete scene;
		scene = new C_GameRefresh();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case GAME_NORMAL:
        delete scene;
		scene = new C_GameNormal();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case RANKING:
		delete scene;
		scene = new C_Ranking();
		scene->InitScene(gra->GetDevice(),font,sou,score);
		break;
	case GAME_END:
		PostQuitMessage(0);
		break;
    }
}