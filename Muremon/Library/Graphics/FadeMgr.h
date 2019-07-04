#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Vertex;

class FadeMgr
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	FadeMgr(Vertex* vertex);

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
	static void			Create(Vertex* vertex);

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			Destroy();

	/**
	 * @brief	�X�V
	 */
	void				Update();

	/**
	 * @brief	�t�F�[�h�C��
	 */
	void				FadeIn();

	/**
	 * @brief	�t�F�[�h�A�E�g
	 */
	void				FadeOut();

	/**
	 * @brief	�t�F�[�h�C������
	 */
	bool				IsFadeIn();

	/**
	 * @brief	�t�F�[�h�A�E�g����
	 */
	bool				IsFadeOut();


private:
	enum FadeState
	{
		cFadeState_None,
		cFadeState_FadeIn,
		cFadeState_FadeOut,
	};

private:
	static FadeMgr*		mInstance;		// �C���X�^���X
	Vertex*				mVertex;		// �o�[�e�b�N�X
	int					mAlpha;			// �A���t�@
	int					mFadeSpeed;		// �t�F�[�h���x
	FadeState			mState;			// �X�e�[�g
};

static FadeMgr* GetFadeMgr() { return FadeMgr::GetInstance(); }
