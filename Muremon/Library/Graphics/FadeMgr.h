#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/StateMachine.h"

class FadeMgr
{
public:
	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static FadeMgr*		getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void			create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			destroy();

	/**
	 * @brief	������
	 */
	void				init(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	�X�V
	 */
	void				update();

	/**
	 * @brief	�`��
	 */
	void				draw() const;

	/**
	 * @brief	�t�F�[�h�C��
	 */
	void				fadeIn();

	/**
	 * @brief	�t�F�[�h�A�E�g
	 */
	void				fadeOut();

	/**
	 * @brief	�t�F�[�h���I���������H
	 */
	bool				isFadeEnd() const;

	/**
	 * @brief	�J���[�̃Z�b�g
	 */
	void				setColor(int r, int g, int b);

private:
	/**
	 * @brief	�R���X�g���N�^
	*/
	FadeMgr();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~FadeMgr();

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(FadeIn);
	DECLAR_STATE_FUNC2(FadeOut);

private:
	static FadeMgr*			mInstance;		// �C���X�^���X

	StateMachine			mState;			// �X�e�[�g
	LPDIRECT3DDEVICE9		mDevice;		// �f�o�C�X
	int						mAlpha;			// �A���t�@
	int						mColorR;		// �J���[(R)
	int						mColorG;		// �J���[(R)
	int						mColorB;		// �J���[(R)
	int						mFadeSpeed;		// �t�F�[�h���x
};

static FadeMgr* GetFadeMgr() { return FadeMgr::getInstance(); }
