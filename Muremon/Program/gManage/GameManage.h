//---------------------------------------------
//
//      �Q�[���S�̂̊Ǘ����s��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��17��
//			�쐬��:	����
//
//---------------------------------------------

#ifndef _GAMEMANAGE_H_
#define _GAMEMANAGE_H_

#include "Library/Window/Window.h"
#include "Program/Scene/SceneBase.h"
#include "Library/Font/DirectFont.h"
#include "Library/Graphics/Vertex.h"

#include "Program/Scene/Logo.h"
#include "Program/Scene/Title.h"
#include "Program/Scene/Tutorial.h"
#include "Program/Scene/GameRefresh.h"
#include "Program/Scene/GameNormal.h"
#include "Program/Scene/Ranking.h"

class C_GameMain
{
private:
	C_Window*		mWindow;	// �E�B���h�E�N���X�ւ̃|�C���^
	C_DGraphics*	mGraphics;	// �O���t�B�b�N�N���X�ւ̃|�C���^
    C_DFont*		mFont;		// �t�H���g�N���X�ւ̃|�C���^
	C_SceneBase*	mScene;		// �V�[���N���X�ւ̃|�C���^
	DWORD			mBackground;
	int				mScore;

public:
    //////////////////////////////////////////////////////////
    //
    //      �����@�F�Q�[���Ŏg�������o�̏�����
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
    void InitGameMain(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F���C���֐�
    //      ����  �FHINSTANCE   hInstance   �C���X�^���X�n���h��
    //              HINSTANCE   hPrevInst   ���ۂ�WinMain�ɓn��
    //              LPSTR       lpCmdLine   ���ۂ�WinMain�ɓn��
    //              int         nShowCmd    ���ۂ�WinMain�ɓn��
    //      �߂�l�Fint         ���b�Z�[�W���[�v��Ԃ�
    //
    //////////////////////////////////////////////////////////
	int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�Q�[�������[�v�֐�
    //      ����  �F�Ȃ�
    //      �߂�l�Fint     ���b�Z�[�W
    //
    //////////////////////////////////////////////////////////
	int MsgLoop(void);

    //////////////////////////////////////////////////////////
    //
    //      �����@�F�Q�[���Ŏg�������o�̊J������
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
    void ReleaseGameMain(void);

    //////////////////////////////////////////////////////////
    //
    //      �����@�F���C�������̃R���g���[�����s��
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
    void ControlGame(void);
};

#endif	//_GAMEMANAGE_H_