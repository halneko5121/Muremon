/******************************************************************
 *	@file	SceneManage.cpp
 *	@brief	�V�[���̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneBase.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/FadeMgr.h"

/**
 * @brief	�R���X�g���N�^
 */
SceneBase::SceneBase()
{
    mSceneID	= cSceneName_Logo;    // ������
	mVertex		= new Vertex();
	mTexture	= new Texture();

}

/**
 * @brief	�f�X�g���N�^
 */
SceneBase::~SceneBase()
{
}

/**
 * @brief	���s����
 */
bool
SceneBase::RunScene()
{
	bool is_scene_change = Update();
	Draw();
	return is_scene_change;
}

/**
 * @brief	�ݒ菈��
 * @param	apDev		�f�o�C�X
 */
void
SceneBase::SetScene(LPDIRECT3DDEVICE9 apDev)
{
	mDevice		= apDev;		// �f�o�C�X�Z�b�g

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;
}

/**
 * @brief	�V�[���̕ύX���s��
 * @param	nextID		���̃V�[���̔ԍ�
 */
void
SceneBase::ChangeScene(DWORD next_id)
{
    mSceneID = next_id;
}

/**
 * @brief	�V�[���ԍ��̎擾
 */
DWORD
SceneBase::GetSceneID()
{
	return mSceneID;
}