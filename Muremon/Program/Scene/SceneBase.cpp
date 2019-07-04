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
C_SceneBase::C_SceneBase()
{
    mSceneID	= cSceneName_Logo;    // 初期化
	mVertex		= new C_Vertex();
	mTexture	= new C_Texture();
}

/**
 * @brief	デストラクタ
 */
C_SceneBase::~C_SceneBase()
{
}

/**
 * @brief	実行処理
 */
bool
C_SceneBase::RunScene()
{
	bool is_scene_change = Update();
	Draw();
	return is_scene_change;
}

/**
 * @brief	設定処理
 * @param	apDev		デバイス
 */
void
C_SceneBase::SetScene(LPDIRECT3DDEVICE9 apDev)
{
	mDevice		= apDev;		// デバイスセット

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;
}

/**
 * @brief	シーンの変更を行う
 * @param	nextID		次のシーンの番号
 */
void
C_SceneBase::ChangeScene(DWORD next_id)
{
    mSceneID = next_id;
}

/**
 * @brief	シーン番号の取得
 */
DWORD
C_SceneBase::GetSceneID()
{
	return mSceneID;
}