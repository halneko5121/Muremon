//---------------------------------------------
//
//      キーの情報
//      作成開始日:	3月20日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#include "Control.h"

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
	if(GetAsyncKeyState(VK_UP)){		//↑キー押したら
		key = KEY_UP;
	}
	else if(GetAsyncKeyState(VK_DOWN)){		//↓キー押したら
		key = KEY_DOWN;
	}
	else if(GetAsyncKeyState(VK_LEFT)){		//←キー押したら
		key = KEY_LEFT;
	}
	else if(GetAsyncKeyState(VK_RIGHT)){		//→キー押したら
		key = KEY_RIGHT;
	}
	else if(GetAsyncKeyState('Z')){			//Ｚキー押したら
		key = KEY_Z;
	}
	else if(GetAsyncKeyState(VK_RETURN)){	//ENTERキー押したら
		key = KEY_ENTER;
	}
	else if(GetAsyncKeyState('X')){			//Ｘキー押したら
		key = KEY_X;
	}
	else{
		key = 0;
	}
	if(key != keep_key){
		keep_key = key;
		return key;
	}
	return 0;
}

int C_Control::KeyCheckGame()
{
	//一段目
	if(GetAsyncKeyState('Q') & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState('W') & 0x8000){
		key = KEY_SKY_1;
	}
	else if(GetAsyncKeyState('E') & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState('R') & 0x8000){
		key = KEY_SKY_1;
	}
	else if(GetAsyncKeyState('T') & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState('Y') & 0x8000){
		key = KEY_SKY_1;
	}
	else if(GetAsyncKeyState('U') & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState('I') & 0x8000){
		key = KEY_SKY_1;
	}
	else if(GetAsyncKeyState('O') & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState('P') & 0x8000){
		key = KEY_SKY_1;
	}
	else if(GetAsyncKeyState(VK_OEM_3) & 0x8000){
		key = KEY_GROUND_1;
	}
	else if(GetAsyncKeyState(VK_OEM_4) & 0x8000){
		key = KEY_SKY_1;
	}
	//一段目終
	//二段目
	else if(GetAsyncKeyState('A') & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState('S') & 0x8000){
		key = KEY_SKY_2;
	}
	else if(GetAsyncKeyState('D') & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState('F') & 0x8000){
		key = KEY_SKY_2;
	}
	else if(GetAsyncKeyState('G') & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState('H') & 0x8000){
		key = KEY_SKY_2;
	}
	else if(GetAsyncKeyState('J') & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState('K') & 0x8000){
		key = KEY_SKY_2;
	}
	else if(GetAsyncKeyState('L') & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState(VK_OEM_PLUS) & 0x8000){
		key = KEY_SKY_2;
	}
	else if(GetAsyncKeyState(VK_OEM_1) & 0x8000){
		key = KEY_GROUND_2;
	}
	else if(GetAsyncKeyState(VK_OEM_6) & 0x8000){
		key = KEY_SKY_2;
	}
	//二段目終
	//三段目
	else if(GetAsyncKeyState('Z') & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState('X') & 0x8000){
		key = KEY_SKY_3;
	}
	else if(GetAsyncKeyState('C') & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState('V') & 0x8000){
		key = KEY_SKY_3;
	}
	else if(GetAsyncKeyState('B') & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState('N') & 0x8000){
		key = KEY_SKY_3;
	}
	else if(GetAsyncKeyState('M') & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState(VK_OEM_COMMA) & 0x8000){
		key = KEY_SKY_3;
	}
	else if(GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState(VK_OEM_2) & 0x8000){
		key = KEY_SKY_3;
	}
	else if(GetAsyncKeyState(VK_OEM_5) & 0x8000){
		key = KEY_GROUND_3;
	}
	else if(GetAsyncKeyState(VK_RETURN) & 0x8000){
		key = KEY_ENTER;
	}
	//三段目終
	else{
		key = 0;
	}
	if(key != keep_key){
		keep_key = key;
		return key;
	}
	return 0;
}

int C_Control::KeyCheckMission()
{
	//一段目
	if(GetAsyncKeyState('Q') & 0x8000){
		key = KEY_Q;
	}
	else if(GetAsyncKeyState('W') & 0x8000){
		key = KEY_W;
	}
	else if(GetAsyncKeyState('E') & 0x8000){
		key = KEY_E;
	}
	else if(GetAsyncKeyState('R') & 0x8000){
		key = KEY_R;
	}
	else if(GetAsyncKeyState('T') & 0x8000){
		key = KEY_T;
	}
	else if(GetAsyncKeyState('Y') & 0x8000){
		key = KEY_Y;
	}
	else if(GetAsyncKeyState('U') & 0x8000){
		key = KEY_U;
	}
	else if(GetAsyncKeyState('I') & 0x8000){
		key = KEY_I;
	}
	else if(GetAsyncKeyState('O') & 0x8000){
		key = KEY_O;
	}
	else if(GetAsyncKeyState('P') & 0x8000){
		key = KEY_P;
	}
	//一段目終
	//二段目
	else if(GetAsyncKeyState('A') & 0x8000){
		key = KEY_A;
	}
	else if(GetAsyncKeyState('S') & 0x8000){
		key = KEY_S;
	}
	else if(GetAsyncKeyState('D') & 0x8000){
		key = KEY_D;
	}
	else if(GetAsyncKeyState('F') & 0x8000){
		key = KEY_F;
	}
	else if(GetAsyncKeyState('G') & 0x8000){
		key = KEY_G;
	}
	else if(GetAsyncKeyState('H') & 0x8000){
		key = KEY_H;
	}
	else if(GetAsyncKeyState('J') & 0x8000){
		key = KEY_J;
	}
	else if(GetAsyncKeyState('K') & 0x8000){
		key = KEY_K;
	}
	else if(GetAsyncKeyState('L') & 0x8000){
		key = KEY_L;
	}
	//二段目終
	//三段目
	else if(GetAsyncKeyState('Z') & 0x8000){
		key = KEY_Z;
	}
	else if(GetAsyncKeyState('X') & 0x8000){
		key = KEY_X;
	}
	else if(GetAsyncKeyState('C') & 0x8000){
		key = KEY_C;
	}
	else if(GetAsyncKeyState('V') & 0x8000){
		key = KEY_V;
	}
	else if(GetAsyncKeyState('B') & 0x8000){
		key = KEY_B;
	}
	else if(GetAsyncKeyState('N') & 0x8000){
		key = KEY_N;
	}
	else if(GetAsyncKeyState('M') & 0x8000){
		key = KEY_M;
	}
	//三段目終
	else{
		key = 0;
	}
	if(key != keep_key){
		keep_key = key;
		return key;
	}
	return 0;
}