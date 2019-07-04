 /******************************************************************
  *	@file	GameManage.cpp
  *	@brief	�Q�[���S�̂̊Ǘ����s��
  *
  *	����ҁF�O��
  *	�Ǘ��ҁF�O��
  ******************************************************************/

#include "GameManage.h"
#include "Library/Font/DirectFont.h"
#include "Library/Input/DirectInput.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Sound/DirectSound.h"
// �e�V�[����include
#include "Program/Scene/Logo.h"
#include "Program/Scene/Title.h"
#include "Program/Scene/Tutorial.h"
#include "Program/Scene/GameRefresh.h"
#include "Program/Scene/GameNormal.h"
#include "Program/Scene/Ranking.h"

 /**
  * @brief	�Q�[���Ŏg�������o�̏�����
  */
void
C_GameMain::InitGameMain(void)
{
	mWindow			= new C_Window;
	mGraphics		= C_DGraphics::Create();
	C_DInputKey::Create();
	C_DInputMouse::Create();
	C_DFont::Create();
	C_DSound::Create();

	// �ŏ��̃V�[����
	mScene = new SceneLogo();
	mScore = 0;
}

/**
 * @brief ���C���֐�
 * @param	hInstance   �C���X�^���X�n���h��(�v���O�����𓮂������߂̂���)
 * @param	hPrevInst   ���̑O�̏�Ԃ�ۑ����Ă���(1�ڂɏ�񂪓����ĂȂ��������p)
 * @param	lpCmdLine	Windows����̖��߂��i�[�����(�|�C���^�̐擪�A�h���X)
 * @param	nShowCmd    ���̖��߂���������̂�
 * @return  int         ���b�Z�[�W���[�v��Ԃ�
 */
int WINAPI
C_GameMain::WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	InitGameMain();
	mWindow->InitWindow(hInstance);	// �E�B���h�E�������֐�

	// �e���C�u�����̏�����
	// DirectInput������
	if(FAILED(GetInputKey()->Init(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectInput�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(GetInputMouse()->Init(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectInput�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectGraphics������
	if(FAILED(mGraphics->InitDGraphics(mWindow, mWindow->GetHwnd(), GAMESIZE_WIDE, GAMESIZE_HEIGHT)))
	{
		MessageBox(NULL, TEXT("DirectGraphics�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectFont������
	if(FAILED(GetDirectFont()->InitDFont(mGraphics->GetDevice())))
	{
		MessageBox(NULL, TEXT("DirectFont�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectSound������
	if(FAILED(GetDirectSound()->InitDSound(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectSound�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	return MsgLoop();
}
	
/**
 * @brief	�Q�[�������[�v�֐�
 * @return  ���b�Z�[�W�p�����[�^
 */
int
C_GameMain::MsgLoop(void)
{
	// ������
	MSG msg;
	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// ������
	ZeroMemory(&msg , sizeof(msg));

	// �`��ݒ�
	mGraphics->SetRender();

	GetDirectSound()->LoadSoundData("Data\\sound_data.txt");

	// �ŏ��̃V�[���̏�����
	mScene->SetScene(mGraphics->GetDevice());
	mScene->Init();

	srand((unsigned int)time(NULL));

	// ���[�v
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg , NULL , 0 , 0 , PM_REMOVE))
		{
			// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ύX
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
				GetInputKey()->Update();
				mGraphics->RenderStart(mBackground);
				if(!mScene->RunScene())
				{
					// �V�[���I��
					mScore = mScene->End();
					// ���S���I�������N���A���̐F�𔒂ɂ���
					if(mScene->GetSceneID() == cSceneName_Title) mBackground = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);
					// �^�C�g�����I�������N���A���̐F�����ɂ���
					if(mScene->GetSceneID() == cSceneName_Prologue) mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

					// �V�[�����ς�������̏���(�V�[���؂�ւ�)��
					ControlSequence();				
				}
				mGraphics->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				GetDirectFont()->DrawFont("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	ReleaseGameMain();  

	return (int)msg.wParam;
}

/**
 * @brief �Q�[���Ŏg�������o�̊J������
 */
void
C_GameMain::ReleaseGameMain(void)
{
    // �J��
	mScene->End();

	GetInputKey()->ReleaseDirectInput();
	APP_SAFE_DELETE(mScene);
	C_DGraphics::Destroy();
	mGraphics = nullptr;
	C_DFont::Destroy();
	C_DInputKey::Destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief �V�[�P���X�̊Ǘ����s��
 */
void
C_GameMain::ControlSequence(void)
{
	// �V�[��ID�ɂ���ĕ���
	switch(mScene->GetSceneID()){
	case cSceneName_Logo:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneLogo();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
    case cSceneName_Title:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTitle();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_Tutorial:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTutorial();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_GameRefresh:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameRefresh();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_GameNormal:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameNormal();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_Ranking:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneRanking();
		mScene->SetScene(mGraphics->GetDevice());
		dynamic_cast<SceneRanking*>(mScene)->InitScene(mScore);
		break;
	case cSceneName_GameEnd:
		PostQuitMessage(0);
		break;
    }
}