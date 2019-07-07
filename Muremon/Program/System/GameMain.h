#pragma once
/******************************************************************
 *	@file	GameMain.h
  *	@brief	�Q�[�����C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Window/Window.h"
#include "Library/StateMachine.h"

class Window;
class SceneBase;
class DirectInputKey;
class DirectInputMouse;
class DirectGraphics;
class C_Sprite;
class DirectFont;
class C_DWaveSound;
class C_DOggSound;
namespace Dix {
	class C_PCMPlayer;
}

class GameMain
{
public:
	/**
	 * @brief	�Q�[���Ŏg�������o�̏�����
	 */
    void		init();

	/**
     * @brief	���C���֐�												
	 * @param	hInstance   �C���X�^���X�n���h��(�v���O�����𓮂������߂̂���)		
	 * @param	hPrevInst   ���̑O�̏�Ԃ�ۑ����Ă���(1�ڂɏ�񂪓����ĂȂ��������p)
	 * @param	lpCmdLine	Windows����̖��߂��i�[�����(�|�C���^�̐擪�A�h���X)
	 * @param	nShowCmd    ���̖��߂���������̂�
     * @return  int         ���b�Z�[�W���[�v��Ԃ�						
	 */
	int WINAPI	winMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	/**
	 * @brief	�Q�[�������[�v�֐�
     * @return  ���b�Z�[�W�p�����[�^
	 */
	int			msgLoop();

	/**
     * @brief �Q�[���Ŏg�������o�̊J������
	 */
    void		release();

	/**
     * @brief �V�[�P���X�̊Ǘ����s��
	 */
	void		controlSequence();

private:
	// �X�e�[�g�֐�
	void		 stateEnterInit();
	void		 stateExeInit();

	void		 stateEnterRun();
	void		 stateExeRun();

	void		 stateEnterEnd();
	void		 stateExeEnd();

private:
	StateMachine<GameMain>	mState;			// �X�e�[�g
	Window*					mWindow;		// �E�B���h�E�N���X�ւ̃|�C���^
	SceneBase*				mScene;			// �V�[���N���X�ւ̃|�C���^
	DirectGraphics*			mGraphics;		// �O���t�B�b�N�N���X�ւ̃|�C���^
	char**					mSoundText;
	DWORD					mBackground;
	int						mScore;
};