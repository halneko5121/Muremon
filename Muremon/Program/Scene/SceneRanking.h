#pragma once
/******************************************************************
 *	@file	SceneRanking.h
 *	@brief	�����L���O�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
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
	enum { cRankingCount = 5 };
	enum { cRankingNameCount = 3 };

	struct RankingData
	{
		char	mName[cRankingNameCount];	// ���O
		int		mScore;						// �X�R�A
	};

private:
	void		loadRanking();						// �f�[�^�̓ǂݍ���
	void		writeRanking();						// �f�[�^�̏�������
	int			checkRankingIn();					// �����N�C�����Ă邩�`�F�b�N
	void		sortRanking(int new_rank_index);	// �X�R�A�̕��ёւ�

	void		drawBackGround() const;				// �����L���O�w�i
	void		drawRankingNum() const;				// �����L���O����
	void		drawRankingName() const;			// �����L���O���O
	void		drawRankingScore() const;			// �����L���O�X�R�A

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(View);
	DECLAR_STATE_FUNC2(Input);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine		mState;						// �X�e�[�g
	RankingData			mRankData[cRankingCount];
	RankingData			mRankNewData;				// ���O�ƃX�R�A�̏������̂���

	int					mRankingNo;					// �����L���O����
	int					mInputIndex;				// ���͂��郉���L���O�l�[���̃C���f�b�N�X
	int					mInputKey;					// ���͂����L�[

	int					mNameAlpha[cRankingCount][cRankingNameCount];
	bool				mIsNameAlphaDown;
};