//---------------------------------------------
//
//      �L�[�̏��
//      �쐬�J�n��:	3��20��
//			�X�V��:	3��20��
//			�쐬��:	����
//
//---------------------------------------------
#include "Control.h"
#include "UtilInput.h"

C_Control::C_Control(void)
{
	key = 0;
	keep_key = key;
}

C_Control::~C_Control(void)
{
}

int C_Control::KeyCheck()
{
	return 0;
}

int C_Control::KeyCheckMission()
{
	return 0;
}