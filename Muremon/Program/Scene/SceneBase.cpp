/******************************************************************
 *	@file	SceneBase.cpp
 *	@brief	シーンベース
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
	: mChangeSceneID(cSceneId_Logo)
	, mTexture(nullptr)
	, mVertex(nullptr)
	, mIsSceneEnd(false)
{
	mTexture	= new Texture();
	mVertex		= new Vertex();
}

/**
 * @brief	デストラクタ
 */
SceneBase::~SceneBase()
{
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	初期化処理
 */
void
SceneBase::init()
{
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
void
SceneBase::update()
{
}

/**
 * @brief	シーンの変更を行う
 * @param	nextID		次のシーンの番号
 */
void
SceneBase::requestChangeScene(DWORD next_id)
{
    mChangeSceneID = next_id;
}

/**
 * @brief	シーン番号の取得
 */
DWORD
SceneBase::getChangeSceneID()
{
	return mChangeSceneID;
}

/**
 * @brief	シーン終了か
 */
bool
SceneBase::isSceneEnd() const
{
	return mIsSceneEnd;
}