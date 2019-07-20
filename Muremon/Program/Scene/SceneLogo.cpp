/******************************************************************
 *	@file	SceneLogo.cpp
 *	@brief	���S�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
 * @brief	������
 */
void
SceneLogo::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "logo");
}

/**
 * @brief	�X�V
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
 * @brief	�`��
 */
void
SceneLogo::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_LOGO);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_LOGO);
}

/**
 * @brief	�V�[���I��
 */
void
SceneLogo::end()
{
	requestChangeScene(cSceneId_Title);
}

