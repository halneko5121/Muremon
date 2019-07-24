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
#include "Library/Graphics/FadeMgr.h"
#include "Library/Sound/DirectSound.h"
#include "Program/DefineGame.h"
#include "Program/System/GameScore.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/Actor/ActorMgr.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Collision/CollisionMgr.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilBattle.h"

// �e�V�[����include
#include "Program/Scene/SceneLogo.h"
#include "Program/Scene/SceneTitle.h"
#include "Program/Scene/SceneTutorial.h"
#include "Program/Scene/SceneGameRefresh.h"
#include "Program/Scene/SceneGameNormal.h"
#include "Program/Scene/SceneRanking.h"

namespace
{
	// Window��\������ʒu
	const int cWindowPosY = 100;
	const int cWindowPosX = 220;

	// �Q�[���p�J�[�\���̃T�C�Y
	const int cCursorHeight = 20;
	const int cCursorWidth = 20;

	enum State
	{
		cState_Idle,
		cState_Init,
		cState_Run,
		cState_End,
		cState_Count,
	};
}

/**
 * @brief	�R���X�g���N�^
 */
GameMain::GameMain()
	: mState()
	, mWindow(nullptr)
	, mScene(nullptr)
	, mGraphics(nullptr)
	, mBackground(255)
{
}

/**
 * @brief	�f�X�g���N�^
 */
GameMain::~GameMain()
{
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
	GameInfoMgr::create();
	ActorMgr::create();
	EffectMgr::create();
	CollisionMgr::create();

	// �ŏ��̃V�[����
	mScene = new SceneLogo();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(GameMain, mState, Idle,	cState_Idle);
	REGIST_STATE_FUNC2(GameMain, mState, Init,	cState_Init);
	REGIST_STATE_FUNC2(GameMain, mState, Run,	cState_Run);
	REGIST_STATE_FUNC2(GameMain, mState, End,	cState_End);
	mState.changeState(cState_Idle);
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
	if(FAILED(getInputKey()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInput�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(getInputMouse()->init(mWindow->getWindowHandle())))
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
	if(FAILED(getDirectFont()->init(mGraphics->getDevice())))
	{
		MessageBox(NULL, TEXT("DirectFont�̏������Ɏ��s"), NULL, MB_OK);
		return 0;
	}

	// DirectSound������
	if(FAILED(getDirectSound()->init(mWindow->getWindowHandle())))
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
	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// ������
	ZeroMemory(&msg , sizeof(msg));

	// �`��ݒ�
	mGraphics->initRender();
	getFadeMgr()->init(mGraphics->getDevice());
	getFadeMgr()->setColor(0, 0, 0);

	getDirectSound()->load("Data\\sound_data.txt");

	// �ŏ��̃V�[���̏�����
	mState.changeState(cState_Init);

	srand((unsigned int)time(NULL));

	// ���[�v
	int cnt = 0;
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
				getInputKey()->update();
				mGraphics->renderStart(mBackground);
				getFadeMgr()->update();

				mState.executeState();
				mScene->draw();

				getFadeMgr()->draw();
				mGraphics->renderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				getDirectFont()->draw("a",750,550);
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
	getInputMouse()->release();
	DirectInputMouse::destroy();
	getInputKey()->release();
	DirectInputKey::destroy();
	ActorMgr::destroy();
	EffectMgr::destroy();
	DirectSound::destroy();
	CollisionMgr::destroy();
	GameInfoMgr::destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief �V�[���̐���
 */
SceneBase*
GameMain::createScene(int scene_id)
{
	switch (scene_id) {
	case cSceneId_Logo:			return (new SceneLogo());
	case cSceneId_Title:		return (new SceneTitle());
	case cSceneId_Tutorial:		return (new SceneTutorial());
	case cSceneId_GameRefresh:	return (new SceneGameRefresh());
	case cSceneId_GameNormal:	return (new SceneGameNormal());
	case cSceneId_Ranking:		return (new SceneRanking());
	case cSceneId_GameEnd:		return (new SceneBase());
	}

	APP_ASSERT_FALSE_MESSAGE("�ǂ̃V�[������������܂���ł���");
	return nullptr;
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
GameMain::stateEnterIdle()
{
}
void
GameMain::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Init
 */
void
GameMain::stateEnterInit()
{
	getFadeMgr()->fadeIn();

	// �V�[��ID�ɂ���ĕ���
	int next_scene_id = mScene->getChangeSceneID();
	APP_SAFE_DELETE(mScene);
	mScene = createScene(next_scene_id);
	mScene->init();

	// ���Z�b�g
	if (next_scene_id == cSceneId_Title)
	{
		UtilGame::setScore(0);
		UtilBattle::resetAtkCount();
	}
	else if (next_scene_id == cSceneId_GameEnd)
	{
		PostQuitMessage(0);
	}
}
void
GameMain::stateInit()
{
	if (getFadeMgr()->isFadeEnd())
	{
		mState.changeState(cState_Run);
		return;
	}
}

/**
 * @brief �X�e�[�g:Run
 */
void
GameMain::stateEnterRun()
{
}
void
GameMain::stateRun()
{
	mScene->update();

	if (mScene->isSceneEnd())
	{
		// ���S���I�������N���A���̐F�𔒂ɂ���
		if (mScene->getChangeSceneID() == cSceneId_Title)
		{
			mBackground = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
			getFadeMgr()->setColor(255, 255, 255);
		}
		// �^�C�g�����I�������N���A���̐F�����ɂ���
		if (mScene->getChangeSceneID() == cSceneId_Prologue)
		{
			mBackground = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
			getFadeMgr()->setColor(0, 0, 0);
		}

		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
GameMain::stateEnterEnd()
{
	getFadeMgr()->fadeOut();
}
void
GameMain::stateEnd()
{
	if (getFadeMgr()->isFadeEnd())
	{
		// �V�[���I��
		mScene->end();
		mState.changeState(cState_Init);
		return;
	}
}