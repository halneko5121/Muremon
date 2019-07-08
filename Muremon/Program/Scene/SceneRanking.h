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
	bool		update() override;
	void		draw() override;
	void		end() override;

private:
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

private:
	int			mRankingNo;					// �����L���O����
	int			mInputIndex;				// ���͂��郉���L���O�l�[���̃C���f�b�N�X
	int			mInputKey;					// ���͂����L�[

	int			mNameAlpha[5][3];
	char		mRankingName[3];
	bool		mIsNameAlphaDown;
};