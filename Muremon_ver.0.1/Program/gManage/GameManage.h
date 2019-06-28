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

#include "program/gManage/Window.h"
#include "program/gManage/SceneManage.h"
#include "Library/DirectFont.h"
#include "LIbrary/DirectSound.h"
#include "LIbrary/Vertex.h"

#include "program/Scene/Logo.h"
#include "program/Scene/Title.h"
#include "program/Scene/Tutorial.h"
#include "program/Scene/GameRefresh.h"
#include "program/Scene/GameNormal.h"
#include "program/Scene/Ranking.h"

//#include "..\\GameScene.h"
//#include "..\\TitleScene.h"
//#include "..\\Fps.h"
//#include "..\\MapRead.h"

class C_GameMain
{
private:
	C_Window		*wind;	//�E�B���h�E�N���X�ւ̃|�C���^
	//C_DInput		*input;	//�C���v�b�g�N���X�ւ̃|�C���^
	C_DGraphics		*gra;	//�O���t�B�b�N�N���X�ւ̃|�C���^
	C_DSound		*sou;	//�T�E���h�N���X�ւ̃|�C���^
    C_DFont			*font;  //�t�H���g�N���X�ւ̃|�C���^
	C_SceneManage	*scene;	//�V�[���N���X�ւ̃|�C���^

	DWORD background;

	int score;
	//CFps		*fps;
	//MapRead		*mapread;
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