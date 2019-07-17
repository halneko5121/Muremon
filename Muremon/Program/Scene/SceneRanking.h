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
	SceneRanking();
	~SceneRanking();

	void		impleInit() override;
	void		update() override;
	void		draw() const override;
	void		end() override;

private:
	struct RankingData
	{
		char	mName[3];	// ���O
		int		mScore;		// �X�R�A
	};

private:
	void		updateRanking(int rank);	// �����N�C���������A���O������͂���
	void		loadRanking();				// �f�[�^�̓ǂݍ���
	void		writeRanking();				// �f�[�^�̏�������
	int			checkRankingIn();			// �����N�C�����Ă邩�`�F�b�N
	void		sortRanking(int new_rank);	// �X�R�A�̕��ёւ�

	void		drawBackGround() const;		// �����L���O�w�i
	void		drawRankingPlace() const;	// �����L���O�ʒu
	void		drawRankingName() const;	// �����L���O���O
	void		drawRankingScore() const;	// �����L���O�X�R�A

private:
	RankingData mRankData[5];
	RankingData mRankNewData;				// ���O�ƃX�R�A�̏������̂���

	int			mRankingNo;					// �����L���O����
	int			mInputIndex;				// ���͂��郉���L���O�l�[���̃C���f�b�N�X
	int			mInputKey;					// ���͂����L�[

	int			mNameAlpha[5][3];
	bool		mIsNameAlphaDown;
};