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
	APP_SAFE_DELETE(mVertex);
	APP_SAFE_DELETE(mTexture);
}

/**
 * @brief	����������
 */
void
SceneBase::init(LPDIRECT3DDEVICE9 apDev)
{
	mDevice = apDev;		// �f�o�C�X�Z�b�g

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;

	impleInit();
}

/**
 * @brief	�I�[�o�[���C�h�����O��̏���
 */
void
SceneBase::impleInit()
{
}

/**
 * @brief	���s����
 */
bool
SceneBase::runScene()
{
	bool is_scene_change = update();
	return is_scene_change;
}

/**
 * @brief	�V�[���̕ύX���s��
 * @param	nextID		���̃V�[���̔ԍ�
 */
void
SceneBase::requestChangeScene(DWORD next_id)
{
    mSceneID = next_id;
}

/**
 * @brief	�V�[���ԍ��̎擾
 */
DWORD
SceneBase::getSceneID()
{
	return mSceneID;
}