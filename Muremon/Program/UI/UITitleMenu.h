#pragma once
/******************************************************************
 *	@file	UITitleMenu.h
 *	@brief	�^�C�g�����j���[UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"

class Texture;
class Vertex;

class UITitleMenu
{
public:
	UITitleMenu();
	~UITitleMenu();
	void	init();
	void	update();
	void	draw() const;

	// ���j���[�Z���N�g
	bool	isDecideMenuSelectGame() const;
	bool	isDecideMenuSelectRanking() const;
	bool	isDecideMenuSelectExit() const;

	// �Q�[���Z���N�g
	bool	isDecideGameSelectRefresh() const;
	bool	isDecideGameSelectNormal() const;
	bool	isDecideGameSelectTutorial() const;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Top);
	DECLAR_STATE_FUNC2(MenuSelect);
	DECLAR_STATE_FUNC2(GameSelect);

private:
	StateMachine				mState;					// �X�e�[�g
	Texture*					mTexture;				// �e�N�X�`��
	Vertex*						mVertex;				// �o�[�e�b�N�X
	Vector2f					mCursorPos;				// �J�[�\���ʒu
	int							mCurrentMenuItem;		// �J�[�\�����I�����Ă�����̂𔻕ʁB
	int							mAlphaZPush;			// Zpush �p�̃A���t�@
	int							mTimeCount;				// ���S�̃^�C���J�E���g
	int							mCursorAnime;			// �J�[�\���A�j���[�V����
	bool						mIsZPush;
};