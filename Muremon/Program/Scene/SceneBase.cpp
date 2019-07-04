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

/**
 * @brief	�R���X�g���N�^
 */
C_SceneBase::C_SceneBase()
{
    mSceneID	= cSceneName_Logo;    // ������
	mVertex		= new C_Vertex();
	mTexture	= new C_Texture();
}

/**
 * @brief	�f�X�g���N�^
 */
C_SceneBase::~C_SceneBase()
{
}

/**
 * @brief	���s����
 */
bool
C_SceneBase::RunScene()
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
C_SceneBase::SetScene(LPDIRECT3DDEVICE9 apDev)
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
C_SceneBase::ChangeScene(DWORD next_id)
{
    mSceneID = next_id;
}

/**
 * @brief	�V�[���ԍ��̎擾
 */
DWORD
C_SceneBase::GetSceneID()
{
	return mSceneID;
}