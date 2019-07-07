#pragma once
/******************************************************************
 *	@file	UITitleMenu.h
 *	@brief	�^�C�g�����j���[UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/StateMachine.h"

class Texture;
class Vertex;

class UITitleMenu
{
public:
	UITitleMenu();
	~UITitleMenu();
	void	init(LPDIRECT3DDEVICE9 device);
	void	update();
	void	draw();

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
	void	stateEnterIdle();
	void	stateExeIdle();

	void	stateEnterTop();
	void	stateExeTop();

	void	stateEnterMenuSelect();
	void	stateExeMenuSelect();

	void	stateEnterGameSelect();
	void	stateExeGameSelect();

private:
	StateMachine<UITitleMenu>	mState;					// �X�e�[�g
	Texture*					mTexture;				// �e�N�X�`��
	Vertex*						mVertex;				// �o�[�e�b�N�X
	LPDIRECT3DDEVICE9			mDevice;				// �f�o�C�X
	D3DXVECTOR2					mCursorPos;				// �J�[�\���ʒu
	int							mCurrentMenuItem;		// �J�[�\�����I�����Ă�����̂𔻕ʁB
	int							mAlphaZPush;			// Zpush �p�̃A���t�@
	int							mTimeCount;				// ���S�̃^�C���J�E���g
	int							mCursorAnime;			// �J�[�\���A�j���[�V����
	bool						mIsZPush;
};