#pragma once
/******************************************************************
 *	@file	GameManage.h
 *	@brief	�Q�[���S�̂̊Ǘ����s��	
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Window/Window.h"

class C_Window;
class SceneBase;
class C_DInputKey;
class C_DInputMouse;
class C_DGraphics;
class C_Sprite;
class C_DFont;
class C_DWaveSound;
class C_DOggSound;
namespace Dix {
	class C_PCMPlayer;
}

class C_GameMain
{
public:
	/**
	 * @brief	�Q�[���Ŏg�������o�̏�����
	 */
    void InitGameMain();

	/**
     * @brief	���C���֐�												
	 * @param	hInstance   �C���X�^���X�n���h��(�v���O�����𓮂������߂̂���)		
	 * @param	hPrevInst   ���̑O�̏�Ԃ�ۑ����Ă���(1�ڂɏ�񂪓����ĂȂ��������p)
	 * @param	lpCmdLine	Windows����̖��߂��i�[�����(�|�C���^�̐擪�A�h���X)
	 * @param	nShowCmd    ���̖��߂���������̂�
     * @return  int         ���b�Z�[�W���[�v��Ԃ�						
	 */
	int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	/**
	 * @brief	�Q�[�������[�v�֐�
     * @return  ���b�Z�[�W�p�����[�^
	 */
	int MsgLoop();

	/**
     * @brief �Q�[���Ŏg�������o�̊J������
	 */
    void ReleaseGameMain();

	/**
     * @brief �V�[�P���X�̊Ǘ����s��
	 */
	void ControlSequence();

private:
	C_Window*			mWindow;		// �E�B���h�E�N���X�ւ̃|�C���^
	SceneBase*		mScene;			// �V�[���N���X�ւ̃|�C���^
	C_DGraphics*		mGraphics;		// �O���t�B�b�N�N���X�ւ̃|�C���^
	char**				mSoundText;
	DWORD				mBackground;
	int					mScore;
};