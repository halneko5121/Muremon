//---------------------------------------------
//
//      キーの情報
//      作成開始日:	3月20日
//			更新日:	3月20日
//			作成者:	平野
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
	int KeyCheck();			//タイトルなどで使用

	int KeyCheckGame();		//ゲーム用

	int KeyCheckMission();	//ミッション用

	C_Control(void);
	~C_Control(void);
};
