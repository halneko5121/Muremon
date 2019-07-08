 /******************************************************************
  *	@file	GameMain.cpp
  *	@brief	�Q�[�����C��
  *
  *	����ҁF�O��
  *	�Ǘ��ҁF�O��
  ******************************************************************/

#include "GameMain.h"

#include "Library/Font/DirectFont.h"
#include "Library/Input/DirectInput.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/FadeMgr.h"
#include "Library/Sound/DirectSound.h"
#include "Program/DefineGame.h"
#include "Program/System/GameScore.h"

// �e�V�[����include
#include "Program/Scene/SceneLogo.h"
#include "Program/Scene/SceneTitle.h"
#include "Program/Scene/SceneTutorial.h"
#include "Program/Scene/SceneGameRefresh.h"
#include "Program/Scene/SceneGameNormal.h"
#include "Program/Scene/SceneRanking.h"

namespace
{
	enum State
	{
		cState_Init,
		cState_Run,
		cState_End,
		cState_Count,
	};
}

 /**
  * @brief	�Q�[���Ŏg�������o�̏�����
  */
void
GameMain::init(void)
{
	mWindow			= new Window;
	mGraphics		= DirectGraphics::create();
	DirectInputKey::create();
	SIZE window_size = { cWindowWidth, cWindowHeight };
	POINT window_pos = { cWindowPosX, cWindowPosY };
	SIZE cursor_size = { cCursorWidth, cCursorHeight };
	DirectInputMouse::create(window_size, window_pos, cursor_size);
	DirectFont::create();
	DirectSound::create();
	FadeMgr::create();
	GameScore::create();

	// �ŏ��̃V�[����
	mScene = new SceneLogo();

	mState.initialize(cState_Count, cState_Init);
	mState.registState(this, &GameMain::stateEnterInit,	&GameMain::stateExeInit,	nullptr, cState_Init);
	mState.registState(this, &GameMain::stateEnterRun,	&GameMain::stateExeRun,		nullptr, cState_Run);
	mState.registState(this, &GameMain::stateEnterEnd,	&GameMain::stateExeEnd,		nullptr, cState_End);
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
GameMain::winMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	init();

	// �E�B���h�E�������֐�
	mWindow->init(hInstance, cWindowWidth, cWindowHeight, cWindowPosX, cWindowPosY);

	// �e���C�u�����̏�����
	// DirectInput������
	if(FAILED(GetInputKey()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInput�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(GetInputMouse()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInput�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectGraphics������
	if(FAILED(mGraphics->init(mWindow, mWindow->getWindowHandle(), cWindowWidth, cWindowHeight)))
	{
		MessageBox(NULL, TEXT("DirectGraphics�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectFont������
	if(FAILED(GetDirectFont()->init(mGraphics->getDevice())))
	{
		MessageBox(NULL, TEXT("DirectFont�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectSound������
	if(FAILED(GetDirectSound()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectSound�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	return msgLoop();
}
	
/**
 * @brief	�Q�[�������[�v�֐�
 * @return  ���b�Z�[�W�p�����[�^
 */
int
GameMain::msgLoop(void)
{
	// ������
	MSG msg;
	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// ������
	ZeroMemory(&msg , sizeof(msg));

	// �`��ݒ�
	mGraphics->initRender();
	GetFadeMgr()->init(mGraphics->getDevice());
	GetFadeMgr()->setColor(0, 0, 0);

	GetDirectSound()->load("Data\\sound_data.txt");

	// �ŏ��̃V�[���̏�����
	mState.changeState(cState_Init);

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
				GetInputKey()->update();
				mGraphics->renderStart(mBackground);
				GetFadeMgr()->update();

				mState.executeState();

				GetFadeMgr()->draw();
				mGraphics->renderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				GetDirectFont()->draw("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	release();  

	return (int)msg.wParam;
}

/**
 * @brief �Q�[���Ŏg�������o�̊J������
 */
void
GameMain::release(void)
{
    // �J��
	mScene->end();

	APP_SAFE_DELETE(mScene);
	DirectGraphics::destroy();
	mGraphics = nullptr;
	FadeMgr::destroy();
	DirectFont::destroy();
	GetInputMouse()->release();
	DirectInputMouse::destroy();
	GetInputKey()->release();
	DirectInputKey::destroy();
	GameScore::destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief �V�[�P���X�̊Ǘ����s��
 */
void
GameMain::controlSequence(void)
{
	// �V�[��ID�ɂ���ĕ���
	switch(mScene->getSceneID()){
	case cSceneName_Logo:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneLogo();
		mScene->init(mGraphics->getDevice());
		break;
    case cSceneName_Title:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTitle();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_Tutorial:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTutorial();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameRefresh:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameRefresh();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameNormal:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameNormal();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_Ranking:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneRanking();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameEnd:
		PostQuitMessage(0);
		break;
    }
}


// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Init
 */
void
GameMain::stateEnterInit()
{
	GetFadeMgr()->fadeIn();

	// �V�[���؂�ւ�
	controlSequence();
}
void
GameMain::stateExeInit()
{
	if (GetFadeMgr()->isFadeEnd())
	{
		mState.changeState(cState_Run);
		return;
	}

	mScene->draw();
}

/**
 * @brief �X�e�[�g:Run
 */
void
GameMain::stateEnterRun()
{
	mScene->draw();
}
void
GameMain::stateExeRun()
{
	if (!mScene->runScene())
	{
		// ���S���I�������N���A���̐F�𔒂ɂ���
		if (mScene->getSceneID() == cSceneName_Title)
		{
			mBackground = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
			GetFadeMgr()->setColor(255, 255, 255);
		}
		// �^�C�g�����I�������N���A���̐F�����ɂ���
		if (mScene->getSceneID() == cSceneName_Prologue)
		{
			mBackground = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
			GetFadeMgr()->setColor(0, 0, 0);
		}

		mState.changeState(cState_End);
		return;
	}

	mScene->draw();
}

/**
 * @brief �X�e�[�g:End
 */
void
GameMain::stateEnterEnd()
{
	GetFadeMgr()->fadeOut();
	mScene->draw();
}
void
GameMain::stateExeEnd()
{
	if (GetFadeMgr()->isFadeEnd())
	{
		// �V�[���I��
		mScene->end();
		mState.changeState(cState_Init);
		return;
	}

	mScene->draw();
}