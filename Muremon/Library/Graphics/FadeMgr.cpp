/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "FadeMgr.h"

#include "DirectGraphics.h"
#include "Texture.h"
#include "Vertex.h"

/* ���_�t�H�[�}�b�g�i��{�`�j*/
#define FVF_CUSTOM2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace
{
	struct SimpleVertex
	{
		float x, y, z;
		float rhw;
		DWORD color;
	};

	enum State
	{
		cState_Idle,		// �ҋ@
		cState_FadeIn,		// �t�F�[�h�C��
		cState_FadeOut,		// �t�F�[�h�A�E�g
		cState_Count
	};
}

FadeMgr* FadeMgr::mInstance = nullptr;

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
}

/**
 * @brief	�X�V
 */
void
FadeMgr::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
FadeMgr::draw() const
{
	// ���_�t�H�[�}�b�g�̎w��
	SimpleVertex cVertexDataTable[4] =
	{
		{ 0.0f,		0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 0.0f,		600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
	};

	// �`��
	mDevice->SetTexture(0, nullptr);
	mDevice->SetFVF(FVF_CUSTOM2D);
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, cVertexDataTable, sizeof(SimpleVertex));
}

/**
 * @brief	�t�F�[�h�C��
 */
void
FadeMgr::fadeIn()
{
	mState.changeStateIfDiff(cState_FadeIn);
}

/**
 * @brief	�t�F�[�h�A�E�g
 */
void
FadeMgr::fadeOut()
{
	mState.changeStateIfDiff(cState_FadeOut);
}

/**
 * @brief	�t�F�[�h���I���������H
 */
bool
FadeMgr::isFadeEnd() const
{
	return (mState.isEqual(cState_Idle));
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

/**
 * @brief	�R���X�g���N�^
 */
FadeMgr::FadeMgr()
	: mDevice(nullptr)
	, mAlpha(255)
	, mColorR(255)
	, mColorG(255)
	, mColorB(255)
	, mFadeSpeed(0)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(FadeMgr, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(FadeMgr, mState, FadeIn,		cState_FadeIn);
	REGIST_STATE_FUNC2(FadeMgr, mState, FadeOut,	cState_FadeOut);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
FadeMgr::~FadeMgr()
{
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
FadeMgr::stateEnterIdle()
{
}
void
FadeMgr::stateIdle()
{
}

/**
 * @brief �X�e�[�g:FadeIn
 */
void
FadeMgr::stateEnterFadeIn()
{
	mFadeSpeed = -6;
}
void
FadeMgr::stateFadeIn()
{
	mAlpha += mFadeSpeed;
	if (mAlpha <= 0)
	{
		mAlpha = 0;
		mState.changeState(cState_Idle);
		return;
	}
}

/**
 * @brief �X�e�[�g:FadeOut
 */
void
FadeMgr::stateEnterFadeOut()
{
	mFadeSpeed = 6;
}
void
FadeMgr::stateFadeOut()
{
	mAlpha += mFadeSpeed;
	if (255 <= mAlpha)
	{
		mAlpha = 255;
		mState.changeState(cState_Idle);
		return;
	}
}