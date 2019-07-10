/******************************************************************
 *	@file	SceneBase.cpp
 *	@brief	�V�[���x�[�X
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
	: mChangeSceneID(cSceneName_Logo)
	, mTexture(nullptr)
	, mVertex(nullptr)
	, mIsSceneEnd(false)
	, mMouseData()
{
	mTexture	= new Texture();
	mVertex		= new Vertex();
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
SceneBase::init()
{
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
void
SceneBase::update()
{
}

/**
 * @brief	�V�[���̕ύX���s��
 * @param	nextID		���̃V�[���̔ԍ�
 */
void
SceneBase::requestChangeScene(DWORD next_id)
{
    mChangeSceneID = next_id;
}

/**
 * @brief	�V�[���ԍ��̎擾
 */
DWORD
SceneBase::getChangeSceneID()
{
	return mChangeSceneID;
}

/**
 * @brief	�V�[���I����
 */
bool
SceneBase::isSceneEnd() const
{
	return mIsSceneEnd;
}