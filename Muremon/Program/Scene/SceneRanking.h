#pragma once
/******************************************************************
 *	@file	SceneRanking.h
 *	@brief	�����L���O�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class SceneRanking : public SceneBase
{
public:
	SceneRanking(void);
	~SceneRanking(void);

	void		impleInit() override;
	void		init(LPDIRECT3DDEVICE9 apDev, int score);
	bool		update() override;
	void		draw() override;
	int			end() override;

private:
	void		updateFade();

	void		updateRanking(int rank);	// �����N�C���������A���O������͂���
	void		sortRanking(int get);		// �X�R�A�̕��ёւ�
	void		loadRanking();				// �f�[�^�̓ǂݍ���
	void		writeRanking();				// �f�[�^�̏�������

	void		drawBackGround();			// �����L���O�w�i
	void		drawRankingPlace();			// �����L���O�ʒu
	void		drawRankingName();			// �����L���O���O
	void		drawRankingScore();			// �����L���O�X�R�A

	void		checkRanking();
	void		initRanking();
	void		updateInput();

private:
	int		mTimeCount;					// �`�悷��^�C���J�E���g
	int		mRank;						// �����N�C�����Ă��邩
	int		mFadeFlag;					// �t�F�[�h����t���O
	int		mFontAlpha;
	int		mFlag;
	int		mKeyNo;
	int		mIn;
	int		mDelay;

	int		mNameAlpha[5][3];
	int		mNameRed[5][3];
	int		mNameBlue[5][3];
	int		mNameGreen[5][3];
	char	mKeepKey[3];

	bool	mIsWrite;

	int		mNameFontAlpha;
	bool	mIsNameBlink;
	bool	mIsNameAlphaDown;

	int		mKeyState;
	bool	mIsDrawRank;
	int		mAddScore;
	bool	mIsRanking;
};