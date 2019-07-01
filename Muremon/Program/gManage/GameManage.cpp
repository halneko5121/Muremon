//---------------------------------------------
//
//      �Q�[���S�̂̊Ǘ����s��
//			�쐬��:����
//
//---------------------------------------------

#include "GameManage.h"
#include "Library/Sound/DirectSound.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�Q�[���Ŏg�������o�̏�����
//      ����  �F�Ȃ�
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_GameMain::InitGameMain(void)
{
    // �V��������
	mWindow		= new C_Window;
	mGraphics	= new C_DGraphics;
    mFont		= new C_DFont;
	mScene		= new C_Logo();
	C_DSound::Create();
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
	mWindow->InitWindow(hInstance);

	//DirectGraphics������
	if(FAILED(mGraphics->InitDGraphics(mWindow,mWindow->GetHwnd(),800,600)))
	{
		MessageBox(NULL,TEXT("DirectGraphics�̏������Ɏ��s"),NULL,MB_OK);
		return 0;
	}
    //DirectFont������
	if(FAILED(mFont->InitDFont(mGraphics->GetDevice())))
	{
		MessageBox(NULL,TEXT("DirectFont�̏������Ɏ��s"),NULL,MB_OK);
		return 0;
	}

	//DirectSound������
	if(FAILED(GetDirectSound()->InitDSound(mWindow->GetHwnd())))
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

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	//������
	ZeroMemory(&msg , sizeof(msg));

	mGraphics->SetRender();	//�`��ݒ�

    mScene->InitScene(mGraphics->GetDevice(), mFont, 0);

	GetDirectSound()->LoadSoundData("Data\\sound_data.txt");

	srand((unsigned int)time(NULL));

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
				mGraphics->RenderStart(mBackground);
				if(!mScene->RunScene())
				{
					mScore = mScene->EndScene();								//�V�[���I��
					if(mScene->GetSceneID() == TITLE) mBackground = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);	//���S���I�������N���A���̐F�𔒂ɂ���
					if(mScene->GetSceneID() == PROLOGUE) mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);	//�^�C�g�����I�������N���A���̐F�����ɂ���
					ControlGame();										//�V�[���؂�ւ�
				}

				mGraphics->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				mFont->DrawFont("a",750,550);
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
	mScene->EndScene();
	delete mScene;
	delete mGraphics;
    delete mFont;
	delete mWindow;
	C_DSound::Destroy();
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
    switch(mScene->GetSceneID()) //�V�[��ID�ɂ���ĕ���
    {
	case LOGO:
		delete mScene;
		mScene = new C_Logo();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
		break;
    case TITLE:
        delete mScene;
		mScene = new C_Title();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case TUTORIAL:
		delete mScene;
		mScene = new C_Tutorial();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
		break;
	case GAME_REFRESH:
        delete mScene;
		mScene = new C_GameRefresh();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case GAME_NORMAL:
        delete mScene;
		mScene = new C_GameNormal();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case RANKING:
		delete mScene;
		mScene = new C_Ranking();
		mScene->InitScene(mGraphics->GetDevice(), mFont, mScore);
		break;
	case GAME_END:
		PostQuitMessage(0);
		break;
    }
}