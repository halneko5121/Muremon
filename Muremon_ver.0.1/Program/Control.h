//---------------------------------------------
//
//      �L�[�̏��
//      �쐬�J�n��:	3��20��
//			�X�V��:	3��20��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include <windows.h>
#include "Define.h"

class C_Control
{
private:
	int key;
	int keep_key;
public:
	int KeyCheck();			//�^�C�g���ȂǂŎg�p

	int KeyCheckGame();		//�Q�[���p

	int KeyCheckMission();	//�~�b�V�����p

	C_Control(void);
	~C_Control(void);
};
