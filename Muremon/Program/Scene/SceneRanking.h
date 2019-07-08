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
	void		fadeIn();					// �t�F�[�h�C��
	void		fadeOut();					// �t�F�[�h�A�E�g

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
	void		drawZKey();

private:
	int time_count;	//�`�悷��^�C���J�E���g

	int rank;	//�����N�C�����Ă��邩

	int fade_flag;	//�t�F�[�h����t���O

	int alpha;	//�A���t�@�l

	int font_alpha;

	int alpha_count;	//�A���t�@�J�E���g

	int flag;

	int key_no;

	int in;

	int deray;

	int name_alpha[5][3];

	int name_red[5][3];

	int name_bule[5][3];

	int name_green[5][3];

	char keep_key[3];

	bool write_flag;

	int name_font_alpha;

	bool name_blink;

	bool name_alpha_down;

	int key_state;

	bool rank_draw_flag;

	int add_score;

	bool z_key_flag;

	bool z_alpha_up;

	int z_alpha;

	bool ranking_flag;
};