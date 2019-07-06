//---------------------------------------------
//
//      �^�C�g��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��20��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/StateMachine.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void PosiDrawControl();
	void KeyControl();

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
	StateMachine<SceneTitle>	mState;					// �X�e�[�g
	D3DXVECTOR2					mCursorPos;
	D3DXVECTOR2					mTitlePos;
	int							mTimeCount;				// ���S�̃^�C���J�E���g
	int							mAlphaZPush;			//
	int							mDispItem;				// �O���t�B�b�N�̕ω���m�点��B
	int							mCurrentMenuItem;		// �J�[�\�����I�����Ă�����̂𔻕ʁB
	int							mNextSceneIndex;		// ���̃V�[���ԍ�
	int							mCursorAnime;			// �J�[�\���A�j���[�V����
	bool						mIsZPush;
	int							mDrawCount;
	int							mCountMove;
};
