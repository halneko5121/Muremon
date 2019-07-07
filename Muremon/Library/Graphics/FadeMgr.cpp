/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "FadeMgr.h"
#include "Texture.h"
#include "Vertex.h"

FadeMgr* FadeMgr::mInstance = nullptr;

 /**
  * @brief	�R���X�g���N�^
  */
FadeMgr::FadeMgr()
	: mTexture(nullptr)
	, mVertex(nullptr)
	, mAlpha(255)
	, mColorR(255)
	, mColorG(255)
	, mColorB(255)
	, mFadeSpeed(0)
	, mState(cFadeState_None)
{
	mTexture = new Texture();
	mVertex = new Vertex();
}

/**
 * @brief	�f�X�g���N�^
 */
FadeMgr::~FadeMgr()
{
	mTexture->release();
	mVertex->AllReleaseRect();
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	�C���X�^���X�̎擾
 */
FadeMgr*
FadeMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
FadeMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new FadeMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
FadeMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	������
 */
void
FadeMgr::init(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
	mTexture->load("Library\\Data\\T_Fade.txt", mDevice); // �G�̓ǂݍ���
	mVertex->LoadRect("Library\\Data\\R_Fade.txt");
}

/**
 * @brief	�X�V
 */
void
FadeMgr::update()
{
	switch (mState)
	{
	case cFadeState_FadeIn:
		mAlpha += mFadeSpeed;
		if (mAlpha <= 0)
		{
			mAlpha = 0;
			mState = cFadeState_None;
		}
		break;

	case cFadeState_FadeOut:
		mAlpha += mFadeSpeed;
		if (255 <= mAlpha)
		{
			mAlpha = 255;
			mState = cFadeState_None;
		}
		break;

	default:
		break;
	}
}

/**
 * @brief	�`��
 */
void
FadeMgr::draw()
{
	mVertex->SetTextureData(mTexture->getTextureData(0), mDevice);
	mVertex->SetColor(mAlpha, mColorR, mColorG, mColorB);
	mVertex->DrawF(400.f, 300.f, 0);
}

/**
 * @brief	�t�F�[�h�C��
 */
void
FadeMgr::fadeIn()
{
	mState = cFadeState_FadeIn;
	mFadeSpeed = -6;
}

/**
 * @brief	�t�F�[�h�A�E�g
 */
void
FadeMgr::fadeOut()
{
	mState = cFadeState_FadeOut;
	mFadeSpeed = 6;
}

/**
 * @brief	�t�F�[�h���I���������H
 */
bool
FadeMgr::isFadeEnd()
{
	return (mState == cFadeState_None);
}

/**
 * @brief	�J���[�̃Z�b�g
 */
void
FadeMgr::setColor(int r, int g, int b)
{
	mColorR = r;
	mColorG = g;
	mColorB = b;
}
