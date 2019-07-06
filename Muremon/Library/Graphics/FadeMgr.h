#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"

class Texture;
class Vertex;

class FadeMgr
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	FadeMgr();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~FadeMgr();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static FadeMgr*		GetInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void			Create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			Destroy();

	/**
	 * @brief	������
	 */
	void				Init(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	�X�V
	 */
	void				Update();

	/**
	 * @brief	�`��
	 */
	void				Draw();

	/**
	 * @brief	�t�F�[�h�C��
	 */
	void				FadeIn();

	/**
	 * @brief	�t�F�[�h�A�E�g
	 */
	void				FadeOut();

	/**
	 * @brief	�t�F�[�h���I���������H
	 */
	bool				IsFadeEnd();

	/**
	 * @brief	�J���[�̃Z�b�g
	 */
	void				SetColor(int r, int g, int b);

private:
	enum FadeState
	{
		cFadeState_None,
		cFadeState_FadeIn,
		cFadeState_FadeOut,
	};

private:
	static FadeMgr*		mInstance;		// �C���X�^���X
	LPDIRECT3DDEVICE9	mDevice;		// �f�o�C�X
	Texture*			mTexture;		// �e�N�X�`��
	Vertex*				mVertex;		// �o�[�e�b�N�X

	int					mAlpha;			// �A���t�@
	int					mColorR;		// �J���[(R)
	int					mColorG;		// �J���[(R)
	int					mColorB;		// �J���[(R)
	int					mFadeSpeed;		// �t�F�[�h���x
	FadeState			mState;			// �X�e�[�g
};

static FadeMgr* GetFadeMgr() { return FadeMgr::GetInstance(); }
