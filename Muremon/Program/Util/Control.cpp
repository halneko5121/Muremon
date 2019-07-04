//---------------------------------------------
//
//      キーの情報
//      作成開始日:	3月20日
//			更新日:	3月20日
//			作成者:	平野
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