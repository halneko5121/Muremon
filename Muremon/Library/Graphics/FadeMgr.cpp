/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "FadeMgr.h"
#include "Vertex.h"

FadeMgr* FadeMgr::mInstance = nullptr;

 /**
  * @brief	�R���X�g���N�^
  */
FadeMgr::FadeMgr(Vertex* vertex)
	: mVertex(vertex)
	, mAlpha(0)
	, mFadeSpeed(0)
	, mState(cFadeState_None)
{
}

/**
 * @brief	�f�X�g���N�^
 */
FadeMgr::~FadeMgr()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
FadeMgr*
FadeMgr::GetInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
FadeMgr::Create(Vertex* vertex)
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new FadeMgr(vertex);
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
FadeMgr::Destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�t�F�[�h�C��
 */
void
FadeMgr::Update()
{
	switch (mState)
	{
	case cFadeState_FadeIn:
		mAlpha += mFadeSpeed;
		if (mAlpha <= 0)	mAlpha = 0;
		break;

	case cFadeState_FadeOut:
		mAlpha += mFadeSpeed;
		if (255 <= mAlpha)	mAlpha = 255;
		break;

	default:
		break;
	}

	mVertex->SetColor(mAlpha, 255, 255, 255);
}

/**
 * @brief	�t�F�[�h�C��
 */
void
FadeMgr::FadeIn()
{
	mState = cFadeState_FadeIn;
	mFadeSpeed = -5;
}

/**
 * @brief	�t�F�[�h�A�E�g
 */
void
FadeMgr::FadeOut()
{
	mState = cFadeState_FadeOut;
	mFadeSpeed = 5;
}

/**
 * @brief	�t�F�[�h�C������
 */
bool
FadeMgr::IsFadeIn()
{
	return (mState == cFadeState_FadeIn);
}

/**
 * @brief	�t�F�[�h�A�E�g����
 */
bool
FadeMgr::IsFadeOut()
{
	return (mState == cFadeState_FadeOut);
}