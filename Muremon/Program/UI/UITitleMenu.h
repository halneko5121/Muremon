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
	void	Init(Texture* texture, Vertex* vertex);
	void	Update();
	void	Draw();
	int		CurrentSelectIndex();

private:
	// �X�e�[�g�֐�
	void stateEnterIdle();
	void stateExeIdle();

	void stateEnterTop();
	void stateExeTop();

	void stateEnterMenuSelect();
	void stateExeMenuSelect();

	void stateEnterGameSelect();
	void stateExeGameSelect();

private:
	StateMachine<UITitleMenu>	mState;					// �X�e�[�g
	Texture*					mTexture;
	Vertex*						mVertex;
	D3DXVECTOR2					mCursorPos;
	int							mCurrentMenuItem;		// �J�[�\�����I�����Ă�����̂𔻕ʁB
	int							mAlphaZPush;
	int							mTimeCount;				// ���S�̃^�C���J�E���g
	int							mCursorAnime;			// �J�[�\���A�j���[�V����
	int							mDispItem;				// �O���t�B�b�N�̕ω���m�点��B
	bool						mIsZPush;
};