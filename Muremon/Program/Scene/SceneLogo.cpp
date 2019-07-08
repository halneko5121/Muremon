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
	mIsSceneEnd = false;
}

SceneLogo::~SceneLogo()
{
}

void SceneLogo::impleInit()
{
	mTexture->load("Data\\TextureData\\logo.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->load("Data\\RectData\\logo.txt");
}

void SceneLogo::update()
{
	mSceneChangeCount++;

	if (mSceneChangeCount == cSceneChangeCount)
	{
		mIsSceneEnd = true;
	}
}

void SceneLogo::draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_LOGO), mDevice);
	mVertex->drawF(400.f,300.f,R_LOGO);
}

void SceneLogo::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

}

