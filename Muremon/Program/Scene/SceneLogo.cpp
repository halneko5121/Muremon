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
	mIsSceneChange = true;
}

SceneLogo::~SceneLogo()
{
}

void SceneLogo::ImpleInit()
{
	mTexture->load("Data\\TextureData\\logo.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->load("Data\\RectData\\logo.txt");
}

bool SceneLogo::update()
{
	mSceneChangeCount++;

	if (mSceneChangeCount == cSceneChangeCount)
	{
		mIsSceneChange = false;
	}

	return mIsSceneChange;
}

void SceneLogo::Draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_LOGO), mDevice);
	mVertex->drawF(400.f,300.f,R_LOGO);
}

int SceneLogo::End()
{
	ChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

	return 0;
}

