/******************************************************************
 *	@file	SceneLogo.cpp
 *	@brief	ロゴシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneLogo.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"

namespace
{
	const int cSceneChangeCount = 129;

	enum TEXTURE_DATA_LOGO
	{
		T_LOGO,
	};

	enum RECT_DATA_LOGO
	{
		R_LOGO,
	};
}

SceneLogo::SceneLogo()
	: mSceneChangeCount(0)
{
}

SceneLogo::~SceneLogo()
{
}

/**
 * @brief	初期化
 */
void
SceneLogo::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "logo");
}

/**
 * @brief	更新
 */
void
SceneLogo::update()
{
	mSceneChangeCount++;

	if (mSceneChangeCount == cSceneChangeCount)
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief	描画
 */
void
SceneLogo::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_LOGO);
	mVertex->drawF(400.f,300.f,R_LOGO);
}

/**
 * @brief	シーン終了
 */
void
SceneLogo::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

}

