/******************************************************************
 *	@file	SceneManage.cpp
 *	@brief	シーンの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneBase.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"

/**
 * @brief	コンストラクタ
 */
SceneBase::SceneBase()
{
    mSceneID	= cSceneName_Logo;    // 初期化
	mVertex		= new Vertex();
	mTexture	= new Texture();
}

/**
 * @brief	デストラクタ
 */
SceneBase::~SceneBase()
{
	APP_SAFE_DELETE(mVertex);
	APP_SAFE_DELETE(mTexture);
}

/**
 * @brief	初期化処理
 */
void
SceneBase::init(LPDIRECT3DDEVICE9 apDev)
{
	mDevice = apDev;		// デバイスセット

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;

	impleInit();
}

/**
 * @brief	オーバーライドされる前提の処理
 */
void
SceneBase::impleInit()
{
}

/**
 * @brief	実行処理
 */
bool
SceneBase::runScene()
{
	bool is_scene_change = update();
	return is_scene_change;
}

/**
 * @brief	シーンの変更を行う
 * @param	nextID		次のシーンの番号
 */
void
SceneBase::requestChangeScene(DWORD next_id)
{
    mSceneID = next_id;
}

/**
 * @brief	シーン番号の取得
 */
DWORD
SceneBase::getSceneID()
{
	return mSceneID;
}